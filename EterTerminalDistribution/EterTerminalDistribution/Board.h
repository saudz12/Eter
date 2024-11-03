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
#include "MinionCard.h"

using cardStack = std::deque<uint16_t>;
using line = std::deque<cardStack>;
using resizeableMatrix = std::deque<line>;
using lineChecker = std::deque<std::pair<uint16_t, uint16_t>>; //<R/B>

class Board
{
private:
	resizeableMatrix m_board;
	uint16_t m_max_size; //in privinta folosirii uint8_t mutam totul mai incolo 
	lineChecker m_rowChecker;
	lineChecker m_colChecker;
	uint16_t m_line_cnt; //for explosions, keep check either here or in game

	void increaseOnColor(uint16_t, uint16_t, char);
	int16_t XBoundTest(int16_t);
	int16_t YBoundTest(int16_t);
	bool posPlaceTest(int16_t, int16_t, uint16_t);

	void addLineToLeft();
	void addLineToRight();
	void addLineOnTop();
	void addLineOnBottom();

public:

	Board();
	~Board() = default;
	
	int16_t getCardOnPos(int16_t, int16_t);
	int16_t setPos(int16_t, int16_t, uint16_t, char);
	int16_t removePos(int16_t, int16_t, uint16_t);
	char entityWon(int16_t, int16_t, char);

	uint16_t getRowCount();
	uint16_t getColCount();
	uint16_t getMaxSize();

	void printBoard();
};

