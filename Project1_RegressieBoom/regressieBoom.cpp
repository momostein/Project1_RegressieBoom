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
	myOrgan.condition = FAIR;
	myOrgan.leslie = true;

	Tree<int> regressionTree;
	if (!regressionTree.load(ruleFile)) {
		cout << "Couldn't open file..." << endl;
		cin.get();
		return -1;
	}

	regressionTree.print();

	cout << endl << endl;
	cout << "Estimating Organ:" << endl;
	cout << "\tModel: " << myOrgan.model << endl;

	cout << "\tCondition: ";
	switch (myOrgan.condition)
	{
	case FAIR:
		cout << "Fair";
		break;
	case GOOD:
		cout << "Good";
		break;
	case EXCELLENT:
		cout << "Excellent";
	default:
		break;
	}
	cout << endl;

	cout << "\tLeslie: " << boolalpha << myOrgan.leslie << endl << endl;

	cout << "Price estimate: " << regressionTree.estimate(myOrgan) << endl;


	system("pause");
	return 0;
}