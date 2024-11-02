#pragma once
#include <deque>
#include <cstdint>
#include <iostream>

using cardStack = std::deque<int>;
using line = std::deque<cardStack>;
using resizeableMatrix = std::deque<line>;
using lineChecker = std::deque<std::pair<uint8_t, uint8_t>>; //

class Board
{
private:
	resizeableMatrix m_board;
	uint8_t m_max_size;
	lineChecker m_rowChecker;
	lineChecker m_colChecker;
	uint8_t m_line_cnt; //for explosions, keep check either here or in game

public:

	Board();
	~Board() = default;
	
	int getCardOnPos(int, int);
	int setPos(int, int, int);
	void removePos(int, int, int);
	char entityWon(int, int, char);

	uint8_t getRowCount();
	uint8_t getColCount();
	uint8_t getMaxSize();

	void printBoard();
	
	int XBoundTest(int);
	int YBoundTest(int);
};

