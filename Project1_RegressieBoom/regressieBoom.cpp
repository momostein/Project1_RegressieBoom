#include <iostream>
#include <string>

#include "tree.ipp"
using namespace tree;

int main()
{
	using namespace std;
	using namespace organ;

	const string ruleFile = "tree_gen/rules_bad.json";

	Organ myOrgan;
	myOrgan.model = "T202";
	myOrgan.condition = EXCELLENT;
	myOrgan.leslie = true;

	Tree<int> regressionTree;
	
	try {
		regressionTree.load(ruleFile);
	}
	catch (exception e)
	{
		cout << "Something went wrong while loading the regression tree:" << endl;
		cout << "Error: \"" << e.what() << "\"" << endl;
		cout << endl << "Press enter to continue...";
		cin.get();
		return -1;
	}

	// Print the tree
	regressionTree.print();
	cout << endl << endl;

	print(myOrgan);

	cout << endl;

	// Estimate the price and print it
	cout << "Price estimate: " << regressionTree.estimate(myOrgan) << endl;

	// Wait for user to close
	cout << endl << "Press enter to continue...";
	cin.get();
	return 0;
}