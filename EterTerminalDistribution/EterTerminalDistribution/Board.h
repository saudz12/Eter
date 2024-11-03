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
	uint16_t XBoundTest(uint16_t);
	uint16_t YBoundTest(uint16_t);
	bool posPlaceTest(uint16_t, uint16_t, uint16_t);

public:

	Board();
	~Board() = default;
	
	uint16_t getCardOnPos(uint16_t, uint16_t);
	uint16_t setPos(uint16_t, uint16_t, uint16_t, char);
	uint16_t removePos(uint16_t, uint16_t, uint16_t);
	char entityWon(uint16_t, uint16_t, char);

	uint16_t getRowCount();
	uint16_t getColCount();
	uint16_t getMaxSize();

	void printBoard();
};

