#pragma once
#include <string>

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
}
