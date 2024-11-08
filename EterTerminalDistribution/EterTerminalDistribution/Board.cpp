#include "Board.h"

Board::Board()
	: m_lineCnt{ 0 }, m_max_size{ 3 }, m_firstDiag{ 0, 0 }, m_seconDiag{ 0, 0 }, m_board(resizeableMatrix()), m_rowChecker(lineChecker()), m_colChecker(lineChecker()), m_reachedMaxSize{ false }
{
	m_board.push_back(line());
	m_board[0].push_back(cardStack());
	m_rowChecker.emplace_back(0, 0);
	m_colChecker.emplace_back(0, 0);
}

//true if yes, false if no
bool Board::isMatMaxSize()
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

void Board::increaseOnColorColumn(uint16_t x, uint16_t y, char col)
{
	if (col == 'R') {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'B') {
				m_colChecker[y].second--;
			}
			else
				return;
		m_colChecker[y].first++;
	}
	else {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'R') {
				m_colChecker[y].first--;
			}
			else
				return;
		m_colChecker[y].second++;
	}
}

void Board::increaseOnColorRow(uint16_t x, uint16_t y, char col)
{
	if (col == 'R') {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'B') {
				m_rowChecker[x].second--;
			}
			else
				return;
		m_rowChecker[x].first++;
	}
	else {
		if (!m_board[x][y].empty())
			if (m_board[x][y].back().GetColor() == 'R') {
				m_rowChecker[x].first--;
			}
			else
				return;
		m_rowChecker[x].second++;
	}
}

/// <summary>
/// Implementation notes:
/// LA STERRGERI DE LINII/COLOANE TREBUIE SA FIE FACUT ASTFEL INCAT SA SE RECALCULEZE NUMAI O DATA CAND DEVINE IAR PATRATICA CU LATURA MAXIMA
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="col"></param>
void Board::increaseOnColorDiagonal(uint16_t x, uint16_t y, char col)
{
	if (m_reachedMaxSize) {
		increaseOnColorFirstDiagonal(x, y, col);
		increaseOnColorSeconDiagonal(x, y, col);
		return;
	}

	m_firstDiag = { 0, 0 };
	m_seconDiag = { 0, 0 };
	m_reachedMaxSize = true;
	for (int i = 0; i < m_max_size; i++)
	{
		if (!m_board[i][i].empty()) {
			if (m_board[i][i].back().GetColor() == 'R')
				m_firstDiag.first++;
			else
				m_firstDiag.second++;
		}
		if (!m_board[i][m_max_size - i - 1].empty()) {
			if (m_board[i][m_max_size - i - 1].back().GetColor() == 'R')
				m_seconDiag.first++;
			else
				m_seconDiag.second++;
		}
	}
	if (x == y)
	{
		if (col == 'R')
		{
			m_firstDiag.first++;
		}
		else
		{
			m_firstDiag.second++;
		}
	}
	if (x + y == m_max_size - 1)
	{
		if (col == 'R')
		{
			m_seconDiag.first++;
		}
		else
		{
			m_seconDiag.second++;
		}
	}
}

void Board::increaseOnColorFirstDiagonal(uint16_t x, uint16_t y, char col)
{
	if (col == 'R') {
		if (m_board[x][y].empty()) {
			if (x == y) {
				m_firstDiag.first++;
			}
			if (x + y == m_max_size) {
				m_seconDiag.first++;
			}
			return;
		}
		if (m_board[x][y].back().GetColor() == 'B') {
			if (x == y) {
				m_firstDiag.first++;
				m_firstDiag.second--;
			}
			if (x + y == m_max_size) {
				m_seconDiag.first++;
				m_seconDiag.second--;
			}
		}
	}
	else {
		if (m_board[x][y].empty()) {
			if (x == y) {
				m_firstDiag.second++;
			}
			if (x + y == m_max_size - 1) {
				m_seconDiag.second++;
			}
			return;
		}
		if (m_board[x][y].back().GetColor() == 'R') {
			if (x == y) {
				m_firstDiag.second++;
				m_firstDiag.first--;
			}
			if (x + y == m_max_size - 1) {
				m_seconDiag.second++;
				m_seconDiag.first--;
			}
		}
	}
}

void Board::increaseOnColorSeconDiagonal(uint16_t x, uint16_t y, char col)
{
}

MinionCard Board::getCardOnPos(int16_t x, int16_t y) {//-1 esec
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return MinionCard{ 0,'\0' };
	return m_board[x][y].back();
}

