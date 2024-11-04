#include "Board.h"


Board::Board() 
	: m_line_cnt{0}, m_max_size{3}, m_firstDiag{0, 0}, m_seconDiag{0, 0}, m_board(resizeableMatrix()), m_rowChecker(lineChecker()), m_colChecker(lineChecker())
{
	m_board.push_back(line());
	m_board[0].push_back(cardStack());
	m_rowChecker.emplace_back(0, 0);
	m_colChecker.emplace_back(0, 0);
}

bool Board::reached_max_size()
{
	return getColCount() == m_max_size && getRowCount() == m_max_size;
}

void Board::increaseOnColorSides(uint16_t x, uint16_t y, char col)
{
	if (col == 'R') {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'B') {
				m_rowChecker[x].second--;
				m_colChecker[y].second--;
			}
			else
				return;
		m_rowChecker[x].first++;
		m_colChecker[y].first++;
	}
	else {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'R') {
				m_rowChecker[x].first--;
				m_colChecker[y].first--;
			}
			else
				return;
		m_rowChecker[x].second++;
		m_colChecker[y].second++;
	}
}

void Board::increaseOnColorDiagonal(uint16_t x, uint16_t y, char col)
{
	if (col == 'R') {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'B') {
				if (x == y) {
					m_firstDiag.second--;
				}
				if (x + y == m_max_size) {
					m_seconDiag.second--;
				}
			}
			else
				return;
		if (x == y) {
			m_firstDiag.first++;
		}
		if (x + y == m_max_size) {
			m_seconDiag.first++;
		}
	}
	else {
		if (!m_board.empty()) {
			if (m_board[x][y].back().GetColor() == 'B') {
				if (x == y) {
					m_firstDiag.first--;
				}
				if (x + y == m_max_size) {
					m_seconDiag.first--;
				}
			}
			else
				return;
		}
		if (x == y) {
			m_firstDiag.second++;
		}
		if (x + y == m_max_size) {
			m_seconDiag.second++;
		}
	}
}

MinionCard Board::getCardOnPos(int16_t x, int16_t y) {//-1 esec
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return MinionCard{0,'\0'};
	return m_board[x][y].back();
}

int16_t Board::setPos(int16_t x, int16_t y, uint16_t val, char col) { //1 if not succesfull/invalid, 0 if ok
	const int boundCondX = XBoundTest(x);
	const int boundCondY = YBoundTest(y);

	if (boundCondX == OUTSIDE_BOUND || boundCondY == OUTSIDE_BOUND)
		return -1;

	if (boundCondX == INSIDE_BOUND && boundCondY == INSIDE_BOUND) {
		if (posPlaceTest(x, y, val)) {
			increaseOnColorSides(x, y, col);
			m_board[x][y].push_back({ val,col });
			return 0;
		}
		else
			return -1;
	}

	if (boundCondX != INSIDE_BOUND || boundCondY != INSIDE_BOUND) {
		if (boundCondX == TOP_BOUND && boundCondY == LEFT_BOUND) {
			x = 0;
			y = 0;
			addLineOnTop();
			addLineToLeft();
			increaseOnColorSides(x, y, col);
			m_board[x][y].push_back({ val,col });

			return 0;
		}
		if (boundCondX == BOTTOM_BOUND && boundCondY == RIGHT_BOUND) {
			addLineOnBottom();
			addLineToRight();
			increaseOnColorSides(x, y, col);
			m_board[x][y].push_back({ val,col });

			return 0;
		}
		if (boundCondX == TOP_BOUND && boundCondY == RIGHT_BOUND) {
			x = 0;
			addLineOnTop();
			addLineToRight();
			increaseOnColorSides(x, y, col);
			m_board[x][y].push_back({ val,col });

			return 0;
		}
		if (boundCondX == BOTTOM_BOUND && boundCondY == LEFT_BOUND) {
			y = 0;
			addLineOnBottom();
			addLineToLeft();
			increaseOnColorSides(x, y, col);
			m_board[x][y].push_back({ val,col });

			return 0;
		}
		if (boundCondX == TOP_BOUND) {
			x = 0;
			addLineOnTop();
			increaseOnColorSides(x, y, col);
		}

		if (boundCondY == LEFT_BOUND) {
			y = 0;
			addLineToLeft();
			increaseOnColorSides(x, y, col);
		}

		if (boundCondX == BOTTOM_BOUND) {
			addLineOnBottom();
			increaseOnColorSides(x, y, col);
		}

		if (boundCondY == RIGHT_BOUND) {
			addLineToRight();
			increaseOnColorSides(x, y, col);
		}
	}

	if (reached_max_size() && x == y && x + y == m_max_size - 1)
		increaseOnColorDiagonal(x, y, col);
	else {
		m_firstDiag.first = 0;
		m_firstDiag.second = 0;
		m_seconDiag.first = 0;
		m_seconDiag.second = 0;
	}

	m_board[x][y].push_back({ val, col });
	return 0;
}

