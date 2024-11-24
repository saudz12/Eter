#include "functionsInputCheck.h"
// add input checks here
// return 0 means all good
// 1 and higher means an error

int checkFuncFlame(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard& CardToBePlaced, Player& p)
{
	uint16_t lines = board.getLineCount(), cols = board.getColCount();
	if (x1 < 0 || x1 > lines || y1 < 0 || y1 > cols)/// bound check
		return 1;
	if (x2 < 0 || x2 > lines || y2 < 0 || y2 >cols)
		return 1;
	if (board.setPos(x2, y2, CardToBePlaced, p) == 1)
		//std::cout << "Failed to place minion card with Flame elemental card\n";
		return 2;
	return 0;
}
int checkFuncFire(Board&, Player&, Player&, uint16_t cardValue) {
	if (cardValue < 1 || cardValue > 4)
		return 1;
	return 0;
}
int checkFuncAsh(Board& board, const MinionCard& card, uint16_t x, uint16_t y) {
	uint16_t lines = board.getLineCount(), cols = board.getColCount();
	if (card.GetValue() > 4 || card.GetValue() < 1)
		return 2;
	if (x < 0 || x > lines || y < 0 || y > cols)/// bound check
		return 1;
	return 0;
}
int checkFuncSpark(Board& board, uint16_t x1,uint16_t y1,uint16_t x2, uint16_t y2)
{
	uint16_t lines = board.getRowCount(), cols = board.getColCount();
	resizeableMatrix& matrix = board.getMatrix();
	if (x1<0 || x1>lines ||
		x2<0 || x2>lines ||
		y1<0 || y1>cols ||
		y2<0 || y2>cols)
		return 1;
	if (matrix[x1][y1].back().GetIsEterCard())
		return 2;
	//std::cout << "Can't use Spark elemental card on eter card\n";
	return 0;
}

int checkFuncSquall(Board& board, uint16_t x1, uint16_t y1) {
	uint16_t lines = board.getRowCount(), cols = board.getColCount();
	resizeableMatrix& matrix = board.getMatrix();

	if (x1 < 0 || x1 > lines)
		return 1;
	if (y1 < 0 || y1 > cols)
		return 1;


	if (matrix[x1][y1].empty()) {
		//std::cout << "Empty Space..\n";
		return 2;
	}

	if (matrix[x1][y1].back().GetIsEterCard())
	{
		//std::cout << "Can't use Squall elemental card on eter card\n";
		return 3;
	}

	if (matrix[x1][y1].back().GetIsIllusionCard())
	{
		//std::cout << "Can't use Squall elemental card on illusion\n";
		return 4;
	}
	return 0;
}


int checkFuncHurricane(Board&, hand& p1, hand& p2) {// for saud, dont touch
	return 0;
}

int checkFuncGust(Board&, uint16_t, uint16_t, uint16_t, uint16_t) {
	return 0;
}

int checkFuncMirage(Board&, Player&, uint16_t, uint16_t, const MinionCard&) {
	return 0;
}

int checkFuncStorm(Board&, Player&, Player&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncTide(Board&, uint16_t, uint16_t, uint16_t, uint16_t) {
	return 0;
}

int checkFuncMist(Board&, Player&, uint16_t, uint16_t, MinionCard&) {
	return 0;
}

int checkFuncWave(Board&, uint16_t, uint16_t, MinionCard) {
	return 0;
}

int checkFuncWhirlpool(Board&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncBlizzard(line&) {
	return 0;
}

int checkFuncWaterfall(Board&, uint16_t) {
	return 0;
}

int checkFuncSupport(Board&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncEarthquake(Board&) {
	return 0;
}

int checkFuncCrumble(Board&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncBorder(Board&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncAvalanche(Board&, uint16_t, uint16_t, uint16_t, uint16_t, char) {
	return 0;
}

int checkFuncRock(Board&, uint16_t, uint16_t, MinionCard&) {
	return 0;
}

int checkFuncFireMage1(Board&, Player&) {
	return 0;
}

int checkFuncFireMage2(Board&, Player&) {
	return 0;
}

int checkFuncEarthMage1(Board&, Player&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncEarthMage2(Board&) {
	return 0;
}

int checkFuncAirMage1(Board&, Player& pl) {
	return 0;
}

int checkFuncAirMage2(Board&, uint16_t, uint16_t) {
	return 0;
}

int checkFuncWaterMage1(Board&, Player&) {
	return 0;
}

int checkFuncWaterMage2(Board& board, char color, Player& pl) {
	return 0;
}
