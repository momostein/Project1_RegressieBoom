#pragma once
#include <string>
#include <vector>

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
		int price;

		Organ() : price(-1) {};

		Organ(
			const string& model,
			Condition condition,
			bool leslie,
			int price = -1
		)
			: model(model)
			, condition(condition)
			, leslie(leslie)
			, price(price)
		{
		};

	};

	void print(const Organ& organ);

	
}