int16_t Board::removePos(int16_t x, int16_t y, uint16_t pos) { //1 esec, 0 succes
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

char Board::entityWon(int16_t x, int16_t y, char col) //0 inseamna ca momentan e egal
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

uint16_t Board::getRowCount()
{
	return uint16_t(m_rowChecker.size());
}

uint16_t Board::getColCount()
{
	return uint16_t(m_colChecker.size());
}

uint16_t Board::getMaxSize()
{
	return this->m_max_size;
}

void Board::printBoard()
{
	std::cout << "R\\B ";
	for (int i = 0; i < getColCount(); i++)
		std::cout << int(m_colChecker[i].first) << "|" << m_colChecker[i].second << " ";

	for (int i = 0; i < getRowCount(); i++) {
		std::cout << "\n" << m_rowChecker[i].first << "|" << m_rowChecker[i].second << " ";
		for (int j = 0; j < getColCount(); j++)
			if (!m_board[i][j].empty())
				std::cout << m_board[i][j].back() << " ";
			else
				std::cout << "--- ";
	}
}

int16_t Board::XBoundTest(int16_t x)//0 inside, -1 left margin, 1 right margin, 2 outside
{
	if (x >= 0 && x < getRowCount()) return INSIDE_BOUND;

	if (x == -1 && getRowCount() < m_max_size) return TOP_BOUND;

	if (x == getRowCount() && getRowCount() < m_max_size) return BOTTOM_BOUND;

	return OUTSIDE_BOUND;
}

int16_t Board::YBoundTest(int16_t y)//0 inside, -1 top margin, 1 buttom margin, 2 outside
{
	if (y >= 0 && y < getColCount()) return INSIDE_BOUND;

	if (y == -1 && getColCount() < m_max_size) return LEFT_BOUND;

	if (y == getColCount() && getColCount() < m_max_size) return RIGHT_BOUND;

	return OUTSIDE_BOUND;
}

bool Board::posPlaceTest(int16_t x, int16_t y, uint16_t val) //x si y unde punem si MinionCard.m_value
{
	if (m_board[x][y].empty())
		return true;
	if (val > m_board[x][y].back().GetValue())
		return true;
	return false;
}

void Board::addLineToLeft()
{
	for (int i = 0; i < getRowCount(); i++) {
		m_board[i].push_front(cardStack());
	}
	m_colChecker.emplace_front(0, 0);
}

void Board::addLineToRight()
{
	for (int i = 0; i < getRowCount(); i++) {
		m_board[i].push_back(cardStack());
	}
	m_colChecker.emplace_back(0, 0);
}

void Board::addLineOnTop()
{
	m_board.push_front(line(getColCount()));
	m_rowChecker.emplace_front(0, 0);
}

void Board::addLineOnBottom()
{
	m_board.push_back(line(getColCount()));
	m_rowChecker.emplace_back(0, 0);
}
