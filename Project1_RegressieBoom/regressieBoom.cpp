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
	double load_times[5];
	double avarage_times[5];
	// Declare the organ that is to be estimated
	Organ myOrgan;
	myOrgan.model = "T202";
	myOrgan.condition = EXCELLENT;
	myOrgan.leslie = true;

	// Declare the decision tree
	Tree<int> regressionTree;
	for (int i = 0; i < 5; i++) {
		cout << "depth " << i + 1 << endl;
	try {
		// Load the rules from the rule file into the tree
		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();
		int x = 0;
		while (x < 10000) {
		regressionTree.load(rulefiles[i]);
		x += 1;
		}
		end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		load_times[i] = elapsed_seconds.count() / 10000;
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

	// Print the organ
	print(myOrgan);
	cout << endl;

	// Estimate the price and print it
	int x = 0;
	double elapsed_secs = 0;
	int price;
	std::chrono::time_point<std::chrono::system_clock> start, end;

	start = std::chrono::system_clock::now();
	while( x<10000){
	price = regressionTree.estimate(myOrgan);
	
	x += 1;
	}
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	avarage_times[i] = elapsed_seconds.count() / 10000;
	std::cout << "average time: " << elapsed_seconds.count()/10000 << "s\n";
	cout << "Price estimate: " << price << endl;
	}
	for (int i = 0; i < 5; i++) {

		cout << "depth " << i + 1 << ": " << load_times[i] << endl;
	}
	for (int i = 0; i < 5; i++) {
		
		cout << "depth " << i + 1 << ": " << avarage_times[i] <<endl;
	}

	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}