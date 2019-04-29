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

	// Filename of the rule file
	const string rulefiles[5] = { "tree_gen/rules_d1.json", "tree_gen/rules_d2.json", "tree_gen/rules_d3.json", "tree_gen/rules_d4.json", "tree_gen/rules_d5.json" };
	const string ruleFile = "tree_gen/rules.json";

	// Declare the organ that is to be estimated
	Organ myOrgan;
	myOrgan.model = "T202";
	myOrgan.condition = EXCELLENT;
	myOrgan.leslie = true;

	// How much times the tests should be executed
	const int load_amount = 100;
	const int estimate_amount = 10000;

	// Array to store the load times
	double average_load_times[5];
	double avarage_times[5];

	// Print the organ
	print(myOrgan);

	// Declare the decision tree
	Tree<int> regressionTree;

	// For every depth
	for (int i = 0; i < 5; i++)
	{
		cout << endl << "depth " << i + 1 << ":" << endl;
		try
		{
			// Start and end times
			std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
			start = std::chrono::high_resolution_clock::now();

			// Load the tree a bunch of times
			for (int j = 0; j < load_amount; j++)
			{
				// Load the rules from the rule file into the tree
				regressionTree.load(rulefiles[i]);
			}

			// End time
			end = std::chrono::high_resolution_clock::now();

			// Total time
			std::chrono::duration<double> elapsed_seconds = end - start;

			// Average load time
			average_load_times[i] = elapsed_seconds.count() / load_amount;
		}
		catch (exception& e)
		{
			// Catch and print out the error
			cout << "Something went wrong while loading the regression tree:" << endl;
			cout << "Error: \"" << e.what() << "\"" << endl;

			// Wait for user confirmation
			cout << endl << "Press enter to continue...";
			cin.get();
			return -1;
		}

		// Print the tree
		regressionTree.print();
		cout << endl << endl;

		// Estimate the price and print it
		int x = 0;
		double elapsed_secs = 0;
		int price;
		std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

		start = std::chrono::high_resolution_clock::now();
		for (int j = 0; j < estimate_amount; j++)
		{
			price = regressionTree.estimate(myOrgan);
		}
		end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		avarage_times[i] = elapsed_seconds.count() / estimate_amount;
		std::cout << "average time: " << elapsed_seconds.count() / estimate_amount << "s\n";
		cout << "Price estimate: " << price << endl;
	}
	for (int i = 0; i < 5; i++) {

		cout << "depth " << i + 1 << ": " << average_load_times[i] << endl;
	}
	for (int i = 0; i < 5; i++) {

		cout << "depth " << i + 1 << ": " << avarage_times[i] << endl;
	}

	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}