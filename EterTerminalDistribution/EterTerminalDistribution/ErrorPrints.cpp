#include "ErrorPrints.h"

void ErrorMesageHuricane(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Invalid Line.. Chosen line is out of bounds\n";
		return;
	case CommonErrors::_INVALID_LINE_TYPE:
		std::cout << "ERR: Invalid Line Type.. Only accepting C for columns and R for rows..\n";
		return;
	case CommonErrors::_INCOMPLETE_LINE_STRUCTURE:
		std::cout << "ERR: Invalid Line Structure.. Selected Line has empty spaces..\n";
		return;
	case CommonErrors::_INVALID_DIRECTION:
		std::cout << "ERR: Invalid Direction.. Only accepting U and D for columns and L and R for rows..\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Invalid Hurricane Usage.. Can't use hurricane on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageWhirlpool(CommonErrors _message) {
	switch (_message)
	{
	case CommonErrors::_INVALID_LINE_TYPE:
		std::cout << "ERR: Invalid Line Type.. Only accepting C for columns and R for rows..\n";
		return;
	case CommonErrors::_INVALID_DIRECTION:
		std::cout << "ERR: Invalid Direction.. Only accepting U and D for columns and L and R for rows..\n";
		return;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR: Invalid space.. Chosen space must be empty..\n";
		return;
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Invalid Space.. Chosen space is out of bounds..\n";
		return;
	case CommonErrors::_ADJACENT_OUTSIDE_BOUNDS:
		std::cout << "ERR: Invalid Adjacent.. Adjacent spaces are out of bounds..\n";
		return;
	case CommonErrors::_ADJACENT_SPACES_EMPTY:
		std::cout << "ERR: Invalid Adjacent.. One or both of the adjacents spaces are empty..\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Invalid Whirlpool Usage.. Can't use hurricane on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFlame(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Invalid slot.. Slot coordinates are out of bounds...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageFire(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_INVALID_CARD_VALUE:
		std::cout << "ERR: Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageAsh(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_INVALID_CARD_VALUE:
		std::cout << "ERR: Chosen value is invalid... Pick a card between 1 and 4..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSpark(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds...\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Spark elemental card on eter card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSquall(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds...\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Squall elemental card on eter card..\n";
		return;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR: Cannot place on empty space..\n";
		return;
	case CommonErrors::_ILLUSION_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Squall elemental card on illusion..\n";
		return;
	case CommonErrors::_NOT_ENEMY_CARD:
		std::cout << "ERR: Not an opponent card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageGust(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Gust elemental card on eter card..\n";
		return;
	case CommonErrors::_IDENTICAL_COORDINATES:
		std::cout << "ERR: Chosen coordinates are identical to your current coordinates...\n";
		return;
	case CommonErrors::_INVALID_CARD_VALUE:
		std::cout << "ERR: Can't place on top of card of greater value...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageMirage(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::_NOT_ILLUSION:
		std::cout << "ERR: Chosen card position is not an illusion..\n";
		return;
	default:
		break;
	}
}

void ErrorMessagestorm(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::_STACK_HEIGHT_TOO_SMALL:
		std::cout << "ERR: The stack does not have enough cards..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageTide(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Tide elemental card on eter card..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageMist(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_ILLUSION_PROPERTY_VIOLATION:
		std::cout << "ERR: There is another active illusion..\n";
		return;
	default:
		break;
	}
}

void ErrorMessageWave(CommonErrors _message) {
	switch (_message) {
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Wave elemental power on eter card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageSupport(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Support elemental power on eter card\n";
		return;
	case CommonErrors:: _INVALID_CARD_VALUE:
		std::cout << "ERR:Card value is too great, choose a lower value card. \n";
		return;

	default:
		break;
	}
}

void ErrorMessageCrumble(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Crumble elemental power on eter card\n";
		return;
	case CommonErrors::_INVALID_CARD_VALUE:
		std::cout << "ERR: Card value is less than 2, please choose a higher value card\n";
		return;
	case CommonErrors::_ILLUSION_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Crumble elemental power on illusion card\n";
		return;
	default:
		break;
	}
}

