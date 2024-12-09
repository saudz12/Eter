#include "Board.h"

Board::Board(uint16_t size)
	: m_lineCnt{ 0 }, m_max_size{ size }, m_firstDiag{ 0, 0 }, m_seconDiag{ 0, 0 }, m_matrix(ResizeableMatrix()), m_rowChecker(LineChecker()), m_colChecker(LineChecker()), m_reachedMaxSize{ false }
{
	m_matrix.push_back(Line());
	m_matrix[0].push_back(CardStack());
	m_rowChecker.emplace_back(0, 0);
	m_colChecker.emplace_back(0, 0);
}

Board::Board()
	: m_lineCnt{ 0 }, m_max_size{ 3 }, m_firstDiag{ 0, 0 }, m_seconDiag{ 0, 0 }, m_matrix(ResizeableMatrix()), m_rowChecker(LineChecker()), m_colChecker(LineChecker()), m_reachedMaxSize{ false }
{
	m_matrix.push_back(Line());
	m_matrix[0].push_back(CardStack());
	m_rowChecker.emplace_back(0, 0);
	m_colChecker.emplace_back(0, 0);
}

//true if yes, false if no
bool Board::isMatMaxSize()
{
	return getColCount() == m_max_size && getRowCount() == m_max_size;
}

//update 
void Board::increaseOnColorSides(uint16_t x, uint16_t y, Colours col)
{
	if (col == Colours::RED) {
		if (!m_matrix[x][y].empty())
			if (m_matrix[x][y].back().GetColor() == Colours::BLUE) {
				m_rowChecker[x].second--;
				m_colChecker[y].second--;
			}
			else
				return;
		m_rowChecker[x].first++;
		m_colChecker[y].first++;
	}
	else {
		if (!m_matrix[x][y].empty())
			if (m_matrix[x][y].back().GetColor() == Colours::RED) {
				m_rowChecker[x].second++;
				m_colChecker[y].second++;

				return;
			}
			else
				return;
		m_rowChecker[x].second++;
		m_colChecker[y].second++;
	}
}

void Board::increaseOnColorColumn(uint16_t x, uint16_t y, Colours col)
{
	if (col == Colours::RED) {
		if (!m_matrix[x][y].empty())
			if (m_matrix[x][y].back().GetColor() == Colours::BLUE) {
				m_colChecker[y].second--;
			}
			else
				return;
		m_colChecker[y].first++;
	}
	else {
		if (!m_matrix[x][y].empty())
			if (m_matrix[x][y].back().GetColor() == Colours::RED) {
				m_colChecker[y].first--;
			}
			else
				return;
		m_colChecker[y].second++;
	}
}

