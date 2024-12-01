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
		std::cout << "ERR:Invalid slot.. Slot coordinates are out of bounds...\n";
		return;
	case FAILED_FLAME_CARD_PLACEMENT:
		std::cout << "ERR:Failed to place minion card with Flame elemental card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFire(int message)
{
	switch (message) {
	case INVALID_CARD_VALUE:
		std::cout << "ERR:Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageAsh(int message)
{
	switch (message) {
	case INVALID_CARD_VALUE:
		std::cout << "ERR:Chosen value is invalid... Pick a card between 1 and 4..\n";
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
	case ETER_PROPERTY_VIOALTION:
		std::cout << "Can't use Spark elemental card on eter card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSquall(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Chosen coordinates out of bounds...\n";
		return;
	case ETER_PROPERTY_VIOALTION:
		std::cout << "Can't use Squall elemental card on eter card..\n";
		return;
	case EMPTY_SPACE:
		std::cout << "Cannot place on empty space..\n";
		return;
	case FAILED_ON_ILLUSION:
		std::cout << "Can't use Squall elemental card on illusion..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageGust(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Chosen coordinates out of bounds..\n";
		return;
	case ETER_PROPERTY_VIOALTION:
		std::cout << "Can't use Gust elemental card on eter card..\n";
		return;
	case IDENTICAL_COORDINATES:
		std::cout << "Chosen coordinates are identical to your current coordinates...\n";
		return;
	case VALUE_TOO_GREAT:
		std::cout << "Can't place on top of card of greater value...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageMirage(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Chosen coordinates out of bounds..\n";
		return;
	case NOT_ILLUSION:
		std::cout << "Chosen card position is not an illusion..\n";
		return;
	default:
		break;
	}
}

void ErrorMessagestorm(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Chosen coordinates out of bounds..\n";
		return;
	case INSUFFICIENT_STACK_HEIGHT:
		std::cout << "The stack does not have enough cards..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageTide(int message)
{
	switch (message) {
	case OUTSIDE_BOUNDS:
		std::cout << "Chosen coordinates out of bounds..\n";
		return;
	case ETER_PROPERTY_VIOALTION:
		std::cout << "Can't use Tide elemental card on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageMist(int message)
{
	switch (message) {
	case FAILED_MIST_CARD_PLACEMENT:
		std::cout << "Failed to place card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageWave(int message) {
	switch (message) {
	case ETER_PROPERTY_VIOALTION:
		std::cout << "Can't use Wave elemental power on eter card\n";
		return;
	default:
		break;
	}
}




