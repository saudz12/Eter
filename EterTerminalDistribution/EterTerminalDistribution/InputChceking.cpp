#include "InputChecking.h"

int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction)
{
	const ResizeableMatrix& matrix = board.getMatrix();

	//valid typing
	if (type != ID_ROW && type != ID_COLUMN) {
		return INVALID_LINE_TYPE;
	}

	//insine bounds
	if (lineCnt < 0 || type == ID_ROW && lineCnt > board.getLineCount() - 1 || type == ID_COLUMN && lineCnt > board.getColCount() - 1) {
		return OUTSIDE_BOUNDS;
	}

	//valid direction
	if (type == ID_ROW && direction != DIR_LEFT && direction != DIR_RIGHT || type == ID_COLUMN && direction != DIR_UP && direction != DIR_DOWN) {
		return INVALID_DIRECTION;
	}

	//full line and no eters
	if (type == ID_ROW) {
		for (auto& stack : matrix[lineCnt])
		{
			if (stack.empty()) {
				return INVALID_LINE_STRUCTURE;
			}
			if (stack.back().GetIsEterCard())
			{
				return ETER_PROPERTY_VIOALTION;
			}
		}
	}
	if (type == ID_COLUMN) {
		for (auto& row : matrix)
		{
			if (row[lineCnt].empty()) {
				return INVALID_LINE_STRUCTURE;
			}
			if (row[lineCnt].back().GetIsEterCard())
			{
				return ETER_PROPERTY_VIOALTION;
			}
		}
	}

	return NO_ERRORS;
}

//incomplete. needs preference cehck - ask about it
int CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference)
{
	ResizeableMatrix& matrix = board.getMatrix();

	int ratioX = (linetype == ID_ROW) ? 0 : 1;
	int ratioY = (linetype == ID_ROW) ? 1 : 0;

	if (linetype != ID_ROW && linetype != ID_COLUMN) {
		return INVALID_LINE_TYPE;
	}

	if (linetype == ID_ROW && (preference != DIR_LEFT || preference != DIR_RIGHT) || linetype == ID_COLUMN && (preference != DIR_UP || preference != DIR_DOWN)) {
		return INVALID_DIRECTION;
	}
	if (!matrix[x][y].empty()) {
		return EMPTY_SPACE;
	}

	if ((x < 0 || x >= board.getRowCount()) || (y < 0 || y >= board.getColCount())) {
		return OUTSIDE_BOUNDS;
	}

	//check if the adjacent spaces are out of bounds
	if (linetype == ID_ROW) {
		if (y - 1 < 0 || y + 1 >= board.getColCount())
		{
			return ADJACENT_OUTSIDE_BOUNDS;
		}
	}
	else {
		if (x - 1 < 0 || x + 1 >= board.getRowCount())
		{
			return ADJACENT_OUTSIDE_BOUNDS;
		}
	}

	//check if the adjancent spaces are empty
	if (matrix[x - ratioX][y - ratioY].empty() || matrix[x + ratioX][y + ratioY].empty())
	{
		return ADJACENT_SPACES_EMPTY;
	}
	//check if one of the adjancent spaces is an eter card
	if (matrix[x - ratioX][y - ratioY].back().GetIsEterCard() || matrix[x + ratioX][y + ratioY].back().GetIsEterCard())
	{
		return ETER_PROPERTY_VIOALTION;
	}

	return NO_ERRORS;
}

