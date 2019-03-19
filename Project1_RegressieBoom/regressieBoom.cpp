#include <iostream>
#include <string>

#include "tree.h"
using namespace tree;

int main()
{
	using namespace std;
	const string ruleFile = "tree_gen/rules.json";

	tree::Tree regressionTree;
	if (!regressionTree.load(ruleFile)) {
		cout << "Couldn't open file..." << endl;
		cin.get();
		return -1;
	}

	regressionTree.print();

	system("pause");
	return 0;
}