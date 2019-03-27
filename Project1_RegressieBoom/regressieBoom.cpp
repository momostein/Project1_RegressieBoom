#include <iostream>
#include <string>

#include "tree.ipp"
using namespace tree;

int main()
{
	using namespace std;
	using namespace organ;

	const string ruleFile = "tree_gen/rules.json";

	Organ myOrgan;
	myOrgan.model = "T202";
	myOrgan.condition = EXCELLENT;
	myOrgan.leslie = true;

	Tree<int> regressionTree;
	if (!regressionTree.load(ruleFile)) {
		cout << "Couldn't open file..." << endl;
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

	// Geen system("pause") gebruiken. Het is zeer platform specifiek
	// system("pause");
	return 0;
}