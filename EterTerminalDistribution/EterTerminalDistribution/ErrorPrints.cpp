#include "ErrorPrints.h"

void ErrorMesageHuricane(CommonErrors message)
{
	switch (message)
	{
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Line.. Chosen line is out of bounds\n";
		return;
	case CommonErrors::INVALID_LINE_TYPE:
		std::cout << "ERR: Invalid Line Type.. Only accepting C for columns and R for rows..\n";
		return;
	case CommonErrors::INCOMPLETE_LINE_STRUCTURE:
		std::cout << "ERR: Invalid Line Structure.. Selected Line has empty spaces..\n";
		return;
	case CommonErrors::INVALID_DIRECTION:
		std::cout << "ERR: Invalid Direction.. Only accepting U and D for columns and L and R for rows..\n";
		return;
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Invalid Hurricane Usage.. Can't use hurricane on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageWhirlpool(CommonErrors message) {
	switch (message)
	{
	case CommonErrors::INVALID_LINE_TYPE:
		std::cout << "ERR: Invalid Line Type.. Only accepting C for columns and R for rows..\n";
		return;
	case CommonErrors::INVALID_DIRECTION:
		std::cout << "ERR: Invalid Direction.. Only accepting U and D for columns and L and R for rows..\n";
		return;
	case CommonErrors::EMPTY_STACK:
		std::cout << "ERR: Invalid space.. Chosen space must be empty..\n";
		return;
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Space.. Chosen space is out of bounds..\n";
		return;
	case CommonErrors::ADJACENT_OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Adjacent.. Adjacent spaces are out of bounds..\n";
		return;
	case CommonErrors::ADJACENT_SPACES_EMPTY:
		std::cout << "ERR: Invalid Adjacent.. One or both of the adjacents spaces are empty..\n";
		return;
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Invalid Whirlpool Usage.. Can't use hurricane on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFlame(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid slot.. Slot coordinates are out of bounds...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFire(CommonErrors message)
{
	switch (message) {
	case CommonErrors::INVALID_CARD_VALUE:
		std::cout << "ERR: Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageAsh(CommonErrors message)
{
	switch (message) {
	case CommonErrors::INVALID_CARD_VALUE:
		std::cout << "ERR: Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSpark(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Chosen coordinates out of bounds...\n";
		return;
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Spark elemental card on eter card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSquall(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Chosen coordinates out of bounds...\n";
		return;
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Squall elemental card on eter card..\n";
		return;
	case CommonErrors::EMPTY_STACK:
		std::cout << "ERR: Cannot place on empty space..\n";
		return;
	case CommonErrors::ILLUSION_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Squall elemental card on illusion..\n";
		return;
	case CommonErrors::NOT_ENEMY_CARD:
		std::cout << "ERR: Not an opponent card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageGust(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Gust elemental card on eter card..\n";
		return;
	case CommonErrors::IDENTICAL_COORDINATES:
		std::cout << "ERR: Chosen coordinates are identical to your current coordinates...\n";
		return;
	case CommonErrors::INVALID_CARD_VALUE:
		std::cout << "ERR: Can't place on top of card of greater value...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageMirage(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::NOT_ILLUSION:
		std::cout << "ERR: Chosen card position is not an illusion..\n";
		return;
	default:
		break;
	}
}

void ErrorMessagestorm(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::STACK_HEIGHT_TOO_SMALL:
		std::cout << "ERR: The stack does not have enough cards..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageTide(CommonErrors message)
{
	switch (message) {
	case CommonErrors::OUTSIDE_BOUNDS:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Tide elemental card on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageMist(CommonErrors message)
{
	switch (message) {
	case CommonErrors::ILLUSION_PROPERTY_VIOLATION:
		std::cout << "ERR: There is another active illusion..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageWave(CommonErrors message) {
	switch (message) {
	case CommonErrors::ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Wave elemental power on eter card\n";
		return;
	default:
		break;
	}
}




