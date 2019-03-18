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

		

	public: 
		std::string name;

		TreeNode* falseNode;

		TreeNode* trueNode;
		TreeNode(std::string _name);
		TreeNode(std::string _name, TreeNode* _true, TreeNode* _false);

		//  Parse the node from a filestream
		TreeNode(std::ifstream& fileStream);

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
		void disp(TreeNode* node, int w);

		Tree() : root(NULL) {};
		~Tree();
		friend class TreeNode;
	};
}