void ErrorMessageRock(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_NOT_ILLUSION:
		std::cout << "ERR::Chosen card is not an illusion, choose an illusion card. \n";
		return;
	default:
		break;
	}
}

void ErrorMessageFireMage1(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		break;
	case CommonErrors::_HOLE_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't search in a hole..\n";
		break;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR: The chosen stack must contain at least 2 cards..\n";
		break;
	case CommonErrors::_NO_COVERED_CARDS:
		std::cout << "ERR: You have no covered cards..\n";
		break;
	case CommonErrors::_INVALID_CARD_TYPE:
		std::cout << "ERR: Selected card is not covered by an enemy card ..\n";
		break;
	default:
		break;
	}
}

void ErrorMessageFireMage2(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_INVALID_LINE_TYPE:
		std::cout << "ERR: Only accepting C/c and L/l as line type..\n";
		break;
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		break;
	case CommonErrors::_INCOMPLETE_LINE_STRUCTURE:
		std::cout << "ERR: Selected line must have at least 3 visible cards..\n";
		break;
	case CommonErrors::_LINE_DOES_NOT_CONTAIN_COLOR:
		std::cout << "ERR: Selected line does not conatin a bisible card of your colour..\n";
		break;
	default:
		break;
	}
}

void ErrorMessageEarthMage1(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_INVALID_CARD_VALUE:
		break;
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		break;
	case CommonErrors::_NO_CARDS_OF_VALUE:
		std::cout << "ERR: You don;t own any cards of that type..\n";
		break;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR: Chosen stack can't be empty..\n";
		break;
	case CommonErrors::_NOT_ENEMY_CARD:
		std::cout << "ERR: Top card is not enemie's..\n";
		break;
	case CommonErrors::_HOLE_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't place on a hole..\n";
		break;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use Earth Mage power 1 on eter card\n";
		break;
	case CommonErrors::_ILLUSION_PROPERTY_VIOLATION:
		std::cout << "ERR: Can't use it on an illusion..\n";
		break;
	case CommonErrors::_INVALID_CARD_TYPE:
		std::cout << "ERR: Selected card does not have a value smaller than the top card..\n";
		break;
	default:
		break;
	}
}

void ErrorMessageEarthMage2(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		break;
	case CommonErrors::_POPULATED_STACK:
		std::cout << "ERR: Chosen stack is not empty..\n";
		break;
	default:
		break;
	}
}

void ErrorMessageAirMage1(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR:Card coordinates out of bounds...\n";
		return;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR:Chosen stack to move cannot be empty...\n";
		return;
	case CommonErrors::_POPULATED_STACK:
		std::cout << "ERR:Final position must be empty...\n";
		return;
	case CommonErrors::_INVALID_CARD_TYPE:
		std::cout << "ERR::Card must be of opposing colour...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageAirMage2(CommonErrors _message)
{
	switch (_message)
	{
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR: Chosen coordinates out of bounds..\n";
		break;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR: Source stack is empty..\n";
		break;
	case CommonErrors::_POPULATED_STACK:
		std::cout << "ERR: Destination stack is not empty..\n";
		break;
	default:
		break;
	}
}

void ErrorMessageWaterMage1(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_OUTSIDE_BOUND:
		std::cout << "ERR::Chosen coordinates out of bounds..\n";
		return;
	case CommonErrors::_EMPTY_STACK:
		std::cout << "ERR::Source card stack to move is empty...\n";
		return;
	case CommonErrors::_POPULATED_STACK:
		std::cout << "ERR:: Destination card stack must be empty..\n";
		return;
	case CommonErrors::_INVALID_CARD_TYPE:
		std::cout << "ERR:: Source card stack must contain an opposing colour card...\n";
		return;
	default:
		break;
	}
}

void ErrorMessageWaterMage2(CommonErrors _message)
{
	switch (_message) {
	case CommonErrors::_INVALID_LINE_TYPE:
		std::cout << "Chosen line must be paralel with source line...\n";
		return;
	case CommonErrors::_ETER_PROPERTY_VIOLATION:
		std::cout << "Cannot mirror row/column with eter card?..\n";
		return;
	default:
		break;
	}
}






