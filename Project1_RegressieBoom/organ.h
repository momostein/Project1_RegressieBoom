#pragma once
#include <string>

namespace organ
{
	using namespace std;
	enum Condition
	{
		Fair,
		Good,
		Excellent
	};

	struct Organ
	{
		string model;
		Condition condition;
		bool leslie;

		int price;
	};
}
