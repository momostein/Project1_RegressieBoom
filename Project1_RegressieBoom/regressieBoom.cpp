#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "tree.ipp"
#include "regressieBoom.h"

using namespace std;
using namespace organ;
using namespace tree;


int main()
{
	// Main start and end times
	chrono::time_point<chrono::high_resolution_clock> main_start, main_end;
	main_start = chrono::high_resolution_clock::now();

	const int depths = 5;
	const int fields = 6;

	// Headers for the csv file
	const string csv_headers[fields] = { "depth", "load", "est","total","abs","rel" };

	// Headers and units for printing tot the terminal
	const string disp_headers[fields] = { "Tree Depth", "Load time", "Estimate time","Total error","Absolute error","Relative error"};
	const string units[fields] = { "", "s", "s", "", "", "%" };

	// How much times the tests should be executed
	// Lower these if the tests take too long
	const int load_amount = 10000;
	const int estimate_amount = 10000000;

	// Filenames of the rule files
	// const string ruleFile = "tree_gen/rules.json"; // Single rule file
	const string rulefiles[depths] = {
		"tree_gen/rules_d1.json",
		"tree_gen/rules_d2.json",
		"tree_gen/rules_d3.json",
		"tree_gen/rules_d4.json",
		"tree_gen/rules_d5.json"
	};

	// Filename of the output csv file
	const string outFile = "results/data.csv";

	// A list of default organs for testing
	const vector<Organ> DefaultOrgans = {
			Organ("B3",		EXCELLENT,	true,	4513),
			Organ("T202",	FAIR,		true,	625),
			Organ("A100",	GOOD,		true,	1051),
			Organ("T202",	GOOD,		false,	270),
			Organ("M102",	GOOD,		true,	870),
			Organ("A100",	EXCELLENT,	false,	1770),
			Organ("T202",	FAIR,		false,	99),
			Organ("A100",	GOOD,		true,	1900),
			Organ("E112",	FAIR,		false,	77)
	};

	// Twodimensional array to store the test results
	double results[depths][fields];

	// The regression tree
	Tree<int> regressionTree;

	// Do the tests for every depth
	for (int i = 0; i < depths; i++)
	{
		int depth = i + 1;

		results[i][0] = depth;
		cout << endl << "Depth = " << depth << ":" << endl;

		// Try to load the test a bunch of times
		try
		{
			// Start and end times
			chrono::time_point<chrono::high_resolution_clock> start, end;

			// Clock the start time
			start = chrono::high_resolution_clock::now();

			// Load the tree a bunch of times
			for (int j = 0; j < load_amount; j++)
			{
				// Load the rules from the rule file into the tree
				regressionTree.load(rulefiles[i]);
			}

			// Clock the end time
			end = chrono::high_resolution_clock::now();

			// Total time and the average time
			chrono::duration<double> elapsed_seconds = end - start;
			results[i][1] = elapsed_seconds.count() / load_amount;
		}
		catch (exception& e)
		{
			// Catch and print out the error
			cout << "Something went wrong while loading the regression tree:" << endl;
			cout << e.what() << endl;

			// Wait for user confirmation
			cout << endl << "Press enter to continue...";
			cin.get();
			return -1;
		}

		// Print the tree
		regressionTree.print();

		// An array to store the price estimates
		vector<int> prices(estimate_amount);

		// The start and end times
		chrono::time_point<chrono::high_resolution_clock> start, end;

		// Clock the start time
		start = chrono::high_resolution_clock::now();

		// Estimate the prices and store them in the array
		for (int j = 0; j < prices.size(); j++)
		{
			Organ test_organ = DefaultOrgans[j % DefaultOrgans.size()];
			prices[j] = regressionTree.estimate(test_organ);

		}

		// Clock the end time
		end = chrono::high_resolution_clock::now();

		// Calculate the total time and the average time
		chrono::duration<double> elapsed_seconds = end - start;
		results[i][2] = elapsed_seconds.count() / estimate_amount;

		// Calculate the average errors
		long long total_error = 0;
		unsigned long long total_abs_error = 0;
		double total_rel_error = 0;
		for (int j = 0; j < prices.size(); j++)
		{
			int real_price = DefaultOrgans[j % DefaultOrgans.size()].price;

			int error = prices[j] - real_price;
			int abs_error = abs(error);

			total_error += error;
			total_abs_error += abs_error;
			total_rel_error += abs_error / (double)real_price;
		}

		results[i][3] = total_error / (double)estimate_amount;
		results[i][4] = total_abs_error / (double)estimate_amount;
		results[i][5] = total_rel_error / estimate_amount;

		cout << endl;
		cout << "Average load time: " << results[i][1] << "s\n";
		cout << "Average estimate time: " << results[i][2] << "s\n";
		cout << "Average error: " << results[i][3] << endl;
		cout << "Average abs error: " << results[i][4] << endl;
		cout << "Average rel error: " << results[i][5] << "%" << endl;
	}

	// Print out the results
	cout << endl;
	print_results(&(results[0][0]), disp_headers, units, depths, fields);

	ofstream csv_out(outFile);
	if (csv_out)
	{
		csv_write(csv_out, &(results[0][0]), csv_headers, depths, fields);
	}
	else
	{
		cout << "Couldn't open the output file..." << endl;
	}
	csv_out.close();

	main_end = chrono::high_resolution_clock::now();
	chrono::duration<double> total_time = main_end - main_start;
	
	cout << "Test completed after " << total_time.count() << " seconds." << endl;

	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}

// Prints out the results per field
void print_results(const double * results, const string * headers, const string * units, int rows, int cols)
{
	for (int i = 1; i < cols; i++)
	{
		cout << headers[i] << ':' << endl;
		for (int j = 0; j < rows; j++)
		{
			cout << " - Depth = " << *(results + j * cols) << ": " << *(results + i + j * cols) << units[i] << endl;
		}
		cout << endl;
	}
}

// Writes the results to a csv file
void csv_write(ofstream & out_file, const double * data, const string * headers, int rows, int cols, char sep)
{
	for (const string* header = headers; header < headers + cols; header++)
	{
		out_file << *header;
		if (header != headers + cols - 1)
		{
			out_file << sep;
		}
	}
	out_file << endl;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			out_file << data[row*cols + col];
			if (col != cols - 1) {
				out_file << sep;
			}
		}
		out_file << endl;
	}

}
