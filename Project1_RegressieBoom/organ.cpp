#include <iostream>

#include "organ.h"

void organ::print(const Organ & organ)
{
	cout << "Organ:" << endl;

	// Model field
	cout << " - Model:\t" << organ.model << endl;

	// Condition field
	cout << " - Condition:\t";
	switch (organ.condition)
	{
	case FAIR:
		cout << "Fair";
		break;
	case GOOD:
		cout << "Good";
		break;
	case EXCELLENT:
		cout << "Excellent";
	default:
		break;
	}
	cout << endl;

	// Leslie field
	cout << " - Leslie:\t" << boolalpha << organ.leslie << endl;
}
