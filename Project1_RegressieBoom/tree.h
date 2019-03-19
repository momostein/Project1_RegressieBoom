#pragma once
#include <string>
#include <fstream>

#include "organ.h"

namespace tree
{
	// Speciale karakters kunnen we niet in string literals zetten,
	// dus gebruiken wij hun ascii waardes
	const char branchT[] = { 195, 196, 'T', 196 , 0 }; // "├─T─"
	const char prefixT[] = { 179, ' ', ' ', ' ' , 0 }; // "│   "
	const char branchF[] = { 192, 196, 'F', 196 , 0 }; // "└─F─"
	const char prefixF[] = "    ";

	class TreeNode
	{
	private:
		bool leaf;

		std::string name;

		TreeNode* falseNode;
		TreeNode* trueNode;

	public:
		void print(const std::string& prefix = "");

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