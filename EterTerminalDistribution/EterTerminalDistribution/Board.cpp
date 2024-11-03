#include "Board.h"

void Board::increaseOnColor(int x, int y, char col)
{
	if (col == 'R')
	{
		m_rowChecker[x].first++;
		m_colChecker[y].first++;
	}
	else
	{
		m_rowChecker[x].second++;
		m_colChecker[y].second++;
	}
}

//REWRITE EVERYTHING DECIDE ON WHAT IS X AND Y

Board::Board()
{
	m_board.push_back(line());
	m_board[0].push_back(cardStack());
	m_line_cnt = 0;
	m_max_size = 3;
	m_rowChecker.emplace_back(0, 0);
	m_colChecker.emplace_back(0, 0);
}

int Board::getCardOnPos(int x, int y) {//-1 esec
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return -1;
	return m_board[x][y].back();
}

int Board::setPos(int x, int y, int val, char col) { //1 if not succesfull/invalid, 0 if ok
	const int boundCondX = XBoundTest(x);
	const int boundCondY = YBoundTest(y);

	if (boundCondX == OUTSIDE_BOUND || boundCondY == OUTSIDE_BOUND)
		return -1;
	
	if (boundCondX == INSIDE_BOUND && boundCondY == INSIDE_BOUND) {
		if (posPlaceTest(x, y, val)) {
			if (getColCount() == 1 && getRowCount() == 1 && m_board[x][y].empty())
				increaseOnColor(x, y, col);
			//if(m_board[x][y].back().col != val.col)
			//if(col == 'R')... scade pt rosu, creste pt albastru
			//else vice versa <--- de implementat odata cu schimbarea tipului lui val din int in minion card!!!
			m_board[x][y].push_back(val);
			return 0;
		}
		else
			return -1;
	}

	if (boundCondX != INSIDE_BOUND || boundCondY != INSIDE_BOUND) {
		if (boundCondX == TOP_BOUND) {
			x = 0;
			m_board.push_front(line(getColCount()));
			m_rowChecker.emplace_front(0, 0);
			increaseOnColor(x, y, col);
		}

		if (boundCondY == LEFT_BOUND) {
			y = 0;
			for (int i = 0; i < getRowCount(); i++) {
				m_board[i].push_front(cardStack());
			}
			m_colChecker.emplace_front(0, 0);
			increaseOnColor(x, y, col);
		}

		if (boundCondX == BOTTOM_BOUND) {
			m_board.push_back(line(getColCount()));	
			m_rowChecker.emplace_front(0, 0);
			increaseOnColor(x, y, col);
		}	

		if (boundCondY == RIGHT_BOUND) {
			for (int i = 0; i < getRowCount(); i++) {
				m_board[i].push_back(cardStack());
			}
			m_colChecker.emplace_front(0, 0);
			increaseOnColor(x, y, col);
		}

	}

	m_board[x][y].push_back(val);
	return 0;
}

int Board::removePos(int x, int y, int pos) { //1 esec, 0 succes
	if (XBoundTest(x) != INSIDE_BOUND || YBoundTest(y) != INSIDE_BOUND)
		return 1;
	if (pos == 0)
		m_board[x][y].pop_front();
	if (pos == m_board[x][y].size()-1)
		m_board[x][y].pop_back();
	else
		m_board[x][y].erase(m_board[x][y].begin()+pos);
	
	return 0;
}

char Board::entityWon(int x, int y, char col) //0 inseamna ca momentan e egal
{
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return 0;
	if (col == 'R') {
		if (++m_rowChecker[x].first == m_max_size || ++m_colChecker[y].first == m_max_size)
			return 'R';
	}
	else {
		if (++m_rowChecker[x].second == m_max_size || ++m_colChecker[y].second == m_max_size)
			return 'B';
	}
	return 0;
}

uint8_t Board::getRowCount()
{
	return uint8_t(m_rowChecker.size());
}

uint8_t Board::getColCount()
{
	return uint8_t(m_colChecker.size());
}

uint8_t Board::getMaxSize()
{
	return this->m_max_size;
}

void Board::printBoard()
{
	std::cout << "R\\B ";
	for (int i = 0; i < getColCount(); i++)
		std::cout << m_colChecker[i].first << "|" << m_colChecker[i].second << " ";
	for (int i = 0; i < getRowCount(); i++) {
		std::cout << "\n" << m_rowChecker[i].first << "|" << m_rowChecker[i].second << " ";
		for (int j = 0; j < getColCount(); j++)
			if (!m_board[i][j].empty())
				std::cout << " " << m_board[i][j].back() << "  ";
			else
				std::cout << " -- ";
	}
}

int Board::XBoundTest(int x)//0 inside, -1 left margin, 1 right margin, 2 outside
{
	if (x >= 0 && x < getRowCount()) return INSIDE_BOUND;

	if (x == -1 && getRowCount() < m_max_size) return TOP_BOUND;

	if (x == getRowCount() && getRowCount() < m_max_size) return BOTTOM_BOUND;

	return OUTSIDE_BOUND;
}

int Board::YBoundTest(int y)//0 inside, -1 top margin, 1 buttom margin, 2 outside
{
	if (y >= 0 && y < getColCount()) return INSIDE_BOUND;

	if (y == -1 && getColCount() < m_max_size) return LEFT_BOUND;

	if (y == getColCount() && getColCount() < m_max_size) return RIGHT_BOUND;

	return OUTSIDE_BOUND;
}

bool Board::posPlaceTest(int x, int y, int val)
{
	if (m_board[x][y].empty())
		return true;
	if (val > *m_board[x][y].rbegin())
		return true;
	return false;
}
