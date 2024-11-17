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

//update 
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
		increaseOnColorDiagonalNoResize(x, y, col);
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

void Board::increaseOnColorDiagonalNoResize(uint16_t x, uint16_t y, char col)
{
	if (col == 'R') {
		if (m_board[x][y].empty()) {
			if (x == y) {
				m_firstDiag.first++;
			}
			if (x + y == m_max_size - 1) {
				m_seconDiag.first++;
			}
			return;
		}
		if (m_board[x][y].back().GetColor() == 'B') {
			if (x == y) {
				m_firstDiag.first++;
				m_firstDiag.second--;
			}
			if (x + y == m_max_size - 1) {
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

MinionCard Board::getCardOnPos(int16_t x, int16_t y) {//-1 esec
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return MinionCard{ 0,'\0' };
	if (m_board[x][y].empty())
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
	if (m_rowChecker[x].first + m_rowChecker[x].second == m_max_size)
		m_lineCnt++;
	if (m_colChecker[y].first + m_colChecker[y].second == m_max_size)
		m_lineCnt++;
	if (m_lineCnt == 2)
		std::cout << "#NOW YOU CAN USE THE EXPLOSION!#\n";

	return 0;
}

int16_t Board::setPosWaterfall(int16_t x, int16_t y, uint16_t val, char col)
{
	m_board[x][y].push_back({ val, col });
	return 0;
}

//1 esec, 0 succes
int16_t Board::removePos(int16_t x, int16_t y, uint16_t pos) {
	/*if (XBoundTest(x) != INSIDE_BOUND || YBoundTest(y) != INSIDE_BOUND)
		return 1;
	if (pos == 0)
		m_board[x][y].pop_front();
	if (pos == m_board[x][y].size() - 1)
		m_board[x][y].pop_back();
	else
		m_board[x][y].erase(m_board[x][y].begin() + pos);

	return 0;*/

	if (XBoundTest(x) != INSIDE_BOUND || YBoundTest(y) != INSIDE_BOUND)
		return 1;
	m_board[x][y].pop_back();
	return 0;
}

int16_t Board::removeStack(int16_t x, int16_t y)
{
	if (!m_board[x][y].empty())
	{
		m_board[x][y].clear();
		return 0;
	}
	return 1;
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

lineChecker& Board::getRowChecker()
{
	return this->m_rowChecker;
}

lineChecker& Board::getColChecker()
{
	return this->m_rowChecker;
}

resizeableMatrix& Board::getMatrix()
{
	return this->m_board;
}

//do position check outside of function or add new static card stack member and return it to represent nothing then check if == respective
cardStack& Board::getStackOnPos(uint16_t x, uint16_t y)
{
	return m_board[x][y];
}

uint16_t Board::getLineCount()
{
	return m_lineCnt;
}

//MAKE DEEP COPY OR USE CLONE_MATRIX METHOD
void Board::setMatrix(const resizeableMatrix& matrix)
{
	m_board = matrix;
}

void Board::updateColChecker(uint16_t y, uint16_t option)
{
	switch (option)
	{
	case RED_ADD:
		m_colChecker[y].first++;
		break;
	case RED_DEC:
		m_colChecker[y].first--;
		break;
	case BLUE_ADD:
		m_colChecker[y].second++;
		break;
	case BLUE_DEC:
		m_colChecker[y].second--;
		break;
	case RED_ADD_BLUE_DEC:
		m_colChecker[y].first++;
		m_colChecker[y].second--;
		break;
	case BLUE_ADD_RED_DEC:
		m_colChecker[y].first--;
		m_colChecker[y].second++;
		break;
	default:
		break;
	}
}

void Board::updateRowChecker(uint16_t x, uint16_t option)
{
	switch (option)
	{
	case RED_ADD:
		m_rowChecker[x].first++;
		break;
	case RED_DEC:
		m_rowChecker[x].first--;
		break;
	case BLUE_ADD:
		m_rowChecker[x].second++;
		break;
	case BLUE_DEC:
		m_rowChecker[x].second--;
		break;
	case RED_ADD_BLUE_DEC:
		m_rowChecker[x].first++;
		m_rowChecker[x].second--;
		break;
	case BLUE_ADD_RED_DEC:
		m_rowChecker[x].first--;
		m_rowChecker[x].second++;
		break;
	default:
		break;
	}
}

void Board::checkForUpdates()
{
	if (m_colChecker[0].first + m_colChecker[0].second == 0) {
		for (int i = 0; i < getRowCount() - 1; i++)
			m_board[i].pop_front();
		m_colChecker.pop_front();
	}
	if (m_colChecker[getColCount() - 1].first + m_colChecker[getColCount() - 1].second == 0) {
		for (int i = 0; i < getRowCount() - 1; i++)
			m_board[i].pop_back();
		m_colChecker.pop_back();
	}
	if (m_rowChecker[0].first + m_rowChecker[0].second == 0) {
		m_board.pop_front();
		m_rowChecker.pop_front();
	}
	if (m_rowChecker[getRowCount() - 1].first + m_rowChecker[getRowCount() - 1].second == 0) {
		m_board.pop_back();
		m_rowChecker.pop_back();
	}
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

//true if it is, false if not
bool Board::isBoardEmpty()
{
	return getColCount() == 1 && getRowCount() == 1 && m_board[0][0].empty();
}

//false good, true not good - sorry
bool Board::checkPosition(uint16_t x, uint16_t y)
{
	return x < 0 || x >= getRowCount() || y < 0 || y >= getColCount();
}

//false good, true not good - sorry
bool Board::checkPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	return x1 < 0 || x1 >= getRowCount() || x2 < 0 || x2 >= getRowCount() || y1 < 0 || y1 >= getColCount() || y2 < 0 || y2 >= getColCount();
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

//returns 1 if you cannot delete that 
bool Board::removeLeftMargin(uint16_t y)
{
	if (y < 0 || y > getColCount() - 1 || isBoardEmpty())
		return 1;
	for (int i = 0; i < getRowCount(); i++)
		m_board[i].pop_front();
	m_colChecker.pop_front();
	return 0;
}

bool Board::removeRightMargin(uint16_t y)
{
	if (y < 0 || y > getColCount() - 1 || isBoardEmpty())
		return 1;
	for (int i = 0; i < getRowCount(); i++)
		m_board[i].pop_back();
	m_colChecker.pop_back();
	return 0;
}

bool Board::removeTopMargin(uint16_t x)
{
	if (x < 0 || x > getRowCount() - 1 || isBoardEmpty())
		return 1;
	m_board.pop_front();
	m_rowChecker.pop_front();
	return 0;
}

bool Board::removeBottomMargin(uint16_t x)
{
	if (x < 0 || x > getRowCount() - 1 || isBoardEmpty())
		return 1;
	m_board.pop_front();
	m_rowChecker.pop_back();
	return 0;
}


void Board::cloneMatrix(const Board& from, Board& to)
{
	uint16_t nCols = from.m_colChecker.size();
	uint16_t nRows = from.m_rowChecker.size();

	to.m_board.resize(nRows);
	for (int i = 0; i < nRows; i++) {
		to.m_board[i].resize(nCols);
		for (int j = 0; j < nCols; j++) {
			for (auto& card : from.m_board[i][j]) {
				to.m_board[i][j].push_back(card);
			}
		}
	}
}

void Board::applyExplosionOnBoard(const ExplosionCard& explCard,Player& pl1, Player& pl2)
{
	explMap currExlpMap = explCard.GetExplosionMap();
	for (const auto& elem : currExlpMap)
	{
		auto[positionX,positionY] = elem.first;
		ReturnRemoveOrHoleCard effect = elem.second;
		
		switch (effect)
		{
		case ReturnRemoveOrHoleCard::RemoveCard:
			if (!m_board[positionX][positionY].empty())
			{
				MinionCard lastCard = m_board[positionX][positionY].back();
				m_board[positionX][positionY].pop_back();
			}
			break;
		case ReturnRemoveOrHoleCard::ReturnCard:
			if (!m_board[positionX][positionY].empty())
			{
				MinionCard lastCard = m_board[positionX][positionY].back();
				m_board[positionX][positionY].pop_back();
				if (lastCard.GetBelongsTo() == pl1.GetPlayerColor())
					pl1.returnMinionCardToHand(lastCard);
				else
					pl2.returnMinionCardToHand(lastCard);
			}
			break;
		case ReturnRemoveOrHoleCard::HoleCard:
			if (!m_board[positionX][positionY].empty())
			{
				while (m_board[positionX][positionY].size()>1)
				{
					m_board[positionX][positionY].pop_back();
				}
				m_board[positionX][positionY].back().SetCardType(CardType::HoleCard);
			}
			break;
		case ReturnRemoveOrHoleCard::Default:
			break;
		default:
			break;
		}	
	}
}
