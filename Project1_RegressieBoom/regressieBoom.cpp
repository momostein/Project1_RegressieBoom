#include <iostream>
#include <string>

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
	cout << "Price estimate: " << regressionTree.estimate(myOrgan) << endl;

	// Wait for user confirmation
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}