void Board::increaseOnColorRow(uint16_t x, uint16_t y, Colours col)
{
	if (col == Colours::RED) {
		if (!m_matrix[x][y].empty())
			if (m_matrix[x][y].back().GetColor() == Colours::BLUE) {
				m_rowChecker[x].second--;
			}
			else
				return;
		m_rowChecker[x].first++;
	}
	else {
		if (!m_matrix[x][y].empty())
			if (m_matrix[x][y].back().GetColor() == Colours::RED) {
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
void Board::increaseOnColorDiagonal(uint16_t x, uint16_t y, Colours col)
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
		if (!m_matrix[i][i].empty()) {
			if (m_matrix[i][i].back().GetColor() == Colours::RED)
				m_firstDiag.first++;
			else
				m_firstDiag.second++;
		}
		if (!m_matrix[i][m_max_size - i - 1].empty()) {
			if (m_matrix[i][m_max_size - i - 1].back().GetColor() == Colours::RED)
				m_seconDiag.first++;
			else
				m_seconDiag.second++;
		}
	}
	if (x == y)
	{
		if (col == Colours::RED)
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
		if (col == Colours::RED)
		{
			m_seconDiag.first++;
		}
		else
		{
			m_seconDiag.second++;
		}
	}
}

void Board::increaseOnColorDiagonalNoResize(uint16_t x, uint16_t y, Colours col)
{
	if (col == Colours::RED) {
		if (m_matrix[x][y].empty()) {
			if (x == y) {
				m_firstDiag.first++;
			}
			if (x + y == m_max_size - 1) {
				m_seconDiag.first++;
			}
			return;
		}
		if (m_matrix[x][y].back().GetColor() == Colours::BLUE) {
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
		if (m_matrix[x][y].empty()) {
			if (x == y) {
				m_firstDiag.second++;
			}
			if (x + y == m_max_size - 1) {
				m_seconDiag.second++;
			}
			return;
		}
		if (m_matrix[x][y].back().GetColor() == Colours::RED) {
			if (x == y) {
				m_firstDiag.first--;
				m_firstDiag.second++;
			}
			if (x + y == m_max_size - 1) {
				m_seconDiag.first--;
				m_seconDiag.second++;
			}
		}
	}
}

MinionCard& Board::getCardOnPos(int16_t x, int16_t y) {//-1 esec
	return m_matrix[x][y].back();
}

int16_t Board::setPos(int16_t& x, int16_t& y, const MinionCard& card, Player& p) {
	const int boundCondX = XBoundTest(x);
	const int boundCondY = YBoundTest(y);

	if (boundCondX == OUTSIDE_BOUND || boundCondY == OUTSIDE_BOUND)
		return 1;
	if ((x != 0 || y != 0) && isBoardEmpty()) //special case for emmpty matrix
		return 1;

	if (boundCondX == INSIDE_BOUND && boundCondY == INSIDE_BOUND || x != 0 && y == 0 && isBoardEmpty()) {
		if (!posPlaceTest(x, y, card)) {
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

	increaseOnColorRow(x, y, card.GetColor());
	increaseOnColorColumn(x, y, card.GetColor());

	if (!isMatMaxSize())
		m_reachedMaxSize = false;
	else if (x == y || x + y == m_max_size - 1)
		increaseOnColorDiagonal(x, y, card.GetColor());

	if (!m_matrix[x][y].empty() && m_matrix[x][y].back().GetIsIllusionCard())
	{
		m_matrix[x][y].back().SetIsIllusionCard(false);
		if (card.GetValue() > m_matrix[x][y].back().GetValue())
		{
			m_matrix[x][y].push_back(card);
		}
		else
		{
			p.addToRemovedCards(card);
			if (card.GetColor() != m_matrix[x][y].back().GetColor())
			{
				if (card.GetColor() == Colours::RED)
				{
					updateColChecker(y, BLUE_ADD_RED_DEC);
					updateRowChecker(x, BLUE_ADD_RED_DEC);
					if (x == y)
						updateFirstDiagChecker(BLUE_ADD_RED_DEC);
					if (x == m_matrix.size() - y - 1)
						updateSeconDiagChecker(BLUE_ADD_RED_DEC);
				}
				else
				{
					{
						updateColChecker(y, RED_ADD_BLUE_DEC);
						updateRowChecker(x, RED_ADD_BLUE_DEC);
						if (x == y)
							updateFirstDiagChecker(RED_ADD_BLUE_DEC);
						if (x == m_matrix.size() - y - 1)
							updateSeconDiagChecker(RED_ADD_BLUE_DEC);
					}
				}
			}
		}
	}
	else
		m_matrix[x][y].push_back(card);

	if (m_rowChecker[x].first + m_rowChecker[x].second == m_max_size)
		m_lineCnt++;
	if (m_colChecker[y].first + m_colChecker[y].second == m_max_size)
		m_lineCnt++;
	if (m_lineCnt == 2)
		std::cout << "#NOW YOU CAN USE THE EXPLOSION!#\n";

	return 0;
}

int16_t Board::setPosWaterfall(int16_t x, int16_t y, const MinionCard& card)
{
	m_matrix[x][y].push_back(card);
	return 0;
}



BoardErrors Board::CheckPos(int16_t _x, int16_t _y)
{
	if (_x == -1 && m_max_size == getRowCount() || _x < -1)
		return BoardErrors::_OUTSIDE_BOUND;
	if (_x == getRowCount() && getRowCount() == m_max_size || _x > getRowCount())
		return BoardErrors::_OUTSIDE_BOUND;
	if (_y == -1 && m_max_size == getColCount() || _y < -1)
		return BoardErrors::_OUTSIDE_BOUND;
	if (_y == getColCount() && getColCount() == m_max_size || _y > getColCount())
		return BoardErrors::_OUTSIDE_BOUND;

	return BoardErrors::_INSIDE_BOUND;
}

StackConditions Board::CheckStackCondition(int16_t _x, int16_t _y)
{
	if (m_matrix[_x][_y].empty())
		return StackConditions::_EMPTY;
	if (m_matrix[_x][_y].back().CheckIsHole())
		return StackConditions::_HOLE;
	return StackConditions::_POPULATED;
}

BoardChanges Board::GetChanges(int16_t _x, int16_t _y)
{
	if (isBoardEmpty())
		return BoardChanges::_EMPTY_BOARD;

	if (_x == -1 && _y == -1)
		return BoardChanges::_TOP_LEFT_BOUND;
	if (_x == -1 && _y == m_max_size)
		return BoardChanges::_TOP_RIGHT_BOUND;
	if (_x == m_max_size && _y == -1)
		return BoardChanges::_BOT_LEFT_BOUND;
	if (_x == -1 && _y == m_max_size)
		return BoardChanges::_BOT_RIGHT_BOUND;

	if (_x == -1)
		return BoardChanges::_TOP_BOUND;
	if (_x == m_max_size)
		return BoardChanges::_BOT_BOUND;
	if (_y == -1)
		return BoardChanges::_LEFT_BOUND;
	if (_y == m_max_size)
		return BoardChanges::_RIGHT_BOUND;

	return BoardChanges::_NO_CHANGES;
}

void Board::ExtendBoard(BoardChanges _flag)
{
	switch (_flag)
	{
	case BoardChanges::_EMPTY_BOARD:
		addLineOnTop(); //anything really -- rewrite the board in such way that the board will be initialised FULLY empty so it will not need coordonates for the first palcement when fully empty.
		break;
	case BoardChanges::_TOP_BOUND:
		addLineOnTop();
		break;
	case BoardChanges::_BOT_BOUND:
		addLineOnBottom();
		break;
	case BoardChanges::_LEFT_BOUND:
		addLineToLeft();
		break;
	case BoardChanges::_RIGHT_BOUND:
		addLineToRight();
		break;
	case BoardChanges::_TOP_LEFT_BOUND:
		addLineOnTop();
		addLineToLeft();
		break;
	case BoardChanges::_TOP_RIGHT_BOUND:
		addLineOnTop();
		addLineToRight();
		break;
	case BoardChanges::_BOT_LEFT_BOUND:
		addLineOnBottom();
		addLineToLeft();
		break;
	case BoardChanges::_BOT_RIGHT_BOUND:
		addLineOnBottom();
		addLineToRight();
		break;
	default:
		break;
	}
}

void Board::PlaceCard(Player& _active, int16_t _x, int16_t _y, int16_t _val, BoardChanges _flag)
{
	ExtendBoard(_flag);

	m_matrix[_x][_y].push_back(_active.MoveCard(_val));

	//update col, row and diagonal -- rewrite them accordingly
}

void Board::RemoveCard(int16_t _x, int16_t _y, int16_t _pos)
{
	for (int i = _pos; i < m_matrix[_x][_y].size() - 1; i++)
		m_matrix[_x][_y][i] = std::move(m_matrix[_x][_y][i + 1]);
}

void Board::CreateHole(int16_t _x, int16_t _y)
{
	m_matrix[_x][_y].clear();
	m_matrix[_x][_y].push_back(MinionCard::CreateHoleCard());
}

void Board::RemoveLine(int16_t _line, LineType _type)
{
	switch (_type)
	{
	case LineType::TYPE_COLUMN:
		
		break;
	case LineType::TYPE_ROW:
		break;
	case LineType::_INVALID_LINE_TYPE:
		break;
	default:
		break;
	}
}

void Board::RemoveRow(int16_t _line)
{
	if (_line == 0)
		removeTopMargin();
	else if (_line == getRowCount() - 1)
		removeBottomMargin();
	else{
		for (int i = 0; i < getColCount(); i++)
			m_matrix[_line][i].clear();
		m_rowChecker[_line] = {0, 0};
	}
	
}

void Board::RemoveColumn(int16_t _line)
{
	if (_line == 0)
		removeLeftMargin();
	else if (_line == getColCount() - 1)
		removeRightMargin();
	else {
		for (int i = 0; i < getRowCount(); i++)
			m_matrix[i][_line].clear();
		m_colChecker[_line] = { 0, 0 };
	}
}

bool Board::LineContainsColour(int16_t _line, LineType _type, Colours _col)
{
	LineChecker& checker = m_rowChecker;
	if (_type == LineType::TYPE_COLUMN)
		checker = m_colChecker;

	if (_col == Colours::RED)
		return checker[_line].first != 0;
	return checker[_line].second != 0;
}

int16_t Board::GetNrOfCardsOnLine(int16_t _line, LineType _type)
{
	switch (_type)
	{
	case LineType::TYPE_ROW:
		return m_rowChecker[_line].first + m_rowChecker[_line].second;
	case LineType::TYPE_COLUMN:
		return m_colChecker[_line].first + m_colChecker[_line].second;
	default:
		return 0;
	}
}

void Board::SwitchStacks(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD, Colours _colour)
{
	if (_colour == Colours::RED)
	{
		if (_xS != _xD)
		{
			m_rowChecker[_xS].first--;
			m_rowChecker[_xD].first++;
		}

		if (_yS != _yD)
		{
			m_colChecker[_yS].first--;
			m_colChecker[_yD].first++;
		}
	}
	else
	{
		if (_xS != _xD)
		{
			m_rowChecker[_xS].second--;
			m_rowChecker[_xD].second++;
		}
		if (_yS != _yD)
		{
			m_colChecker[_yS].second--;
			m_colChecker[_yD].second++;
		}
	}

	m_matrix[_xD][_yD] = std::move(m_matrix[_xS][_yS]);
}

MinionCard Board::ViewTop(int16_t _x, int16_t _y)
{
	if (m_matrix[_x][_y].empty())
		return MinionCard();
	return m_matrix[_x][_y].back();
}

//1 esec, 0 succes
int16_t Board::removePos(int16_t x, int16_t y) {
	if (XBoundTest(x) != INSIDE_BOUND || YBoundTest(y) != INSIDE_BOUND)
		return 1;

	if (m_matrix[x][y].empty())
		return 1;

	if (x == y)
	{
		if (m_matrix[x][y].back().GetColor() == Colours::RED)
			updateFirstDiagChecker(RED_DEC);
		else
			updateFirstDiagChecker(BLUE_DEC);
	}

	if (x == m_matrix.size() - y - 1)
	{
		if (m_matrix[x][y].back().GetColor() == Colours::RED)
			updateSeconDiagChecker(RED_DEC);
		else
			updateSeconDiagChecker(BLUE_DEC);
	}

	if (m_matrix[x][y].back().GetColor() == Colours::RED)
	{
		updateRowChecker(x, RED_DEC);
		updateColChecker(y, RED_DEC);
	}
	else
	{
		updateRowChecker(x, BLUE_DEC);
		updateColChecker(y, BLUE_DEC);
	}

	m_matrix[x][y].pop_back();

	if (!m_matrix[x][y].empty())
	{
		if (m_matrix[x][y].back().GetColor() == Colours::RED)
		{
			if (x == y)
			{
				updateFirstDiagChecker(RED_ADD);
			}

			if (x == m_matrix.size() - y - 1)
			{
				updateSeconDiagChecker(RED_ADD);
			}

			updateRowChecker(x, RED_ADD);
			updateColChecker(y, RED_ADD);
		}
		else
		{
			if (x == y)
			{
				updateFirstDiagChecker(BLUE_ADD);
			}

			if (x == m_matrix.size() - y - 1)
			{
				updateSeconDiagChecker(BLUE_ADD);
			}

			updateRowChecker(x, BLUE_ADD);
			updateColChecker(y, BLUE_ADD);
		}
	}

	return 0;
}

//1 esec, 0 succes
int16_t Board::removeStack(int16_t x, int16_t y)
{
	if (!m_matrix[x][y].empty())
	{
		if (m_matrix[x][y].back().GetColor() == Colours::RED)
		{
			if (x == y)
			{
				updateFirstDiagChecker(RED_DEC);
			}

			if (x == m_matrix.size() - y - 1)
			{
				updateSeconDiagChecker(RED_DEC);
			}

			updateColChecker(y, RED_DEC);
			updateRowChecker(x, RED_DEC);
		}
		else if (m_matrix[x][y].back().GetColor() == Colours::BLUE)
		{
			if (x == y)
			{
				updateFirstDiagChecker(BLUE_DEC);
			}

			if (x == m_matrix.size() - y - 1)
			{
				updateSeconDiagChecker(BLUE_DEC);
			}

			updateColChecker(y, BLUE_DEC);
			updateRowChecker(x, BLUE_DEC);
		}
		m_matrix[x][y].clear();
		return 0;
	}
	return 1;
}

Colours Board::entityWon(int16_t x, int16_t y, Colours col)
{
	return Colours();
}

Colours Board::checkWin()
{
	if (this->isMatMaxSize() == false)
		return Colours::INVALID_COL;
	for (const auto& diff : m_colChecker)
	{
		if (diff.first == 3)
			return Colours::RED;
		if (diff.second == 3)
			return Colours::BLUE;
	}
	for (const auto& diff : m_rowChecker)
	{
		if (diff.first == 3)
			return Colours::RED;
		if (diff.second == 3)
			return Colours::BLUE;
	}

	return Colours::INVALID_COL;
}

Colours Board::checkWin(int16_t x, int16_t y, Colours col)
{
	if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
		return Colours::INVALID_COL;
	if (col == Colours::RED) {
		if (m_rowChecker[x].first == m_max_size || m_colChecker[y].first == m_max_size || m_firstDiag.first == m_max_size || m_seconDiag.first == m_max_size)
			return Colours::RED;
	}
	else {
		if (m_rowChecker[x].second == m_max_size || m_colChecker[y].second == m_max_size || m_firstDiag.second == m_max_size || m_seconDiag.second == m_max_size)
			return Colours::BLUE;
	}
	return Colours::INVALID_COL;
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

LineChecker& Board::getRowChecker()
{
	return this->m_rowChecker;
}

LineChecker& Board::getColChecker()
{
	return this->m_colChecker;
}

ResizeableMatrix& Board::getMatrix()
{
	return this->m_matrix;
}

CardStack& Board::getStackOnPos(uint16_t x, uint16_t y)
{
	return m_matrix[x][y];
}

uint16_t Board::getLineCount()
{
	return m_lineCnt;
}

void Board::setMatrix(const ResizeableMatrix& matrix)
{
	m_matrix = matrix;
}

void Board::updateFirstDiagChecker(uint16_t option)
{
	switch (option)
	{
	case RED_ADD:
		m_firstDiag.first++;
		break;
	case RED_DEC:
		m_firstDiag.first--;
		break;
	case BLUE_ADD:
		m_firstDiag.second++;
		break;
	case BLUE_DEC:
		m_firstDiag.second--;
		break;
	case RED_ADD_BLUE_DEC:
		m_firstDiag.first++;
		m_firstDiag.second--;
		break;
	case BLUE_ADD_RED_DEC:
		m_firstDiag.first--;
		m_firstDiag.second++;
		break;
	case ZERO:
		m_firstDiag.first = 0;
		m_firstDiag.second = 0;
		break;
	default:
		break;
	}
}

void Board::updateSeconDiagChecker(uint16_t option)
{
	switch (option)
	{
	case RED_ADD:
		m_seconDiag.first++;
		break;
	case RED_DEC:
		m_seconDiag.first--;
		break;
	case BLUE_ADD:
		m_seconDiag.second++;
		break;
	case BLUE_DEC:
		m_seconDiag.second--;
		break;
	case RED_ADD_BLUE_DEC:
		m_seconDiag.first++;
		m_seconDiag.second--;
		break;
	case BLUE_ADD_RED_DEC:
		m_seconDiag.first--;
		m_seconDiag.second++;
		break;
	case ZERO:
		m_seconDiag.first = 0;
		m_seconDiag.second = 0;
		break;
	default:
		break;
	}
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
	case ZERO:
		m_colChecker[y].first = 0;
		m_colChecker[y].second = 0;
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
	case ZERO:
		m_rowChecker[x].first = 0;
		m_rowChecker[x].second = 0;
		break;
	default:
		break;
	}
}

void Board::shiftLine(uint16_t start, uint16_t end, int16_t ratio, uint16_t lineNo, uint16_t orientation)
{
	auto quickCheck = [&orientation](uint16_t a, uint16_t b) {return orientation ? a : b; };

	uint16_t lastX = quickCheck(lineNo, end);
	uint16_t lastY = quickCheck(end, lineNo);

	uint16_t firstX = quickCheck(lineNo, start);
	uint16_t firstY = quickCheck(start, lineNo);

	for (int i = start; i != end; i += ratio)
	{
		uint16_t currX = quickCheck(lineNo, i);
		uint16_t currY = quickCheck(i, lineNo);

		if (m_matrix[currX][currY].back().GetColor() == Colours::RED)
		{
			updateRowChecker(currX, RED_DEC);
			updateColChecker(currY, RED_DEC);
		}
		else
		{
			updateRowChecker(currX, BLUE_DEC);
			updateColChecker(currY, BLUE_DEC);
		}

		uint16_t nextX = quickCheck(lineNo, i + ratio);
		uint16_t nextY = quickCheck(i + ratio, lineNo);

		if (m_matrix[nextX][nextY].back().GetColor() == Colours::RED)
		{
			updateRowChecker(currX, RED_ADD);
			updateColChecker(currY, RED_ADD);
		}
		else
		{
			updateRowChecker(currX, BLUE_ADD);
			updateColChecker(currY, BLUE_ADD);
		}
	}

	if (m_matrix[lastX][lastY].back().GetColor() == Colours::RED)
	{
		updateRowChecker(lastX, RED_DEC);
		updateColChecker(lastY, RED_DEC);
	}
	else
	{
		updateRowChecker(lastX, BLUE_DEC);
		updateColChecker(lastY, BLUE_DEC);
	}

	for (int i = start; i != end; i += ratio)
	{
		uint16_t currX = quickCheck(lineNo, i);
		uint16_t currY = quickCheck(i, lineNo);

		uint16_t nextX = quickCheck(lineNo, i + ratio);
		uint16_t nextY = quickCheck(i + ratio, lineNo);

		m_matrix[currX][currY] = std::move(m_matrix[nextX][nextY]);
	}
}

void Board::checkForUpdates()
{
	while (!m_colChecker.empty() && m_colChecker.front().first == 0 && m_colChecker.front().second == 0) {
		removeLeftMargin();
	}

	while (!m_colChecker.empty() && m_colChecker.back().first == 0 && m_colChecker.back().second == 0) {
		removeRightMargin();
	}

	while (!m_rowChecker.empty() && m_rowChecker.front().first == 0 && m_rowChecker.front().second == 0) {
		removeTopMargin();
	}

	while (!m_rowChecker.empty() && m_rowChecker.back().first == 0 && m_rowChecker.back().second == 0) {
		removeBottomMargin();
	}

	if (m_colChecker.size() + m_rowChecker.size() == 0) {
		m_colChecker.emplace_back(0, 0);
		m_rowChecker.emplace_back(0, 0);
		m_matrix.push_back(Line());
		m_matrix[0].push_back(CardStack());
	}
}

bool Board::isBoardFilled()
{
	if (!isMatMaxSize())
		return false;

	for (int i = 0; i < m_max_size; i++)
		for (int j = 0; j < m_max_size; j++)
			if (m_matrix[i][j].empty())
				return false;
	return true;
}

//true if it is, false if not
bool Board::isBoardEmpty()
{
	return getColCount() == 1 && getRowCount() == 1 && m_matrix[0][0].empty();
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
			if (!m_matrix[i][j].empty())
			{
				/*if (m_board[i][j].back().GetColor() == 'R')
					std::cout << "\033[33m";
				else
					std::cout << "\033[34m";*/
				std::cout << m_matrix[i][j].back() << " ";
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
//cartea eter si iluzia se pot pune doar pe spatiile goale
bool Board::posPlaceTest(int16_t x, int16_t y, const MinionCard& card)
{
	if (!m_matrix[x][y].empty())
	{
		if (card.GetIsEterCard() || card.GetIsIllusionCard())
			return false;
		if (m_matrix[x][y].back().GetIsEterCard())
			return false;
		if (card.GetValue() <= m_matrix[x][y].back().GetValue() && !m_matrix[x][y].back().GetIsIllusionCard())
			return false;
	}
	return true;
}

void Board::addLineToLeft()
{
	for (int i = 0; i < getRowCount(); i++) {
		m_matrix[i].push_front(CardStack());
	}
	m_colChecker.emplace_front(0, 0);
}

void Board::addLineToRight()
{
	for (int i = 0; i < getRowCount(); i++) {
		m_matrix[i].push_back(CardStack());
	}
	m_colChecker.emplace_back(0, 0);
}

void Board::addLineOnTop()
{
	m_matrix.push_front(Line(getColCount()));
	m_rowChecker.emplace_front(0, 0);
}

void Board::addLineOnBottom()
{
	m_matrix.push_back(Line(getColCount()));
	m_rowChecker.emplace_back(0, 0);
}

void Board::removeLeftMargin()
{
	for (int i = 0; i < getRowCount(); i++)
		m_matrix[i].pop_front();
	m_colChecker.pop_front();
}

void Board::removeRightMargin()
{
	for (int i = 0; i < getRowCount(); i++)
			m_matrix[i].pop_back();
	m_colChecker.pop_back();
}

void Board::removeTopMargin()
{
	m_matrix.pop_front();
	m_rowChecker.pop_front();
}

void Board::removeBottomMargin()
{
	m_matrix.pop_back();
	m_rowChecker.pop_back();
}

bool Board::removeRow(uint16_t x)
{
	if (x < 0 || x > getRowCount() - 1 || isBoardEmpty())
		return 1;
	for (int16_t i = 0; i < getColCount(); ++i)
	{
		if (m_matrix[x][i].back().GetColor() == Colours::RED)
			m_colChecker[i].first -= 1;
		else
			m_colChecker[i].second -= 1;
	}
	m_matrix.erase(m_matrix.begin() + x);
	m_rowChecker.erase(m_rowChecker.begin()+x);
	
	return 0;
}

bool Board::removeColumn(uint16_t y)
{
	if (y < 0 || y > getColCount() - 1 || isBoardEmpty())
		return 1;
	for (int16_t i = 0; i < getRowCount(); ++i)
	{
		if (m_matrix[i][y].back().GetColor() == Colours::RED)
			m_rowChecker[i].first -= 1;
		else
			m_rowChecker[i].second -= 1;
	}
	for (int16_t i = 0; i < getRowCount(); i++)
		m_matrix[i].erase(m_matrix[i].begin() + y);
	m_colChecker.erase(m_colChecker.begin() + y);
	return 0;
}

void Board::cloneMatrix(const Board& from, Board& to)
{
	uint16_t nCols = from.m_colChecker.size();
	uint16_t nRows = from.m_rowChecker.size();

	to.m_rowChecker = from.m_rowChecker;
	to.m_colChecker = from.m_colChecker;
	to.m_firstDiag = from.m_firstDiag;
	to.m_seconDiag = from.m_seconDiag;

	to.m_matrix.resize(nRows);
	for (int i = 0; i < nRows; i++) {
		to.m_matrix[i].resize(nCols);
		for (int j = 0; j < nCols; j++) {
			for (auto& card : from.m_matrix[i][j]) {
				to.m_matrix[i][j].push_back(card);
			}
		}
	}
}

void Board::applyExplosionOnBoard(const ExplosionCard& explCard, Player& pl1, Player& pl2)
{
	explMap currExlpMap = explCard.GetExplosionMap();
	for (const auto& elem : currExlpMap)
	{
		auto[positionX,positionY] = elem.first;
		ReturnRemoveOrHoleCard effect = elem.second;
		
		switch (effect)
		{
		case ReturnRemoveOrHoleCard::RemoveCard:
			if (!m_matrix[positionX][positionY].empty() && !m_matrix[positionX][positionY].back().GetIsEterCard())
			{
				MinionCard lastCard = m_matrix[positionX][positionY].back();
				lastCard.SetIsIllusionCard(false);
				removePos(positionX, positionY);
				if (lastCard.GetColor() == pl1.GetPlayerColor())
					pl1.addToRemovedCards(lastCard);
				else
					pl2.addToRemovedCards(lastCard);

			}
			break;
		case ReturnRemoveOrHoleCard::ReturnCard:
			if (!m_matrix[positionX][positionY].empty() && !m_matrix[positionX][positionY].back().GetIsEterCard())
			{
				MinionCard lastCard = m_matrix[positionX][positionY].back();
				lastCard.SetIsIllusionCard(false);
				removePos(positionX, positionY);
				if (lastCard.GetColor() == pl1.GetPlayerColor())
					pl1.returnMinionCardToHand(lastCard);
				else
					pl2.returnMinionCardToHand(lastCard);
			}
			break;
		case ReturnRemoveOrHoleCard::HoleCard:
			if (!m_matrix[positionX][positionY].empty() && !m_matrix[positionX][positionY].back().GetIsEterCard())
			{
				removeStack(positionX, positionY);

				MinionCard holeCard(0, Colours::INVALID_COL, false);
				holeCard.SetCardType(CardType::HoleCard);

				m_matrix[positionX][positionY].push_back(holeCard);
			}
			break;
		case ReturnRemoveOrHoleCard::Default:
			break;
		default:
			break;
		}	
	}
	checkForUpdates();
}
