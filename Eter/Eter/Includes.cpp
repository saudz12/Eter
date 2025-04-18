#include "Includes.h"

Colours GetColour(char c)
{
	switch (toupper(c))
	{
	case 'R':
		return Colours::RED;
	case 'B':
		return Colours::BLUE;
	default:
		return Colours::INVALID_COL;
	}
}


char GetColour(Colours c)
{
	switch (c)
	{
	case Colours::RED:
		return 'R';
	case Colours::BLUE:
		return 'B';
	default:
		return '-';
	}
}

Colours GetOppositeColour(Colours c)
{
	switch (c)
	{
	case Colours::RED:
		return Colours::BLUE;
	case Colours::BLUE:
		return Colours::RED;
	default:
		return Colours::INVALID_COL;
	}
}

LineType GetLineType(char t)
{
	switch (toupper(t))
	{
	case 'R':
		return LineType::TYPE_ROW;
	case 'C':
		return LineType::TYPE_COLUMN;
	default:
		return LineType::_INVALID_LINE_TYPE;
	}
}

Directions GetDirection(char d) {
	switch (toupper(d))
	{
	case 'L':
		return Directions::DIR_LEFT;
	case 'R':
		return Directions::DIR_RIGHT;
	case 'U':
		return Directions::DIR_UP;
	case 'D':
		return Directions::DIR_DOWN;
	default:
		return Directions::INVALID_DIR;
	}
}

std::ostream& operator<<(std::ostream& os, const Colours& col) {
	os << GetColour(col);
	return os;
}

std::ostream& operator<<(std::ostream& out, const MinionCard& card)
{
	//std::string cardColour = card.GetColor() == Colours::RED ? "R" : "B";
	if (card.GetCardType() == CardType::HoleCard)
		out << " H ";
	else if (card.GetIsEterCard())
		out << "E:" << card.GetColor();
	else if (card.GetIsIllusionCard())
		out << "I:" << card.GetColor();
	else
		out << card.GetValue() << ":" << card.GetColor();
	return out;
}


QDebug operator<<(QDebug debug, const Colours& col)
{
	QDebugStateSaver saver(debug); // Saves the current state of QDebug (e.g., formatting)
	debug.nospace() << GetColour(col);
	return debug;
}

QDebug operator<<(QDebug debug, const MinionCard& card)
{
	QDebugStateSaver saver(debug);
	if (card.GetCardType() == CardType::HoleCard)
		debug.nospace() << " H:";
	else if (card.GetIsEterCard())
		debug.nospace() << "E:" << card.GetColor();
	else if (card.GetIsIllusionCard())
		debug.nospace() << "I:" << card.GetColor();
	else
		debug.nospace() << card.GetValue() << ":" << card.GetColor();
	return debug;
}