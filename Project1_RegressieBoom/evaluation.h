#pragma once
#include <string>

#include "organ.h"

namespace eval
{
	// A class that store the decision for one node in the regression tree
	class Evaluation
	{
	public:
		// The possible property fields
		enum Field {
			MODEL,
			CONDITION,
			LESLIE,
		};

		// Evaluate the organ
		bool evaluate(const organ::Organ& organ);

		// Constructor from a "name" inside a node
		Evaluation(const std::string& eval_string);

		// Default constructor
		Evaluation() {};

	private:
		// Wich property field the evaluation should look at
		Field field;

		// Field values
		std::string model;
		organ::Condition condition;
		bool leslie;

		// The comparison operator that should be used
		char comp;

		// The value that the property value should be compared to
		float comp_val;

	};
}