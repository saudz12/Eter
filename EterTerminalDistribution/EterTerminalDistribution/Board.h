#pragma once
//bound=boundary
#define TOP_BOUND -1
#define LEFT_BOUND -1
#define BOTTOM_BOUND 1
#define RIGHT_BOUND 1
#define INSIDE_BOUND 0
#define OUTSIDE_BOUND 2
#define RED_ADD 1
#define BLUE_ADD 2
#define RED_ADD_BLUE_DEC 3
#define BLUE_ADD_RED_DEC 4
#define RED_DEC 5
#define BLUE_DEC 6
#define ZERO 7

#include "Player.h"
#include "ExplosionCard.h"

class Board
{
private:
	resizeableMatrix m_matrix;
	
	//score by color management
	lineChecker m_rowChecker;
	lineChecker m_colChecker;
	score m_firstDiag;
	score m_seconDiag;

	//for explosions, keep check either here or in game
	uint16_t m_lineCnt;

	//matrix size management
	uint16_t m_max_size;
	bool m_reachedMaxSize;


	//score counter on each line
	void increaseOnColorSides(uint16_t x, uint16_t y, char col);
	void increaseOnColorColumn(uint16_t x, uint16_t y, char col);
	void increaseOnColorRow(uint16_t x, uint16_t y, char col);
	void increaseOnColorDiagonal(uint16_t x, uint16_t y, char col);
	void increaseOnColorDiagonalNoResize(uint16_t x, uint16_t y, char col);

	//check position to board bounds
	int16_t XBoundTest(int16_t x);
	int16_t YBoundTest(int16_t y);

	//other check
	bool posPlaceTest(int16_t x, int16_t y, const MinionCard& card);
	bool isMatMaxSize();

	//add lines to border
	void addLineToLeft();
	void addLineToRight();
	void addLineOnTop();
	void addLineOnBottom();

	//will be changed if you can remove from middle
	void removeLeftMargin();
	void removeRightMargin();
	void removeTopMargin();
	void removeBottomMargin();
	//other interactions

public:

	Board(uint16_t size);
	~Board() = default;

	//Update board
	//only checks it. to modify it it needs to return a reference. do the check somewhere beforehand to get modifyable card
	MinionCard& getCardOnPos(int16_t x, int16_t y);
	int16_t setPos(int16_t x, int16_t y, const MinionCard& card, Player& p);
	int16_t setPosWaterfall(int16_t x, int16_t y, const MinionCard& card);
	int16_t removePos(int16_t x, int16_t y);
	int16_t removeStack(int16_t x, int16_t y);
	char entityWon(int16_t x, int16_t y, char col);

	uint16_t getRowCount();
	uint16_t getColCount();
	uint16_t getMaxSize();
	lineChecker& getRowChecker();
	lineChecker& getColChecker();
	resizeableMatrix& getMatrix();
	cardStack& getStackOnPos(uint16_t x, uint16_t y);
	uint16_t getLineCount();

	bool removeRow(uint16_t x);
	bool removeColumn(uint16_t y);

	void setMatrix(const resizeableMatrix& matrix);
	
	void updateFirstDiagChecker(uint16_t option);
	void updateSeconDiagChecker(uint16_t option);
	void updateColChecker(uint16_t y, uint16_t option);
	void updateRowChecker(uint16_t x, uint16_t option);

	void shiftLine(uint16_t start, uint16_t end, uint16_t ratio, uint16_t lineNo, uint16_t orientation);
	void checkForUpdates();

	bool isBoardFilled();
	bool isBoardEmpty();
	//false = valid, true = not good - sorry --change them later
	bool checkPosition(uint16_t x, uint16_t y);
	//false = valid, true = not good - sorry
	bool checkPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

	void printBoard();

	static void cloneMatrix(const Board& from, Board& to);

	void applyExplosionOnBoard(const ExplosionCard& explCard, Player& pl1, Player& p2);
};

