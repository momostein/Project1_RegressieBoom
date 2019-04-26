#pragma once
#include <string>

// TODO: Better comments

namespace organ
{
	using namespace std;
	enum Condition
	{
		FAIR,
		GOOD,
		EXCELLENT,
	};

	struct Organ
	{
		string model;
		Condition condition;
		bool leslie;
	};

	void print(const Organ& organ);
}
