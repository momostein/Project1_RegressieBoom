#include <iostream>

#include "organ.h"

void organ::print(const Organ & organ)
{
	// Print the organ
	cout << "Organ:" << endl;
	cout << "\tModel: " << organ.model << endl;

	cout << "\tCondition: ";
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

	cout << "\tLeslie: " << boolalpha << organ.leslie << endl;
}
