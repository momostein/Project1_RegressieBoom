#include <chrono>
#include <cstdlib>
#include <ctime>
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
	// Filenames of the rule files
	const string ruleFile = "tree_gen/rules.json";
	const int depths = 5;
	const string rulefiles[depths] = {
		"tree_gen/rules_d1.json",
		"tree_gen/rules_d2.json",
		"tree_gen/rules_d3.json",
		"tree_gen/rules_d4.json",
		"tree_gen/rules_d5.json"
	};

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

	// How much times the tests should be executed
	const int load_amount = 100;
	const int estimate_amount = 10000;

	// Arrays to store the average times
	double average_load_times[depths];
	double average_estimate_times[depths];

	// Arrays to store the average errors
	double average_errors[depths];
	double average_abs_errors[depths];
	double average_rel_errors[depths];

	// Generate an array and fill it with dafault organs
	Organ organs[estimate_amount];
	for (int i = 0; i < estimate_amount; i++)
	{
		organs[i] = DefaultOrgans[i % DefaultOrgans.size()];
	}
	
	// Declare the decision tree
	Tree<int> regressionTree;

	// For every depth
	for (int i = 0; i < 5; i++)
	{
		cout << endl << "Depth = " << i + 1 << ":" << endl;
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
			average_load_times[i] = elapsed_seconds.count() / load_amount;
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
		int prices[estimate_amount];

		// The start and end times
		chrono::time_point<chrono::high_resolution_clock> start, end;

		// Clock the start time
		start = chrono::high_resolution_clock::now();

		// Estimate the prices and store them in the array
		for (int j = 0; j < estimate_amount; j++)
		{
			prices[j] = regressionTree.estimate(organs[j]);
		}

		// Clock the end time
		end = chrono::high_resolution_clock::now();

		// Calculate the total time and the average time
		chrono::duration<double> elapsed_seconds = end - start;
		average_estimate_times[i] = elapsed_seconds.count() / estimate_amount;

		// Calculate the average errors
		int total_error = 0;
		int total_abs_error = 0;
		double total_rel_error = 0;
		for (int j = 0; j < estimate_amount; j++)
		{
			int error = prices[i] - organs[j].price;
			int abs_error = abs(error);

			total_error += error;
			total_abs_error += abs_error;
			total_rel_error += abs_error / organs[j].price;
		}

		average_errors[i] = total_error / estimate_amount;
		average_abs_errors[i] = total_abs_error / estimate_amount;
		average_rel_errors[i] = total_rel_error / estimate_amount;

		cout << endl;
		cout << "Average load time: " << average_load_times[i] << "s\n";
		cout << "Average estimate time: " << average_estimate_times[i] << "s\n";
		cout << "Average error: " << average_errors[i] << endl;
		cout << "Average abs error: " << average_abs_errors[i] << endl;
		cout << "Average rel error: " << average_rel_errors[i] << "%" << endl;
		
	}

	cout << endl << "Average load times:" << endl;
	print_results(average_load_times, depths, "s");
	
	cout << endl << "Average estimate times:" << endl;
	print_results(average_estimate_times, depths, "s");
	
	cout << endl << "Average errors:" << endl;
	print_results(average_errors, depths);

	cout << endl << "Average absolute errors:" << endl;
	print_results(average_abs_errors, depths);

	cout << endl << "Average relative errors:" << endl;
	print_results(average_rel_errors, depths, "%");

	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}

void print_results(const double * results, int count, const string& unit)
{ 
	for (int i = 0; i < count; i++)
	{
		cout << " - Depth = " << i + 1 << ": " << results[i] << unit << endl;
	}
}