#include <regex>

#include "evaluation.h"


namespace eval
{
	bool Evaluation::evaluate(const organ::Organ & organ)
	{
		return false;
	}

	Evaluation::Evaluation(const std::string & eval_string)
	{
		std::smatch m;

		// Searches for "Field_Value (>/<) (float)"
		// R"(...)" for a raw string
		std::regex e(R"((.*)_(.*) ([><]) ([-+]?[0-9]*\.?[0-9]*))");
		if (!std::regex_search(eval_string, m, e))
			throw std::exception("Wrong Name format for evalutation");

		std::string sField = m[1];
		std::string sFieldVal = m[2];
		if (sField == "Model")
		{
			field = MODEL;
			model = sFieldVal;
		}
		else if (sField == "Condition")
		{
			field = CONDITION;
			if (sFieldVal == "fair")
				condition = organ::Condition::FAIR;
			else if (sFieldVal == "good")
				condition = organ::Condition::GOOD;
			else if (sFieldVal == "excellent")
				condition = organ::Condition::EXCELLENT;
			
			else 
			{
				std::string error = "Unknow Condition: " + sFieldVal;
				throw error;
			}
				
		}
		else if (sField == "Leslie")
		{
			field = LESLIE;
			bool leslie = sFieldVal == "yes";
			
		}
		else
		{
			std::string error = "Unknow Field: " + sField;
			throw error;
		}

		comp = m[3].str()[0]; //Grab first char from the string

		comp_val = std::stof(m[4]);
	}

	Evaluation::Evaluation()
	{

	}
}