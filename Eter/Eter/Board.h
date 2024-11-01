#pragma once
#include <deque>
#include <cstdint>

using resizeableMatrix = std::deque<std::deque<std::deque<int>>>;
using lineChecker = std::deque<std::pair<uint8_t, uint8_t>>; //

class Board
{
private:
	resizeableMatrix m_board;
	uint8_t m_max_size;
	lineChecker m_rowChecker;
	lineChecker m_colChecker;
	uint8_t m_line_cnt;

public:

	Board() = default;

	int getPos(int, int);
	int setPos(int, int, int);
	int removePos(int, int, int);
	char entityWon(int, int);

	uint8_t getRowCount();
	uint8_t getColCount();
	uint8_t getMaxSize();
};

