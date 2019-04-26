#include <regex>

#include "evaluation.h"

namespace eval
{
	bool Evaluation::evaluate(const organ::Organ & organ)
	{
		// should be changed to float in case a numeric property is added to organ
		bool val;

		// Check wich field should be evaluated
		// and calculate the value
		switch (field)
		{
		case eval::Evaluation::MODEL:
			val = (model == organ.model);
			break;
		case eval::Evaluation::CONDITION:
			val = (condition == organ.condition);
			break;
		case eval::Evaluation::LESLIE:
			val = (leslie == organ.leslie);
			break;
		default:
			val = false;
			break;
		}

		// Return the result of the selected comparison
		switch (comp)
		{
		case '>':
			return (val > comp_val);
		case '<':
			return (val < comp_val);
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
			//If no matches were found, throw an exception
			std::string error = "Wrong name format for an evaluation: " + eval_string;
			throw std::exception(error.c_str());
		}


		// Get the strings from the capture groups
		std::string sField = m[1]; // The Field
		std::string sFieldVal = m[2]; // The Value of the field

		// Save the right settings for the right fields
		if (sField == "Model")
		{
			field = MODEL;
			model = sFieldVal;
		}
		else if (sField == "Condition")
		{
			field = CONDITION;

			// Convert the string to the enum for performance
			if (sFieldVal == "fair")
				condition = organ::Condition::FAIR;
			else if (sFieldVal == "good")
				condition = organ::Condition::GOOD;
			else if (sFieldVal == "excellent")
				condition = organ::Condition::EXCELLENT;
			else
			{
				// If no matching condition is found, throw an exception
				std::string error = "Unknow Condition: " + sFieldVal;
				throw std::exception(error.c_str());
			}

		}
		else if (sField == "Leslie")
		{
			field = LESLIE;

			// LESLIE is a boolean, and can be "yes" or something else:
			// "yes"			==> true
			// anything else	==> false
			leslie = sFieldVal == "yes";

		}
		else
		{
			// If no matching field is found, throw an exception
			std::string error = "Unknow Field: " + sField;
			throw std::exception(error.c_str());
		}

		// Get the comparison operator char
		// It's the first and only char of the operator capture group
		comp = m[3].str()[0];

		// Convert the captured value string to a float
		comp_val = std::stof(m[4]);
	}
}