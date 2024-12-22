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
		return CommonErrors::NOT_ADJACENT;
	
	if (_board.CheckPos(_x1, _y1) != BoardErrors::_INSIDE_BOUND || _board.CheckPos(_x2, _y2) != BoardErrors::_INSIDE_BOUND) {
		return CommonErrors::_OUTSIDE_BOUND;
	}

	LineType type;
	if (_x1 == _x2)
		type = LineType::TYPE_ROW;
	else
		type = LineType::TYPE_COLUMN;

	if (!(type == LineType::TYPE_ROW && std::abs(_x2 - _x1) == 2 || type == LineType::TYPE_COLUMN && std::abs(_y2 - _y1) == 2))
		return CommonErrors::NOT_ADJACENT;

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

CommonErrors checkFuncFlame(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const MinionCard& CardToBePlaced, Player& p)
{
	int16_t lines = board.getLineCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines || y1 < 0 || y1 > cols)
		return CommonErrors::_OUTSIDE_BOUND;
	/*if (board.setPos(x2, y2, CardToBePlaced, p) == 1)
		return FAILED_FLAME_CARD_PLACEMENT;*/
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncFire(Board&, int16_t cardValue) {
	if (cardValue < 1 || cardValue > 4)
		return CommonErrors::_INVALID_CARD_VALUE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAsh(Board& board, const MinionCard& card, int16_t x, int16_t y) {
	int16_t lines = board.getLineCount(), cols = board.getColCount();
	if (card.GetValue() > 4 || card.GetValue() < 1)
		return CommonErrors::_INVALID_CARD_VALUE;
	if (x < 0 || x > lines || y < 0 || y > cols)/// bound check
		return CommonErrors::_OUTSIDE_BOUND;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSpark(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t lines = board.getRowCount(), cols = board.getColCount();
	ResizeableMatrix& matrix = board.getMatrix();
	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols)
		return CommonErrors::_OUTSIDE_BOUND;
	if (matrix[x1][y1].back().GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSquall(Board& board, int16_t x1, int16_t y1,Player p) {
	int16_t lines = board.getRowCount(), cols = board.getColCount();
	ResizeableMatrix& matrix = board.getMatrix();

	if (x1 < 0 || x1 > lines)
		return CommonErrors::_OUTSIDE_BOUND;
	if (y1 < 0 || y1 > cols)
		return CommonErrors::_OUTSIDE_BOUND;

	if (matrix[x1][y1].empty())
		return CommonErrors::_EMPTY_STACK;

	if (matrix[x1][y1].back().GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	if (matrix[x1][y1].back().GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;
	if (matrix[x1][y1].back().GetColor() != p.GetPlayerColor())
		return CommonErrors::_NOT_ENEMY_CARD;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncGust(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	ResizeableMatrix& matrix = board.getMatrix();
	int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols) // bound check
		return CommonErrors::_OUTSIDE_BOUND;

	if (matrix[x1][y1].back().GetIsEterCard() || matrix[x2][y2].back().GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	if (!((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2) && std::abs(x1 - x2)))
		return CommonErrors::_IDENTICAL_COORDINATES;

	if (!(matrix[x1][y1].back().GetValue() > matrix[x2][y2].back().GetValue()))
		return CommonErrors::_INVALID_CARD_VALUE;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncMirage(Board& board, int16_t x1, int16_t y1, const MinionCard&) {
	ResizeableMatrix& matrix = board.getMatrix();
	int16_t lines = board.getRowCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines ||
		y1 < 0 || y1 > cols) //bound check
		return CommonErrors::_OUTSIDE_BOUND;

	if (!matrix[x1][y1].back().GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncStorm(Board& board, int16_t x, int16_t y) {

	ResizeableMatrix& matrix = board.getMatrix();
	int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x < 0 || x > lines ||
		y < 0 || y > cols) //bound check
		return CommonErrors::_OUTSIDE_BOUND;
	if (matrix[x][y].size() < 2)
		return CommonErrors::_STACK_HEIGHT_TOO_SMALL;

	return CommonErrors::_OUTSIDE_BOUND;
}

CommonErrors checkFuncTide(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {

	CardStack& first = board.getStackOnPos(x1, y1);
	CardStack& second = board.getStackOnPos(x2, y2);
	int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols) // bound check
		return CommonErrors::_OUTSIDE_BOUND;

	if (first.back().GetIsEterCard() || second.back().GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncMist(Board& _board, Player& _p, int16_t _x, int16_t _y, MinionCard& _card) {

	/*if (board.setPos(x, y, card, p) == 1)
		return 1;*/
	if (!_p.GetIllusionUsage() || _p.GetIllusionCard() == nullptr)
		return CommonErrors::_ILLUSION_PROPERTY_VIOLATION;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWave(Board& _board, int16_t _x1, int16_t _y1, MinionCard) {
	/*ResizeableMatrix matrix = board.getMatrix();
	if (matrix[x1][y1].back().GetIsEterCard())
		return -2;*/
	//nothing else to add
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncBlizzard(Line&) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterfall(Board&, int16_t) {
	//nothing to add
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSupport(Board& board, int16_t x, int16_t y) {
	ResizeableMatrix& matrix = board.getMatrix();
	int CardValue = matrix[x][y].back().GetValue();

	if (matrix[x][y].back().GetIsEterCard()) 
	{
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
	}
	if (CardValue > 3)	//check according to game rules
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
	ResizeableMatrix& matrix = _board.getMatrix();
	int CardValue = matrix[_x][_y].back().GetValue();
	if (matrix[_x][_y].back().GetIsEterCard())
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
	if (matrix[_x][_y].back().GetIsIllusionCard())
		return CommonErrors::_ILLUSION_PROPERTY_VIOLATION;
	if (CardValue < 2)	//check according to game rules
		return CommonErrors::_INVALID_CARD_VALUE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncBorder(Board&, int16_t, int16_t) {
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
		return CommonErrors::NOT_ADJACENT;

	int16_t xD = -1, yD = -1;

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
	if (_x < 0 || _y < 0 || _x >= _board.getRowCount() || _y >= _board.getColCount())
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

	if (_x < 0 || _y < 0 || _x >= _board.getRowCount() || _y >= _board.getColCount())
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
	if (_x < 0 || _y < 0 || _x >= _board.getRowCount() || _y >= _board.getColCount())
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


