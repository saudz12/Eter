#include "InputChecking.h"

CommonErrors CheckHurricaneInput(Board& _board, uint16_t _lineCnt, LineType _type, Directions _direction)
{
	const ResizeableMatrix& matrix = _board.getMatrix();

	//valid typing
	if (_type == LineType::_INVALID_LINE_TYPE) {
		return CommonErrors::_INCOMPLETE_LINE_STRUCTURE;
	}

	//inside bounds
	if (_lineCnt < 0 || _type == LineType::TYPE_ROW && _lineCnt > _board.getLineCount() - 1 || _type == LineType::TYPE_COLUMN && _lineCnt > _board.getColCount() - 1) {
		return CommonErrors::_OUTSIDE_BOUND;
	}

	//valid direction
	if (_direction == Directions::INVALID_DIR) {
		return CommonErrors::_INVALID_DIRECTION;
	}

	if (_type == LineType::TYPE_ROW && _direction != Directions::DIR_LEFT && _direction != Directions::DIR_RIGHT || _type == LineType::TYPE_COLUMN && _direction != Directions::DIR_UP && _direction != Directions::DIR_DOWN) {
		return CommonErrors::_INVALID_DIRECTION;
	}

	//full line and no eters
	if (_type == LineType::TYPE_ROW) {
		for (const auto& stack : matrix[_lineCnt])
		{
			if (stack.empty()) {
				return CommonErrors::_INVALID_LINE_TYPE;
			}
			if (stack.back().GetIsEterCard())
			{
				return CommonErrors::_ETER_PROPERTY_VIOLATION;
			}
		}
	}
	//full column and no eters
	else {
		for (const auto& row : matrix)
		{
			if (row[_lineCnt].empty()) {
				return CommonErrors::_INCOMPLETE_LINE_STRUCTURE;
			}
			if (row[_lineCnt].back().GetIsEterCard())
			{
				return CommonErrors::_ETER_PROPERTY_VIOLATION;
			}
		}
	}

	return CommonErrors::_NO_ERRORS;
}

