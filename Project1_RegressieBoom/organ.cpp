#include <iostream>

#include "organ.h"

void organ::print(const Organ & organ)
{
	// Print the organ
	cout << "Organ:" << endl;
	cout << " - Model:\t" << organ.model << endl;

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

	cout << " - Leslie:\t" << boolalpha << organ.leslie << endl;
}
