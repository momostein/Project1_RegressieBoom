﻿#pragma once
#include <iostream>
#include <regex>
#include <sstream>

#include "tree.h"
#include "json.h"

// TODO: Better comments

namespace tree
{
	template <typename T>
	void TreeNode<T>::print(const std::string & prefix)
	{
		std::cout << name << std::endl;

		if (!leaf)
		{
			std::cout << prefix << branchT;
			trueNode->print(prefix + prefixT);

			std::cout << prefix << branchF;
			falseNode->print(prefix + prefixF);
		}

		/*else
		{
			// Print out the price
			std::cout << price << std::endl;
		}*/
	}

	template<typename T>
	inline T TreeNode<T>::estimate(const organ::Organ & organ)
	{
		if (leaf)
		{
			return price;
		}
		else
		{
			if (evaluation.evaluate(organ))
				return trueNode->estimate(organ);
			else
				return falseNode->estimate(organ);
		}
	}

	template <typename T>
	TreeNode<T>::TreeNode(std::string _name) :
		name(_name), trueNode(NULL), falseNode(NULL), leaf(true) {}

	template <typename T>
	TreeNode<T>::TreeNode(std::string _name, TreeNode* _true, TreeNode* _false) :
		name(_name), trueNode(_true), falseNode(_false), leaf(false) {}

	template <typename T>
	TreeNode<T>::TreeNode(std::ifstream& fileStream)
	{
		// Look for the start of a this JSON object
		json::seek('{', fileStream);

		// Default is true, false when children are found
		leaf = true;

		bool foundName = false;
		while (true)
		{
			char c = json::seek("\"}", fileStream);

			if (c == '}')
			{
				break;
			}

			else if (c == '"')
			{
				std::string  key = json::parseUntill('"', fileStream);
				json::seek(':', fileStream);

				if (key == "name")
				{
					json::seek('"', fileStream);
					name = json::parseUntill('"', fileStream);

					foundName = true;

				}
				else if (key == "children")
				{
					char first = json::seek("[n", fileStream);
					switch (first)
					{
					case 'n': // "children" : null
						break;
					case '[': // "children" : [{...}, {...}]
						trueNode = new TreeNode<T>(fileStream);
						json::seek(',', fileStream);
						falseNode = new TreeNode<T>(fileStream);

						json::seek(']', fileStream);
						leaf = false;
						break;
					}
				}

				char end = json::seek(",}", fileStream);
				if (end == '}')
					break;
			}
		}

		// A name field must always be present
		if (!foundName)
		{
			throw std::exception("Name field not found in json object!");
		}

		// Read the price from the name
		if (leaf)
		{
			std::smatch m;

			// searches for "x of Price"
			// R"(...)" for a raw string
			std::regex e(R"((.*) of Price)");

			if (!std::regex_search(name, m, e))
			{
				std::string error = "Wrong name format for the price: " + name;
				throw std::exception(error.c_str());
			}

			// Convert the first submatch, the price, to a stringstream to parse into the price template
			std::istringstream iss(m[1]);
			iss >> price;
		}
		else
		{
			evaluation = eval::Evaluation(name);
		}
	}

	template <typename T>
	TreeNode<T>::~TreeNode()
	{
		delete trueNode;
		delete falseNode;
	}

	template <typename T>
	void Tree<T>::load(const std::string & filename)
	{
		// Open the file
		std::ifstream ruleFile(filename);

		// Return false if the file wasn't opened correctly
		if (!ruleFile)
		{
			throw std::exception("File not found!");
		}

		// Delete the previously stored root
		delete root;

		// Parse the file's contents into the root node
		root = new TreeNode<T>(ruleFile);
		ruleFile.close();
	}

	template<typename T>
	inline T Tree<T>::estimate(organ::Organ & organ)
	{
		return root->estimate(organ);
	}

	template <typename T>
	void Tree<T>::print() {
		root->print();
	}

	template <typename T>
	Tree<T>::~Tree()
	{
		delete root;
	}
}
