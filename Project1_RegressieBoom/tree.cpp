#include "tree.h"

namespace tree
{
	TreeNode::TreeNode(std::string _name) : 
		name(_name), trueNode(NULL), falseNode(NULL), leaf(true) {}

	TreeNode::TreeNode(std::string _name, TreeNode* _true, TreeNode* _false) : 
		name(_name), trueNode(_true), falseNode(_false), leaf(false) {}

	TreeNode::TreeNode(std::fstream& fileStream)
	{

	}

	TreeNode::~TreeNode()
	{
		delete trueNode;
		delete falseNode;
	}

	bool Tree::load(const std::string & filename)
	{
		// Open the file
		std::ifstream ruleFile(filename);

		// Return false if the file wasn't opened correctly
		if (!ruleFile)
		{
			return false;
		}

		// Parse the file's contents into the root node
		root = new TreeNode(ruleFile);
	}

	Tree::~Tree()
	{
		delete root;
	}
}