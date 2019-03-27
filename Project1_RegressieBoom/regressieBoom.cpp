#include <iostream>
#include <string>

#include "tree.ipp"
using namespace tree;

int main()
{
	using namespace std;
	const string ruleFile = "tree_gen/rules.json";

	Tree<int> regressionTree;
	if (!regressionTree.load(ruleFile)) {
		cout << "Couldn't open file..." << endl;
		cin.get();
		return -1;
	}

	regressionTree.print();

	system("pause");
	return 0;
}