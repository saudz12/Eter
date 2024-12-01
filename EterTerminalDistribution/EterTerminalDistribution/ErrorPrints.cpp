#include "ErrorPrints.h"

void ErrorMesageHuricane(int message)
{
	switch (message)
	{
	case OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Line.. Chosen line is out of bounds\n";
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

void ErrorMessageWhirlpool(int message) {
	switch (message)
	{
	case INVALID_LINE_TYPE:
		std::cout << "ERR: Invalid Line Type.. Only accepting C for columns and R for rows..\n";
		return;
	case INVALID_DIRECTION:
		std::cout << "ERR: Invalid Direction.. Only accepting U and D for columns and L and R for rows..\n";
		return;
	case EMPTY_SPACE:
		std::cout << "ERR: Invalid space.. Chosen space must be empty..\n";
		return;
	case OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Space.. Chosen space is out of bounds..\n";
		return;
	case ADJACENT_OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Adjacent.. Adjacent spaces are out of bounds..\n";
		return;
	case ADJACENT_SPACES_EMPTY:
		std::cout << "ERR: Invalid Adjacent.. One or both of the adjacents spaces are empty..\n";
		return;
	case ETER_PROPERTY_VIOALTION:
		std::cout << "ERR: Invalid Whirlpool Usage.. Can't use hurricane on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFlame(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Invalid slot.. Slot coordinates are out of bounds...\n";
		return;
	case FAILED_FLAME_CARD_PLACEMENT:
		std::cout << "Failed to place minion card with Flame elemental card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFire(int message)
{
	switch (message) {
	case INVALID_CARD_VALUE:
		std::cout << "Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageAsh(int message)
{
	switch (message) {
	case INVALID_CARD_VALUE:
		std::cout << "Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSpark(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Chosen coordinates out of bounds...\n";
		return;
	case FAILED_SPARK_CARD_PLACEMENT:
		std::cout << "Can't use Spark elemental card on eter card\n";
		return;
	default:
		break;
	}
}