int16_t Board::setPos(int16_t x, int16_t y, uint16_t val, char col) {
	const int boundCondX = XBoundTest(x);
	const int boundCondY = YBoundTest(y);

	if (boundCondX == OUTSIDE_BOUND || boundCondY == OUTSIDE_BOUND)
		return 1;
	if ((x != 0 || y != 0) && isBoardEmpty()) //special case for emmpty matrix
		return 1;

	if (boundCondX == INSIDE_BOUND && boundCondY == INSIDE_BOUND || x != 0 && y == 0 && isBoardEmpty()) {
		if (!posPlaceTest(x, y, val)) {
			return 1;
		}
	}
	if (boundCondX == TOP_BOUND) {
		x = 0;
		addLineOnTop();
	}

	if (boundCondY == LEFT_BOUND) {
		y = 0;
		addLineToLeft();
	}

	if (boundCondX == BOTTOM_BOUND) {
		addLineOnBottom();
	}

	if (boundCondY == RIGHT_BOUND) {
		addLineToRight();
	}
	increaseOnColorRow(x, y, col);
	increaseOnColorColumn(x, y, col);

	if (!isMatMaxSize())
		m_reachedMaxSize = false;
	else if (x == y || x + y == m_max_size - 1)
		increaseOnColorDiagonal(x, y, col);

	m_board[x][y].push_back({ val, col });
	return 0;
}

//1 esec, 0 succes
int16_t Board::removePos(int16_t x, int16_t y, uint16_t pos) {
	if (XBoundTest(x) != INSIDE_BOUND || YBoundTest(y) != INSIDE_BOUND)
		return 1;
	if (pos == 0)
		m_board[x][y].pop_front();
	if (pos == m_board[x][y].size() - 1)
		m_board[x][y].pop_back();
	else
		m_board[x][y].erase(m_board[x][y].begin() + pos);

	return 0;
}

//0 inseamna ca momentan e egal
char Board::entityWon(int16_t x, int16_t y, char col)
{
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return 0;
	if (col == 'R') {
		if (m_rowChecker[x].first == m_max_size || m_colChecker[y].first == m_max_size || m_firstDiag.first == m_max_size || m_seconDiag.first == m_max_size)
			return 'R';
	}
	else {
		if (m_rowChecker[x].second == m_max_size || m_colChecker[y].second == m_max_size || m_firstDiag.second == m_max_size || m_seconDiag.second == m_max_size)
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

resizeableMatrix Board::getMatrix()
{
	return resizeableMatrix();
}

void Board::setMatrix(const resizeableMatrix& matrix)
{
	m_board = matrix;
}

bool Board::isBoardFilled()
{
	if (!isMatMaxSize())
		return false;

	for (int i = 0; i < m_max_size; i++)
		for (int j = 0; j < m_max_size; j++)
			if (m_board[i][j].empty())
				return false;
	return true;
}

bool Board::isBoardEmpty()
{
	return getColCount() == 1 && getRowCount() == 1 && m_board[0][0].empty();
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
			{
				/*if (m_board[i][j].back().GetColor() == 'R')
					std::cout << "\033[33m";
				else
					std::cout << "\033[34m";*/
				std::cout << m_board[i][j].back() << " ";
			}
			else
				std::cout << "--- ";
	}

	if (isMatMaxSize()) {
		std::cout << "\nFirst diagonal: " << m_firstDiag.first << "|" << m_firstDiag.second << " | ";
		std::cout << "Second diagonal: " << m_seconDiag.first << "|" << m_seconDiag.second << "\n";
	}
	else
		std::cout << "\nThe matrix is not in a square form, so the diagonal scores will not be shown.\n";
}

//0 inside, -1 left margin, 1 right margin, 2 outside
int16_t Board::XBoundTest(int16_t x)
{
	if (x >= 0 && x < getRowCount()) return INSIDE_BOUND;

	if (x == -1 && getRowCount() < m_max_size) return TOP_BOUND;

	if (x == getRowCount() && getRowCount() < m_max_size) return BOTTOM_BOUND;

	return OUTSIDE_BOUND;
}

//0 inside, -1 top margin, 1 buttom margin, 2 outside
int16_t Board::YBoundTest(int16_t y)
{
	if (y >= 0 && y < getColCount()) return INSIDE_BOUND;

	if (y == -1 && getColCount() < m_max_size) return LEFT_BOUND;

	if (y == getColCount() && getColCount() < m_max_size) return RIGHT_BOUND;

	return OUTSIDE_BOUND;
}

//verifica daca il putem pune peste o carte; de pozitie in tabla daca este valida se ocupa setPos(); true daca putem pune;
bool Board::posPlaceTest(int16_t x, int16_t y, uint16_t val)
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
