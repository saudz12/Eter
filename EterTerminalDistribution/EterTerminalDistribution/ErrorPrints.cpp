#include "ErrorPrints.h"

void ErrorMesageHuricane(int message)
{
	switch (message)
	{
	case OUTSIDE_BOUNDS:
		return;
	case INVALID_LINE_TYPE:
		std::cout << "ERR: Invalid Line Type.. Only accepting C for columns and R for rows..\n";
		return;
	case INVALID_LINE_STRUCTURE:
		std::cout << "ERR: Invalid Line Structure.. Selected Line has empty spaces..\n";
		return;
	case INVALID_DIRECTION:
		std::cout << "ERR: Invalid Direction.. Only accepting U and D for columns and L and R for rows..\n";
		return;
	case ETER_PROPERTY_VIOALTION:
		std::cout << "ERR: Invalid Hurricane Usage.. Can't use hurricane on eter card..\n";
		return;
	default:
		break;
	}
}
