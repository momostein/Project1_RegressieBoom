#include <iostream>
#include <string>
#include <chrono>    
#include <ctime> 
#include "tree.ipp"
using namespace tree;

int main()
{
	using namespace std;
	using namespace organ;

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

	// Declare the organ that is to be estimated
	Organ myOrgan;
	myOrgan.model = "T202";
	myOrgan.condition = EXCELLENT;
	myOrgan.leslie = true;

	// How much times the tests should be executed
	const int load_amount = 100;
	const int estimate_amount = 10000;

	// Array to store the load times
	double average_load_times[depths];
	double avarage_estimate_times[depths];

	// Generate an array with dafault organs to check
	Organ organs[estimate_amount];
	for (int i = 0; i < estimate_amount; i++)
	{

	}

	// And an array to store the price estimates


	// Print the organ
	print(myOrgan);

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
			start = chrono::high_resolution_clock::now();

			// Load the tree a bunch of times
			for (int j = 0; j < load_amount; j++)
			{
				// Load the rules from the rule file into the tree
				regressionTree.load(rulefiles[i]);
			}

			// End time
			end = chrono::high_resolution_clock::now();

			// Total time
			chrono::duration<double> elapsed_seconds = end - start;

			// Average load time
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

		// Estimate the price and print it
		int x = 0;
		double elapsed_secs = 0;
		int price;
		chrono::time_point<chrono::high_resolution_clock> start, end;

		start = chrono::high_resolution_clock::now();
		for (int j = 0; j < estimate_amount; j++)
		{
			price = regressionTree.estimate(myOrgan);
		}
		end = chrono::high_resolution_clock::now();

		chrono::duration<double> elapsed_seconds = end - start;
		avarage_estimate_times[i] = elapsed_seconds.count() / estimate_amount;

		cout <<endl<< "Price estimate: " << price << endl;
		cout << "Average load time: " << average_load_times[i] << "s\n";
		cout << "Average estimate time: " << avarage_estimate_times[i] << "s\n";
		
	}

	// Print the average load times
	cout << endl << "Average load times:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << " - Depth = " << i + 1 << ": " << average_load_times[i] << "s\n";
	}

	// Print the average estimate times
	cout << endl << "Average estimate times:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << " - Depth = " << i + 1 << ": " << avarage_estimate_times[i] << "s\n";
	}

	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}