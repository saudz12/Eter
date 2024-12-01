#include "InputChecking.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction)
{
	const resizeableMatrix& matrix = board.getMatrix();

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

const int CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference)
{
	resizeableMatrix& matrix = board.getMatrix();

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

int16_t checkFuncFlame(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard& CardToBePlaced, Player& p)
{
	uint16_t lines = board.getLineCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines || y1 < 0 || y1 > cols)/// bound check
		return -1;
	if (x2 < 0 || x2 > lines || y2 < 0 || y2 >cols)
		return -1;
	if (board.setPos(x2, y2, CardToBePlaced, p) == 1)
		return 1;
	return 0;
}

int16_t checkFuncFire(Board&, uint16_t cardValue) {
	if (cardValue < 1 || cardValue > 4)
		return 1;
	return 0;
}

int16_t checkFuncAsh(Board& board, const MinionCard& card, uint16_t x, uint16_t y) {
	uint16_t lines = board.getLineCount(), cols = board.getColCount();
	if (card.GetValue() > 4 || card.GetValue() < 1)
		return 1;
	if (x < 0 || x > lines || y < 0 || y > cols)/// bound check
		return -1;
	return 0;
}

int16_t checkFuncSpark(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t lines = board.getRowCount(), cols = board.getColCount();
	resizeableMatrix& matrix = board.getMatrix();
	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols)
		return -1;
	if (matrix[x1][y1].back().GetIsEterCard())
		return 1;

	return 0;
}

int16_t checkFuncSquall(Board& board, uint16_t x1, uint16_t y1) {
	uint16_t lines = board.getRowCount(), cols = board.getColCount();
	resizeableMatrix& matrix = board.getMatrix();

	if (x1 < 0 || x1 > lines)
		return -1;
	if (y1 < 0 || y1 > cols)
		return -1;

	if (matrix[x1][y1].empty())
		return -3;

	if (matrix[x1][y1].back().GetIsEterCard())
		return -2;

	if (matrix[x1][y1].back().GetIsIllusionCard())
		return 3;

	return 0;
}


int16_t checkFuncHurricane(Board&, hand& p1, hand& p2) {// for saud, don't touch !!!!
	return 0;
}

int16_t checkFuncGust(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	resizeableMatrix& matrix = board.getMatrix();
	uint16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols) // bound check
		return -1;

	if (matrix[x1][y1].back().GetIsEterCard() || matrix[x2][y2].back().GetIsEterCard())
		return -2;

	if (!((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2) && std::abs(x1 - x2)))
		return 1;

	if (!(matrix[x1][y1].back().GetValue() > matrix[x2][y2].back().GetValue()))
		return 2;

	return 0;
}

int16_t checkFuncMirage(Board& board, uint16_t x1, uint16_t y1, const MinionCard&) {
	resizeableMatrix& matrix = board.getMatrix();
	uint16_t lines = board.getRowCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines ||
		y1 < 0 || y1 > cols) //bound check
		return -1;

	if (!matrix[x1][y1].back().GetIsIllusionCard())
		return 1;
	return 0;
}

int16_t checkFuncStorm(Board& board, uint16_t x, uint16_t y) {

	resizeableMatrix& matrix = board.getMatrix();
	uint16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x < 0 || x > lines ||
		y < 0 || y > cols) //bound check
		return -1;
	if (matrix[x][y].size() < 2)
		return 1;

	return 0;
}

int16_t checkFuncTide(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {

	cardStack& first = board.getStackOnPos(x1, y1);
	cardStack& second = board.getStackOnPos(x2, y2);
	uint16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols) // bound check
		return -1;

	if (first.back().GetIsEterCard() || second.back().GetIsEterCard())
		return -2;

	return 0;
}

uint16_t checkFuncMist(Board& board, Player& p, uint16_t x, uint16_t y, MinionCard& card) {

	if (board.setPos(x, y, card, p) == 1)
		return 1;
	return 0;
}

int16_t checkFuncWave(Board& board, uint16_t x1, uint16_t y1, MinionCard) {
	resizeableMatrix matrix = board.getMatrix();
	if (matrix[x1][y1].back().GetIsEterCard())
		return -2;

	return 0;
}

uint16_t checkFuncBlizzard(line&) {
	return 0;
}

uint16_t checkFuncWaterfall(Board&, uint16_t) {
	return 0;
}

uint16_t checkFuncSupport(Board&, uint16_t, uint16_t) {
	return 0;
}

uint16_t checkFuncEarthquake(Board&) {
	return 0;
}

uint16_t checkFuncCrumble(Board&, uint16_t, uint16_t) {
	return 0;
}

uint16_t checkFuncBorder(Board&, uint16_t, uint16_t) {
	return 0;
}

uint16_t checkFuncAvalanche(Board&, uint16_t, uint16_t, uint16_t, uint16_t, char) {
	return 0;
}

uint16_t checkFuncRock(Board&, uint16_t, uint16_t, MinionCard&) {
	return 0;
}

uint16_t checkFuncFireMage1(Board&, Player&) {
	return 0;
}

uint16_t checkFuncFireMage2(Board&, Player&) {
	return 0;
}

uint16_t checkFuncEarthMage1(Board&, Player&, uint16_t, uint16_t) {
	return 0;
}

uint16_t checkFuncEarthMage2(Board&) {
	return 0;
}

uint16_t checkFuncAirMage1(Board&, Player& pl) {
	return 0;
}

uint16_t checkFuncAirMage2(Board&, uint16_t, uint16_t) {
	return 0;
}

uint16_t checkFuncWaterMage1(Board&, Player&) {
	return 0;
}

uint16_t checkFuncWaterMage2(Board& board, char color, Player& pl) {
	return 0;
}
