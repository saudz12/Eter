#pragma once
//bound=boundary
#define TOP_BOUND -1
#define LEFT_BOUND -1
#define BOTTOM_BOUND 1
#define RIGHT_BOUND 1
#define INSIDE_BOUND 0
#define OUTSIDE_BOUND 2

#include "MinionCard.h"

using cardStack = std::deque<MinionCard>; //minioncard here
using line = std::deque<cardStack>;
using resizeableMatrix = std::deque<line>;
using score = std::pair <uint16_t, uint16_t>; //<R/B>
using lineChecker = std::deque<score>;

class Board
{
private:
	resizeableMatrix m_board;
	uint16_t m_max_size;
	lineChecker m_rowChecker;
	lineChecker m_colChecker;
	score m_firstDiag;
	score m_seconDiag;

	bool m_reachedMaxSize;

	//for explosions, keep check either here or in game
	uint16_t m_lineCnt;

	void increaseOnColorSides(uint16_t x, uint16_t y, char col);
	void increaseOnColorColumn(uint16_t x, uint16_t y, char col);
	void increaseOnColorRow(uint16_t x, uint16_t y, char col);
	void increaseOnColorDiagonal(uint16_t x, uint16_t y, char col);
	void increaseOnColorFirstDiagonal(uint16_t x, uint16_t y, char col);
	void increaseOnColorSeconDiagonal(uint16_t x, uint16_t y, char col);

	int16_t XBoundTest(int16_t x);
	int16_t YBoundTest(int16_t y);

	bool posPlaceTest(int16_t x, int16_t y, uint16_t val);
	bool isMatMaxSize();

	void addLineToLeft();
	void addLineToRight();
	void addLineOnTop();
	void addLineOnBottom();

public:

	Board();
	~Board() = default;

	MinionCard getCardOnPos(int16_t x, int16_t y);
	//1 if not succesfull/invalid, 0 if ok
	int16_t setPos(int16_t x, int16_t y, uint16_t val, char col);
	int16_t removePos(int16_t x, int16_t y, uint16_t pos);
	char entityWon(int16_t x, int16_t y, char col);

	uint16_t getRowCount();
	uint16_t getColCount();
	uint16_t getMaxSize();
	resizeableMatrix getMatrix();
	void setMatrix(const resizeableMatrix& matrix);

	bool isBoardFilled();
	bool isBoardEmpty();

	void printBoard();
};

