#pragma once
#include <string>
#include <fstream>

#include "organ.h"

namespace tree
{
	class TreeNode
	{
	private:
		bool leaf;
		std::string name;

		TreeNode* trueNode;
		TreeNode* falseNode;

	public: 
		TreeNode(std::string _name);
		TreeNode(std::string _name, TreeNode* _true, TreeNode* _false);

		//  Parse the node from a filestream
		TreeNode(std::fstream& fileStream);

		~TreeNode();
	};
	class Tree
	{
	private:
		TreeNode* root;

	public:
		bool load(const std::string& filename);

		int estimate(organ::Organ& organ);
		void print();

		Tree() : root(NULL) {};
		~Tree();
	};
}