#include <regex>

#include "evaluation.h"


namespace eval
{
	bool Evaluation::evaluate(const organ::Organ & organ)
	{
		bool val;

		switch (field)
		{
		case eval::Evaluation::MODEL:
			val = model == organ.model;
			break;
		case eval::Evaluation::CONDITION:
			val = condition == organ.condition;
			break;
		case eval::Evaluation::LESLIE:
			val = leslie == organ.leslie;
			break;
		default:
			val = false;
			break;
		}
		
		switch (comp)
		{
		case '>':
			return val > comp_val;
		case '<':
			return val < comp_val;
		default:
			return false;
		}
	}

	Evaluation::Evaluation(const std::string & eval_string)
	{
		// Regex matches
		std::smatch m;

		// Searches for "Field_Value (>/<) (float)"
		// R"(...)" for a raw string
		std::regex e(R"((.*)_(.*) ([><]) ([-+]?[0-9]*\.?[0-9]*))");

		// Search the string for an evaluation format
		if (!std::regex_search(eval_string, m, e))
		{
			std::string error = "Wrong name format for an evaluation: " + eval_string;
			throw std::exception(error.c_str());
		}
			

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
				throw std::exception(error.c_str());
			}
				
		}
		else if (sField == "Leslie")
		{
			field = LESLIE;
			leslie = sFieldVal == "yes";
			
		}
		else
		{
			std::string error = "Unknow Field: " + sField;
			throw std::exception(error.c_str());
		}

		comp = m[3].str()[0]; //Grab first char from the string

		comp_val = std::stof(m[4]);
	}

	Evaluation::Evaluation()
	{

	}
}