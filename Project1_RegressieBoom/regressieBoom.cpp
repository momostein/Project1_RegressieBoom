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
	const string ruleFile = "tree_gen/rules.json";

	// Declare the organ that is to be estimated
	Organ myOrgan;
	myOrgan.model = "T202";
	myOrgan.condition = EXCELLENT;
	myOrgan.leslie = true;

	// Declare the decision tree
	Tree<int> regressionTree;
	
	try {
		// Load the rules from the rule file into the tree
		regressionTree.load(ruleFile);
		

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
	std::cout << "average time: " << elapsed_seconds.count()/10000 << "s\n";
	cout << "Price estimate: " << price << endl;
	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}