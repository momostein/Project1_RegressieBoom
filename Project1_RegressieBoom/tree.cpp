#include <iostream>
#include "tree.h"
#include "json.h"

namespace tree
{
	TreeNode::TreeNode(std::string _name) :
		name(_name), trueNode(NULL), falseNode(NULL), leaf(true) {}

	TreeNode::TreeNode(std::string _name, TreeNode* _true, TreeNode* _false) :
		name(_name), trueNode(_true), falseNode(_false), leaf(false) {}

	TreeNode::TreeNode(std::ifstream& fileStream)
	{
		// Look for the start of a this JSON object
		json::seek('{', fileStream);

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
				if (key == "children")
				{
					char first = json::seek("[n", fileStream);
					switch (first)
					{
					case 'n': // "children" : null
						break;
					case '[': // "children" : [{...}, {...}]
						trueNode = new TreeNode(fileStream);
						json::seek(',', fileStream);
						falseNode = new TreeNode(fileStream);

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

		if (!foundName)
		{
			throw json::ParseError("TreeNode Parse Error: name not found");
		}
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