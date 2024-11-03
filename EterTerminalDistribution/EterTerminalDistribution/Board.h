#pragma once
//bound=boundary
#define TOP_BOUND -1
#define LEFT_BOUND -1
#define BOTTOM_BOUND 1
#define RIGHT_BOUND 1
#define INSIDE_BOUND 0
#define OUTSIDE_BOUND 2

#include <deque>
#include <cstdint>
#include <iostream>

using cardStack = std::deque<int>;
using line = std::deque<cardStack>;
using resizeableMatrix = std::deque<line>;
using lineChecker = std::deque<std::pair<int, int>>; //<R/B>

class Board
{
private:
	resizeableMatrix m_board;
	uint8_t m_max_size; //in privinta folosirii uint8_t mutam totul mai incolo 
	lineChecker m_rowChecker;
	lineChecker m_colChecker;
	uint8_t m_line_cnt; //for explosions, keep check either here or in game

	void increaseOnColor(int, int, char);
	int XBoundTest(int);
	int YBoundTest(int);
	bool posPlaceTest(int, int, int);

public:

	Board();
	~Board() = default;
	
	int getCardOnPos(int, int);
	int setPos(int, int, int, char);
	int removePos(int, int, int);
	char entityWon(int, int, char);

	uint8_t getRowCount();
	uint8_t getColCount();
	uint8_t getMaxSize();

	void printBoard();
};

