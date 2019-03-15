#include <iostream>
#include <string>

#include "tree.h"
using namespace tree;

int main()
{
	const string ruleFile = "tree_gen/rules.json";
	{
		TreeNode* tLeaf = new TreeNode("True Leaf");
		TreeNode* fLeaf1 = new TreeNode("False Leaf 1");
		TreeNode* tbranch = new TreeNode("True Branch", tLeaf, fLeaf1);
		TreeNode* fLeaf2 = new TreeNode("False Leaf 2");
		TreeNode* root = new TreeNode("Root", tbranch, fLeaf2);

		delete root;
	}
	cin.get();

	return 0;
}