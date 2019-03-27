#pragma once
#include <string>

#include "organ.h"

namespace eval
{
	class Evaluation
	{
	public:
		enum Field {
			MODEL,
			CONDITION,
			LESLIE,
		};

		bool evaluate(const organ::Organ& organ);

		Evaluation(const std::string& eval_string);
		Evaluation();

	private:
		Field field;

		// Field value
		std::string model;
		organ::Condition condition;
		bool leslie;

		char comp;

		float comp_val;

	};
}