//incomplete. needs preference cehck - ask about it
CommonErrors CheckWhirlpool(Board& _board, uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, Preference _preference)
{
	if (_x1 != _x2 && _y1 != _y2)
		return CommonErrors::_NOT_ADJACENT;
	
	if (_board.CheckPos(_x1, _y1) != BoardErrors::_INSIDE_BOUND || _board.CheckPos(_x2, _y2) != BoardErrors::_INSIDE_BOUND) {
		return CommonErrors::_OUTSIDE_BOUND;
	}

	LineType type;
	if (_x1 == _x2)
		type = LineType::TYPE_ROW;
	else
		type = LineType::TYPE_COLUMN;

	if (!(type == LineType::TYPE_ROW && std::abs(_x2 - _x1) == 2 || type == LineType::TYPE_COLUMN && std::abs(_y2 - _y1) == 2))
		return CommonErrors::_NOT_ADJACENT;

	if (_board.CheckStackCondition((_x1 + _x2) / 2, (_y1 + _y2) / 2) != StackConditions::EMPTY)
		return CommonErrors::_NEEDS_EMPTY_SPACE;

	if (_preference == Preference::INVALID_PREFERENCE) {
		return CommonErrors::_INVALID_DIRECTION;
	}

	if (_board.CheckStackCondition(_x1, _y1) == StackConditions::ETER || _board.CheckStackCondition(_x2, _y2) == StackConditions::ETER) {
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
	}

	if (_board.CheckStackCondition(_x1, _y1) != StackConditions::POPULATED || _board.CheckStackCondition(_x2, _y2) != StackConditions::POPULATED) {
		return CommonErrors::_ADJACENT_SPACES_EMPTY;
	}

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncFlame(Board& _board, int16_t _xi, int16_t _yi, Player& _player, int16_t _val, int16_t _xp, int16_t _yp)
{
	BoardErrors tryPlace = _board.CanPlace(_xp, _yp, _val);
	if (_board.CheckPos(_xi, _yi) == BoardErrors::_OUTSIDE_BOUND|| _board.CanPlace(_xp, _yp, _val) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (!_board.ViewTop(_xi, _yi).GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncFire(Board&, int16_t cardValue) {
	if (cardValue < 1 || cardValue > 4)
		return CommonErrors::_INVALID_CARD_VALUE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAsh(Board& _board, const MinionCard& _card, int16_t _x, int16_t _y) {
	if (_card.GetValue() > 4 || _card.GetValue() < 1)
		return CommonErrors::_INVALID_CARD_VALUE;
	if (_board.CheckPos(_x,_y)==BoardErrors::_OUTSIDE_BOUND)/// bound check
		return CommonErrors::_OUTSIDE_BOUND;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSpark(Board& _board, int16_t _x1, int16_t _y1, int16_t _x2, int16_t _y2)
{

	if (_board.CheckPos(_x1, _y1) == BoardErrors::_OUTSIDE_BOUND|| _board.CheckPos(_x2, _y2) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.getCardOnPos(_x1,_y1).GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSquall(Board& _board, int16_t _x, int16_t _y,Player& _p) {
	MinionCard& Card = _board.getCardOnPos(_x,_y);
	if (_board.CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;

	if (_board.getStackOnPos(_x,_y).empty())
		return CommonErrors::_EMPTY_STACK;

	if (Card.GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	if (Card.GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;
	if (Card.GetColor() != _p.GetPlayerColor())
		return CommonErrors::_NOT_ENEMY_CARD;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncGust(Board& _board, int16_t _x1, int16_t _y1, int16_t _x2, int16_t _y2) {

	if (_board.CheckPos(_x1, _y1) == BoardErrors::_OUTSIDE_BOUND|| _board.CheckPos(_x2, _y2) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;

	if (_board.getCardOnPos(_x1,_y1).GetIsEterCard()|| _board.getCardOnPos(_x2,_y2).GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	if (!((_x1 == _x2 && std::abs(_y1 - _y2) == 1) || (_y1 == _y2) && std::abs(_x1 - _x2)))
		return CommonErrors::_IDENTICAL_COORDINATES;

	if (_board.getCardOnPos(_x1, _y1).GetValue() < _board.getCardOnPos(_x2, _y2).GetValue())
		return CommonErrors::_INVALID_CARD_VALUE;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncMirage(Board& _board, int16_t _x, int16_t _y) {
	
	if (_board.CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;

	if (_board.getCardOnPos(_x,_y).GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncStorm(Board& _board, int16_t _x, int16_t _y) {


	if (_board.CheckPos(_x,_y)==BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.getStackOnPos(_x,_y).size() < 2)
		return CommonErrors::_STACK_HEIGHT_TOO_SMALL;

	return CommonErrors::_OUTSIDE_BOUND;
}

CommonErrors checkFuncTide(Board& _board, int16_t _x1, int16_t _y1, int16_t _x2, int16_t _y2) {

	CardStack& first = _board.getStackOnPos(_x1, _y1);
	CardStack& second = _board.getStackOnPos(_x2, _y2);
	//int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (_board.CheckPos(_x1,_y1)==BoardErrors::_OUTSIDE_BOUND || _board.CheckPos(_x2,_y2)==BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;

	if (first.back().GetIsEterCard() || second.back().GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncMist(Board& _board, Player& _p, int16_t _x, int16_t _y, MinionCard& _card) {

	if (!_p.GetIllusionUsage() || _p.GetIllusionCard() == nullptr)
		return CommonErrors::_ILLUSION_PROPERTY_VIOLATION;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWave(Board& _board, int16_t _x1, int16_t _y1, MinionCard) {
	//nothing else to add
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncBlizzard(Line&) {
	//nothing to add
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterfall(Board&, int16_t) {
	//nothing to add
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSupport(Board& _board, int16_t _x, int16_t _y) {
	MinionCard& card = _board.getCardOnPos(_x, _y);

	if (card.GetIsEterCard()) 
	{
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
	}
	if (card.GetValue() > 3)	//check according to game rules
	{
		return CommonErrors::_INVALID_CARD_VALUE;
	}
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncEarthquake(Board&) {
	//nothing to add
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncCrumble(Board& _board, int16_t _x, int16_t _y) {
	MinionCard& card = _board.getCardOnPos(_x, _y);
	if (card.GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
	if (card.GetIsIllusionCard())
		return CommonErrors::_ILLUSION_PROPERTY_VIOLATION;
	if (card.GetValue() < 2)	//check according to game rules
		return CommonErrors::_INVALID_CARD_VALUE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncBorder(Board& _board, int16_t _x, int16_t _y) {

	if (_board.isMatMaxSize())
		return CommonErrors::_MAX_BOARD_SIZE;

	if (abs(_x) > _board.getMaxSize()|| abs(_y) > _board.getMaxSize())
		return CommonErrors::_OUTSIDE_BOUND;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAvalanche(Board& _board, int16_t _x1, int16_t _y1, int16_t _x2, int16_t _y2, Directions _direction) {
	
	if (_board.CheckPos(_x1, _y1) == BoardErrors::_OUTSIDE_BOUND || _board.CheckPos(_x2, _y2) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;

	if (_direction == Directions::INVALID_DIR)
		return CommonErrors::_INVALID_DIRECTION;

	if (_board.CheckStackCondition(_x1, _y1) != StackConditions::POPULATED || _board.CheckStackCondition(_x2, _y2) != StackConditions::POPULATED)
		return CommonErrors::_EMPTY_STACK;
	if (Board::CheckAdjacent(_x1, _y1, _x2, _y2) != AdjacentType::NEIGHBOURING)
		return CommonErrors::_NOT_ADJACENT;

	int16_t xD = -1, yD = -1; //  xD

	switch (_direction)
	{
	case Directions::DIR_LEFT:
		if (_board.CheckStackCondition(_x1, std::min(_y1, _y2)) != StackConditions::EMPTY) {
			xD = _x1;
			yD = std::min(_y1, _y2);
		}
		break;
	case Directions::DIR_RIGHT:
		if (_board.CheckStackCondition(_x1, std::max(_y1, _y2)) != StackConditions::EMPTY) {
			xD = _x1;
			yD = std::max(_y1, _y2);
		}
		break;
	case Directions::DIR_UP:
		if (_board.CheckStackCondition(std::min(_x1, _x2), _y2) != StackConditions::EMPTY) {
			xD = std::min(_x1, _x2);
			yD = _y2;
		}
		break;
	case Directions::DIR_DOWN:
		if (_board.CheckStackCondition(std::max(_x1, _x2), _y2) != StackConditions::EMPTY) {
			xD = std::min(_x1, _x2);
			yD = _y2;
		}
		break;
	}

	if(xD != -1 && yD != -1)
		return CommonErrors::_NO_ERRORS;
	return CommonErrors::_EMPTY_STACK;
}

CommonErrors checkFuncRock(Board& _board, int16_t _x, int16_t _y, MinionCard&) {
	MinionCard illusionCard =_board.getCardOnPos(_x, _y);
	if (!illusionCard.GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;	
	return CommonErrors::_NO_ERRORS;
}

//i think it's bad practice to select by coordonates --> change covered set to list of pointers which will be printed like a list - select then which 
CommonErrors checkFuncFireMage1(Board& _board, Player& _player, int16_t _x, int16_t _y, int16_t _pos) {
	if (_board.CheckPos(_x,_y)==BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_x, _y) == StackConditions::HOLE)
		return CommonErrors::_HOLE_PROPERTY_VIOLATION;
	if (_board.CheckStackCondition(_x, _y) == StackConditions::EMPTY || _pos == 0)
		return CommonErrors::_EMPTY_STACK;
	if (_player.CheckCoveredPopulation())
		return CommonErrors::_NO_COVERED_CARDS;
	if (_player.CheckCoveredProperty(_x, _y, _pos-1) == false)
		return CommonErrors::_INVALID_CARD_TYPE;

	return CommonErrors::_NO_ERRORS;
}	

CommonErrors checkFuncFireMage2(Board& _board, Player& _player, int16_t _line, char _type) {
	LineType type = GetLineType(_type);
	if (type != LineType::TYPE_ROW && type != LineType::TYPE_COLUMN)
		return CommonErrors::_INVALID_LINE_TYPE;
	if (_line < 0 || (type == LineType::TYPE_ROW && _line >= _board.getRowCount()) || (type == LineType::TYPE_COLUMN && _line >= _board.getColCount()))
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.GetNrOfCardsOnLine(_line, type) < 3)
		return CommonErrors::_INCOMPLETE_LINE_STRUCTURE;
	if (_board.LineContainsColour(_line, GetLineType(_type), _player.GetPlayerColor()) == false)
		return CommonErrors::_LINE_DOES_NOT_CONTAIN_COLOR;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncEarthMage1(Board& _board, Player& _caster, int16_t _x, int16_t _y, int16_t _val)
{
	if (_val < 0 || _val > 3)
		return CommonErrors::_INVALID_CARD_VALUE;

	if (_board.CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;

	if (!_caster.HasCardOfValue((uint16_t)_val))
		return CommonErrors::_NO_CARDS_OF_VALUE;

	const auto& selected = _board.getStackOnPos(_x, _y);
	if (selected.empty())
		return CommonErrors::_EMPTY_STACK;

	const MinionCard& top = selected.back();
	if (top.GetColor() == _caster.GetPlayerColor())
		return CommonErrors::_NOT_ENEMY_CARD;
	if (top.CheckIsHole())
		return CommonErrors::_HOLE_PROPERTY_VIOLATION;
	if (top.GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
	if (top.GetIsIllusionCard())
		return CommonErrors::_ILLUSION_PROPERTY_VIOLATION;
	if (top.GetValue() <= _val)
		return CommonErrors::_INVALID_CARD_TYPE;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncEarthMage2(Board& _board, int16_t _x, int16_t _y) {
	if (_board.CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_x, _y) == StackConditions::POPULATED)
		return CommonErrors::_POPULATED_STACK;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAirMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD) {
	if (_board.CheckPos(_xS, _yS) == BoardErrors::_OUTSIDE_BOUND || _board.CheckPos(_xD, _yD) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_xS, _yS) != StackConditions::POPULATED)
		return CommonErrors::_EMPTY_STACK;
	if (_board.CheckStackCondition(_xD, _yD) != StackConditions::EMPTY)
		return CommonErrors::_POPULATED_STACK;
	if (_board.ViewTop(_xS, _yS).GetColor() == _color)
		return CommonErrors::_INVALID_CARD_TYPE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAirMage2(Board& _board, int16_t _x, int16_t _y,Colours _color) {
	if (_board.CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_x, _y) != StackConditions::EMPTY)
		return CommonErrors::_POPULATED_STACK;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD) {
	if (_board.CheckPos(_xS, _yS) == BoardErrors::_OUTSIDE_BOUND || _board.CheckPos(_xD, _yD) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_xS, _yS) != StackConditions::POPULATED)
		return CommonErrors::_EMPTY_STACK;
	if (_board.CheckStackCondition(_xD, _yD) != StackConditions::EMPTY)
		return CommonErrors::_POPULATED_STACK;
	if (_board.ViewTop(_xS, _yS).GetColor() != _color)
		return CommonErrors::_INVALID_CARD_TYPE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterMage2(Board& _board, char _margin)
{
	int16_t finish;
	int16_t count = 0;

	MarginType marginType = GetMargin(_margin);

	if (marginType == MarginType::INVALID_MARGIN)
		return CommonErrors::_INVALID_LINE_TYPE;

	if (marginType == MarginType::MARGIN_TOP || marginType == MarginType::MARGIN_BOT) {
		finish = _board.getColCount();
	}
	else {
		finish = _board.getRowCount();
	}

	auto quickCheck = [&](int16_t& x, int16_t& y, int16_t i) {
		if (marginType == MarginType::MARGIN_TOP) {
			x = 0;
			y = i;
		}
		else if (marginType == MarginType::MARGIN_BOT) {
			x = _board.getRowCount() - 1;
			y = i;
		}
		else if (marginType == MarginType::MARGIN_LEFT) {
			x = i;
			y = 0;
		}
		else {
			x = i;
			y = _board.getColCount() - 1;
		}
	};

	int16_t x;
	int16_t y;

	for (int16_t i = 0; i < finish; i++) {
		quickCheck(x, y, i);

		StackConditions stackCondition = _board.CheckStackCondition(x, y);
		
		/*if (stackCondition == StackConditions::_HOLE) {
			return CommonErrors::_HOLE_PROPERTY_VIOLATION;
		}*/
		
		if (stackCondition == StackConditions::POPULATED) {
			count++;
			if (_board.CheckTopIsEter(x, y))
				return CommonErrors::_ETER_PROPERTY_VIOLATION;
		}
	}

	if (count < 3)
		return CommonErrors::_INVALID_LINE_TYPE;
	return CommonErrors::_NO_ERRORS;
}