CommonErrors checkFuncFlame(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const MinionCard& CardToBePlaced, Player& p)
{
	int16_t lines = board.getLineCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines || y1 < 0 || y1 > cols)
		return CommonErrors::OUTSIDE_BOUNDS;
	/*if (board.setPos(x2, y2, CardToBePlaced, p) == 1)
		return FAILED_FLAME_CARD_PLACEMENT;*/
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncFire(Board&, int16_t cardValue) {
	if (cardValue < 1 || cardValue > 4)
		return CommonErrors::INVALID_CARD_VALUE;
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncAsh(Board& board, const MinionCard& card, int16_t x, int16_t y) {
	int16_t lines = board.getLineCount(), cols = board.getColCount();
	if (card.GetValue() > 4 || card.GetValue() < 1)
		return CommonErrors::INVALID_CARD_VALUE;
	if (x < 0 || x > lines || y < 0 || y > cols)/// bound check
		return CommonErrors::OUTSIDE_BOUNDS;
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncSpark(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	int16_t lines = board.getRowCount(), cols = board.getColCount();
	ResizeableMatrix& matrix = board.getMatrix();
	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols)
		return CommonErrors::OUTSIDE_BOUNDS;
	if (matrix[x1][y1].back().GetIsEterCard())
		return CommonErrors::ETER_PROPERTY_VIOLATION;

	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncSquall(Board& board, int16_t x1, int16_t y1,Player p) {
	int16_t lines = board.getRowCount(), cols = board.getColCount();
	ResizeableMatrix& matrix = board.getMatrix();

	if (x1 < 0 || x1 > lines)
		return CommonErrors::OUTSIDE_BOUNDS;
	if (y1 < 0 || y1 > cols)
		return CommonErrors::OUTSIDE_BOUNDS;

	if (matrix[x1][y1].empty())
		return CommonErrors::EMPTY_STACK;

	if (matrix[x1][y1].back().GetIsEterCard())
		return CommonErrors::ETER_PROPERTY_VIOLATION;

	if (matrix[x1][y1].back().GetIsIllusionCard())
		return CommonErrors::NOT_ILLUSION;
	if (matrix[x1][y1].back().GetColor() != p.GetPlayerColor())
		return CommonErrors::NOT_ENEMY_CARD;

	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncGust(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	ResizeableMatrix& matrix = board.getMatrix();
	int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols) // bound check
		return CommonErrors::OUTSIDE_BOUNDS;

	if (matrix[x1][y1].back().GetIsEterCard() || matrix[x2][y2].back().GetIsEterCard())
		return CommonErrors::ETER_PROPERTY_VIOLATION;

	if (!((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2) && std::abs(x1 - x2)))
		return CommonErrors::IDENTICAL_COORDINATES;

	if (!(matrix[x1][y1].back().GetValue() > matrix[x2][y2].back().GetValue()))
		return CommonErrors::INVALID_CARD_VALUE;

	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncMirage(Board& board, int16_t x1, int16_t y1, const MinionCard&) {
	ResizeableMatrix& matrix = board.getMatrix();
	int16_t lines = board.getRowCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines ||
		y1 < 0 || y1 > cols) //bound check
		return CommonErrors::OUTSIDE_BOUNDS;

	if (!matrix[x1][y1].back().GetIsIllusionCard())
		return CommonErrors::NOT_ILLUSION;
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncStorm(Board& board, int16_t x, int16_t y) {

	ResizeableMatrix& matrix = board.getMatrix();
	int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x < 0 || x > lines ||
		y < 0 || y > cols) //bound check
		return CommonErrors::OUTSIDE_BOUNDS;
	if (matrix[x][y].size() < 2)
		return CommonErrors::STACK_HEIGHT_TOO_SMALL;

	return CommonErrors::OUTSIDE_BOUNDS;
}

CommonErrors checkFuncTide(Board& board, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {

	CardStack& first = board.getStackOnPos(x1, y1);
	CardStack& second = board.getStackOnPos(x2, y2);
	int16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols) // bound check
		return CommonErrors::OUTSIDE_BOUNDS;

	if (first.back().GetIsEterCard() || second.back().GetIsEterCard())
		return CommonErrors::ETER_PROPERTY_VIOLATION;

	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncMist(Board& board, Player& p, int16_t x, int16_t y, MinionCard& card) {

	/*if (board.setPos(x, y, card, p) == 1)
		return 1;*/
	if (!p.GetIllusionUsage() || p.GetIllusionCard() == nullptr)
		return CommonErrors::ILLUSION_PROPERTY_VIOLATION;
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncWave(Board& board, int16_t x1, int16_t y1, MinionCard) {
	/*ResizeableMatrix matrix = board.getMatrix();
	if (matrix[x1][y1].back().GetIsEterCard())
		return -2;*/

	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncBlizzard(Line&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncWaterfall(Board&, int16_t) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncSupport(Board&, int16_t, int16_t) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncEarthquake(Board&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncCrumble(Board&, int16_t, int16_t) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncBorder(Board&, int16_t, int16_t) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncAvalanche(Board&, int16_t, int16_t, int16_t, int16_t, char) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncRock(Board&, int16_t, int16_t, MinionCard&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncFireMage1(Board&, Player&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncFireMage2(Board&, Player&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncEarthMage2(Board&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncAirMage1(Board&, Player& pl) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncAirMage2(Board&, int16_t, int16_t) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncWaterMage1(Board&, Player&) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkFuncWaterMage2(Board& board, Colours color, Player& pl) {
	return CommonErrors::NO_ERRORS;
}

CommonErrors checkfuncEarthMage1(Board& board, Player& caster, int16_t x, int16_t y, int16_t val)
{
	if (val < 0 || val > 3)
		return CommonErrors::INVALID_CARD_VALUE;

	if (x < 0 || y < 0 || x >= board.getRowCount() || y >= board.getColCount())
		return CommonErrors::OUTSIDE_BOUNDS;

	if (!caster.HasCardOfValue((uint16_t)val))    
		return CommonErrors::NO_CARDS_OF_VALUE;    

	const auto& selected = board.getStackOnPos(x, y);
	if (selected.empty())
		return CommonErrors::EMPTY_STACK;

	const MinionCard& top = selected.back();
	if (top.GetColor() != caster.GetPlayerColor())
		return CommonErrors::NOT_ENEMY_CARD;
	if (top.GetValue() >= val)
		return CommonErrors::INVALID_CARD_TYPE;
	
	return CommonErrors::NO_ERRORS;
}
