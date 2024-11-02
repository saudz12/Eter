#include "Board.h"

int Board::getCardOnPos(int x, int y) {
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return -1;
	return m_board[x][y].back();
}

int Board::setPos(int x, int y, int val) { //1 if not succesfull/invalid, 0 if ok
	const int boundCondX = XBoundTest(x);
	const int boundCondY = YBoundTest(y);

	if (boundCondX == 2 || boundCondY == 2)
		return -1;
	
	if (boundCondX == 0 && boundCondY == 0) {
		if (val > *m_board[x][y].rbegin()) {
			m_board[x][y].push_back(val);
			return 0;
		}
		return -1;
	}

	if (boundCondX == -1) {
		for (int i = 0; i < getRowCount(); i++) {
			m_board[i].push_front(std::deque<int>());
		}
	}

	if (boundCondY == -1) {
		m_board.push_front(std::deque<std::deque<int>>(getColCount()));
	}

	if (boundCondX == 1) {
		for (int i = 0; i < getRowCount(); i++) {
			m_board[i].push_back(std::deque<int>());
		}
	}

	if (boundCondY == 1) {
		m_board.push_back(std::deque<std::deque<int>>(getColCount()));
	}
	
	m_board[x][y].push_back(val);
	
	return 0;
}

void Board::removePos(int x, int y, int pos) {
	if (XBoundTest(x) != 0 || YBoundTest(y) != 0)
		return;
	m_board[x][y].erase(m_board[x][y].begin()+pos);
	
	return;
}

char Board::entityWon(int x, int y, char col)
{

	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return 0;
	if (col == 'R') {
		if (++m_colChecker[x].first > m_max_size)
			return 'R';
		if (++m_rowChecker[y].first > m_max_size)
			return 'R';
	}
	else {
		if (++m_colChecker[x].second > m_max_size)
			return 'B';
		if (++m_rowChecker[y].second > m_max_size)
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

int Board::XBoundTest(int x)//0 inside, -1 left margin, 1 right margin, 2 outside
{
	if (x >= 0 && x < m_max_size) return 0;

	if (x == -1 && this->getColCount() < m_max_size - 1) return -1;

	if (x == m_max_size - 1 && this->getColCount() < m_max_size) return 1;

	return 2;
}

int Board::YBoundTest(int y)//0 inside, -1 top margin, 1 buttom margin, 2 outside
{
	if (y >= 0 && y < m_max_size) return 0;

	if (y == -1 && this->getRowCount() < m_max_size - 1) return -1;

	if (y == m_max_size - 1 && this->getRowCount() < m_max_size) return 1;

	return 2;
}
