#pragma once
#include <string>
#include <fstream>

#include "evaluation.h"
#include "organ.h"

namespace tree
{
	// Speciale karakters werken precies niet in string literals zetten,
	// dus gebruiken wij hun ascii waardes in een null terminated char array
	const char branchT[] = { 195u, 196u, 'T', 196u , 0u }; // "├─T─"
	const char prefixT[] = { 179u,	' ', ' ',  ' ' , 0u }; // "│   "
	const char branchF[] = { 192u, 196u, 'F', 196u , 0u }; // "└─F─"
	const char prefixF[] = "    ";

	template <typename T>
	class TreeNode
	{
	private:
		bool leaf;

		std::string name;

		TreeNode<T>* falseNode;
		TreeNode<T>* trueNode;
		
		eval::Evaluation evaluation;
		
		T price;

	public:
		void print(const std::string& prefix = "");
		T estimate(const organ::Organ& organ);

		TreeNode(std::string _name);
		TreeNode(std::string _name, TreeNode<T>* _true, TreeNode<T>* _false);

		// Parse the node from a filestream
		TreeNode(std::ifstream& fileStream);
		~TreeNode();
	};

	template <typename T>
	class Tree
	{
	private:
		TreeNode<T>* root;

	public:
		bool load(const std::string& filename);

		T estimate(organ::Organ& organ);
		void print();

		Tree<T>() : root(NULL) {};
		~Tree<T>();
	};
}