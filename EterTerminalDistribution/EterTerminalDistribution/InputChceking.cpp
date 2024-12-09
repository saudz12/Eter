#include "InputChecking.h"

CommonErrors CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction)
{
	const ResizeableMatrix& matrix = board.getMatrix();

	//valid typing
	if (type != ID_ROW && type != ID_COLUMN) {
		return CommonErrors::_INCOMPLETE_LINE_STRUCTURE;
	}

	//insine bounds
	if (lineCnt < 0 || type == ID_ROW && lineCnt > board.getLineCount() - 1 || type == ID_COLUMN && lineCnt > board.getColCount() - 1) {
		return CommonErrors::_OUTSIDE_BOUND;
	}

	//valid direction
	if (type == ID_ROW && direction != DIR_LEFT && direction != DIR_RIGHT || type == ID_COLUMN && direction != DIR_UP && direction != DIR_DOWN) {
		return CommonErrors::_INVALID_DIRECTION;
	}

	//full line and no eters
	if (type == ID_ROW) {
		for (auto& stack : matrix[lineCnt])
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
	if (type == ID_COLUMN) {
		for (auto& row : matrix)
		{
			if (row[lineCnt].empty()) {
				return CommonErrors::_INCOMPLETE_LINE_STRUCTURE;
			}
			if (row[lineCnt].back().GetIsEterCard())
			{
				return CommonErrors::_ETER_PROPERTY_VIOLATION;
			}
		}
	}

	return CommonErrors::_NO_ERRORS;
}

//incomplete. needs preference cehck - ask about it
CommonErrors CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference)
{
	ResizeableMatrix& matrix = board.getMatrix();

	int ratioX = (linetype == ID_ROW) ? 0 : 1;
	int ratioY = (linetype == ID_ROW) ? 1 : 0;

	if (linetype != ID_ROW && linetype != ID_COLUMN) {
		return CommonErrors::_INVALID_LINE_TYPE;
	}

	if (linetype == ID_ROW && (preference != DIR_LEFT || preference != DIR_RIGHT) || linetype == ID_COLUMN && (preference != DIR_UP || preference != DIR_DOWN)) {
		return CommonErrors::_INVALID_DIRECTION;
	}
	if (!matrix[x][y].empty()) {
		return CommonErrors::_EMPTY_STACK;
	}

	if ((x < 0 || x >= board.getRowCount()) || (y < 0 || y >= board.getColCount())) {
		return CommonErrors::_OUTSIDE_BOUND;
	}

	//check if the adjacent spaces are out of bounds
	if (linetype == ID_ROW) {
		if (y - 1 < 0 || y + 1 >= board.getColCount())
		{
			return CommonErrors::_ADJACENT_OUTSIDE_BOUNDS;
		}
	}
	else {
		if (x - 1 < 0 || x + 1 >= board.getRowCount())
		{
			return CommonErrors::_ADJACENT_OUTSIDE_BOUNDS;
		}
	}

	//check if the adjancent spaces are empty
	if (matrix[x - ratioX][y - ratioY].empty() || matrix[x + ratioX][y + ratioY].empty())
	{
		return CommonErrors::_ADJACENT_SPACES_EMPTY;
	}
	//check if one of the adjancent spaces is an eter card
	if (matrix[x - ratioX][y - ratioY].back().GetIsEterCard() || matrix[x + ratioX][y + ratioY].back().GetIsEterCard())
	{
		return CommonErrors::_ETER_PROPERTY_VIOLATION;
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

CommonErrors checkFuncMist(Board& board, Player& p, int16_t x, int16_t y, MinionCard& card) {

	/*if (board.setPos(x, y, card, p) == 1)
		return 1;*/
	if (!p.GetIllusionUsage() || p.GetIllusionCard() == nullptr)
		return CommonErrors::_ILLUSION_PROPERTY_VIOLATION;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWave(Board& board, int16_t x1, int16_t y1, MinionCard) {
	/*ResizeableMatrix matrix = board.getMatrix();
	if (matrix[x1][y1].back().GetIsEterCard())
		return -2;*/

	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncBlizzard(Line&) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterfall(Board&, int16_t) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncSupport(Board&, int16_t, int16_t) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncEarthquake(Board&) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncCrumble(Board&, int16_t, int16_t) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncBorder(Board&, int16_t, int16_t) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAvalanche(Board&, int16_t, int16_t, int16_t, int16_t, char) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncRock(Board&, int16_t, int16_t, MinionCard&) {
	return CommonErrors::_NO_ERRORS;
}

//i think it's bad practice to select by coordonates --> change covered set to list of pointers which will be printed like a list - select then which 
CommonErrors checkFuncFireMage1(Board& _board, Player& _player, int16_t _x, int16_t _y, int16_t _pos) {
	if (_x < 0 || _y < 0 || _x >= _board.getRowCount() || _y >= _board.getColCount())
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_x, _y) == StackConditions::_HOLE)
		return CommonErrors::_HOLE_PROPERTY_VIOLATION;
	if (_board.CheckStackCondition(_x, _y) == StackConditions::_EMPTY || _pos == 0)
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
	if (_board.CheckStackCondition(_x, _y) == StackConditions::_POPULATED)
		return CommonErrors::_POPULATED_STACK;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAirMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD) {
	if (_board.CheckPos(_xS, _yS) == BoardErrors::_OUTSIDE_BOUND || _board.CheckPos(_xD, _yD) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (_board.CheckStackCondition(_xS, _yS) != StackConditions::_POPULATED)
		return CommonErrors::_EMPTY_STACK;
	if (_board.CheckStackCondition(_xD, _yD) != StackConditions::_EMPTY)
		return CommonErrors::_POPULATED_STACK;
	if (_board.ViewTop(_xS, _yS).GetColor() == _color)
		return CommonErrors::_INVALID_CARD_TYPE;
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncAirMage2(Board&, int16_t, int16_t) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterMage1(Board&, Player&) {
	return CommonErrors::_NO_ERRORS;
}

CommonErrors checkFuncWaterMage2(Board& board, Colours color, Player& pl) {
	return CommonErrors::_NO_ERRORS;
}

