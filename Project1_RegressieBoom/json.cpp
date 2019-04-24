#include <ctype.h>

#include "json.h"

namespace json
{
	char seek(char c, std::ifstream & fileStream)
	{
		while (true)
		{
			// Throw an Exception if the end-of-file is reached
			if (fileStream.eof())
			{
				std::string error = "EOF reached while seeking for ";
				error += c;
				throw std::exception(error.c_str());
			}

			if (fileStream.get() == c)
				return c;
		}
	}

	char seek(const std::string & chars, std::ifstream & fileStream)
	{
		while (true)
		{
			// Throw an Exception if the end-of-file is reached
			if (fileStream.eof())
			{
				std::string error = "EOF reached while seeking for " + chars;
				throw std::exception(error.c_str());
			}

			// Read the next character from the file
			char c = fileStream.get();

			// Check if the character is in the string
			size_t found = chars.find(c);
			if (found != std::string::npos)
				return c;

		}

	}

	char seekNonWS(std::ifstream & fileStream)
	{
		while (true)
		{
			// Throw an Exception if the end-of-file is reached
			if (fileStream.eof())
				throw std::exception("EOF reached while seeking for a non-whitespace character");

			// Read the next character from the file
			char c = fileStream.get();

			// Check if the character is not whitespace
			if (isspace(c))
				return c;
		}
	}

	std::string parseUntill(char c, std::ifstream & fileStream)
	{
		std::string out = "";
		while (true)
		{
			// Throw an Exception if the end-of-file is reached
			if (fileStream.eof())
			{
				std::string error = "EOF reached while parsing untill ";
				error += c;
				throw std::exception(error.c_str());
			}

			char new_c = fileStream.get();

			if (new_c == c)
				return out;

			out += new_c;

		}
	}
}