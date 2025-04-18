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
void Board::UpdateOnColor(uint16_t _x, uint16_t _y, Colours _col, OrientationType _type, CardAction _action)
{ 

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
		AddLineOnTop();
	}

	if (boundCondY == LEFT_BOUND) {
		y = 0;
		AddLineToLeft();
	}

	if (boundCondX == BOTTOM_BOUND) {
		AddLineOnBottom();
	}

	if (boundCondY == RIGHT_BOUND) {
		AddLineToRight();
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
		qDebug() << "#NOW YOU CAN USE THE EXPLOSION!#\n";

	return 0;
}

int16_t Board::setPosWaterfall(int16_t x, int16_t y, const MinionCard& card)
{
	m_matrix[x][y].push_back(card);
	return 0;
}

StackConditions Board::CheckStackCondition(int16_t _x, int16_t _y)
{
	if (m_matrix[_x][_y].empty())
		return StackConditions::EMPTY;
	if (m_matrix[_x][_y].back().CheckIsHole())
		return StackConditions::HOLE;
	if (m_matrix[_x][_y].back().GetIsEterCard())
		return StackConditions::ETER;
	return StackConditions::POPULATED;
}

BoardErrors Board::CheckPos(int16_t _x, int16_t _y)
{
	if (_x < -1 || _y < -1 || _x > getRowCount() || _y > getColCount())
		return BoardErrors::_OUTSIDE_BOUND;
	if (getRowCount() == m_max_size && (_x == -1 || _x == getRowCount()))
		return BoardErrors::_OUTSIDE_BOUND;
	if (getColCount() == m_max_size && (_y == -1 || _y == getColCount()))
		return BoardErrors::_OUTSIDE_BOUND;

	return BoardErrors::_INSIDE_BOUND;
}

BoardErrors Board::CanPlace(int16_t _x, int16_t _y, int16_t _val)
{
	if (CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return BoardErrors::_OUTSIDE_BOUND;

	if (_x == -1 || _y == -1 || _x == getRowCount() || _y == getColCount())
		return BoardErrors::_NO_ERRORS;

	StackConditions tryPlaceOnStack = CheckStackCondition(_x, _y);
	switch (tryPlaceOnStack)
	{
	case StackConditions::POPULATED:
		if (m_matrix[_x][_y].back().GetIsIllusionCard())
		{
			if (_val > m_matrix[_x][_y].back().GetValue())
				return BoardErrors::ILLUSION_PROPERTY;
			else
				return BoardErrors::ILLUSION_PROPERTY;
		}
		else if (m_matrix[_x][_y].back().GetValue() > _val)
			return BoardErrors::_INVALID_VAL;
		else
			return BoardErrors::_NO_ERRORS;
		break;
	case StackConditions::HOLE:
		return BoardErrors::_HOLE_PROPERTY;
	case StackConditions::ETER:
		return BoardErrors::_ETER_PROPERTY;
	}

	return BoardErrors::_NO_ERRORS;
}


BoardChanges Board::GetChangeFlag(int16_t _x, int16_t _y)
{
	if (isBoardEmpty())
		return BoardChanges::_EMPTY_BOARD;

	if (_x == -1 && _y == -1)
		return BoardChanges::_TOP_LEFT_BOUND;
	if (_x == -1 && _y == getColCount())
		return BoardChanges::_TOP_RIGHT_BOUND;
	if (_x == getRowCount() && _y == -1)
		return BoardChanges::_BOT_LEFT_BOUND;
	if (_x == getRowCount() && _y == getColCount())
		return BoardChanges::_BOT_RIGHT_BOUND;

	if (_x == -1)
		return BoardChanges::_TOP_BOUND;
	if (_x == getRowCount())
		return BoardChanges::_BOT_BOUND;
	if (_y == -1)
		return BoardChanges::_LEFT_BOUND;
	if (_y == getColCount())
		return BoardChanges::_RIGHT_BOUND;

	return BoardChanges::_NO_CHANGES;
}

void Board::ExtendBoard(BoardChanges _flag)
{
	switch (_flag)
	{
	case BoardChanges::_EMPTY_BOARD:
		//AddLineOnTop(); //anything really -- rewrite the board in such way that the board will be initialised FULLY empty so it will not need coordonates for the first palcement when fully empty.
		break;
	case BoardChanges::_TOP_BOUND:
		AddLineOnTop();
		break;
	case BoardChanges::_BOT_BOUND:
		AddLineOnBottom();
		break;
	case BoardChanges::_LEFT_BOUND:
		AddLineToLeft();
		break;
	case BoardChanges::_RIGHT_BOUND:
		AddLineToRight();
		break;
	case BoardChanges::_TOP_LEFT_BOUND:
		AddLineOnTop();
		AddLineToLeft();
		break;
	case BoardChanges::_TOP_RIGHT_BOUND:
		AddLineOnTop();
		AddLineToRight();
		break;
	case BoardChanges::_BOT_LEFT_BOUND:
		AddLineOnBottom();
		AddLineToLeft();
		break;
	case BoardChanges::_BOT_RIGHT_BOUND:
		AddLineOnBottom();
		AddLineToRight();
		break;
	default:
		break;
	}
}

void Board::PlaceCard(MinionCard&& _toPlace, int16_t _x, int16_t _y)
{
	if (isBoardEmpty()) {
		m_matrix[0][0].emplace_back(_toPlace);
		if (_toPlace.GetColor() == Colours::RED)
		{
			m_rowChecker[0].first = 1;
			m_colChecker[0].first = 1;
		}
		else
		{
			m_rowChecker[0].second = 1;
			m_colChecker[0].second = 1;
		}
		return;
	}

	ExtendBoard(GetChangeFlag(_x, _y));
	if (_x == -1)
		_x = 0;
	if (_y == -1)
		_y = 0;

	if (!m_matrix[_x][_y].empty()) {
		if (m_matrix[_x][_y].back().GetIsIllusionCard() && 
			m_matrix[_x][_y].back().GetColor() != _toPlace.GetColor())
			if(m_matrix[_x][_y].back().GetValue() >= _toPlace.GetValue())
				return;
	}
	
	increaseOnColorRow(_x, _y, _toPlace.GetColor());
	increaseOnColorColumn(_x, _y, _toPlace.GetColor());
	if (!isMatMaxSize())
		m_reachedMaxSize = false;
	else if (_x == _y || _x + _y == m_max_size - 1)
		increaseOnColorDiagonal(_x, _y, _toPlace.GetColor());

	m_matrix[_x][_y].push_back(_toPlace);
}

MinionCard&& Board::RemoveTop(int16_t _x, int16_t _y)
{
	MinionCard&& toMove = std::move(m_matrix[_x][_y].back());
	m_matrix[_x][_y].pop_back();
	return std::move(toMove);
}

MinionCard&& Board::RemoveCard(int16_t _x, int16_t _y, int16_t _pos)
{
	/*for (int i = _pos; i < m_matrix[_x][_y].size() - 1; i++)
		m_matrix[_x][_y][i] = std::move(m_matrix[_x][_y][i + 1]);*/

	MinionCard&& toMove = std::move(m_matrix[_x][_y][_pos]);
	m_matrix[_x][_y].erase(m_matrix[_x][_y].begin() + _pos);
	return std::move(toMove);
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

bool Board::ShiftLine(int16_t _line, LineType _type, Directions _direction)
{
	//some necesarry checks just so
	if (_type == LineType::_INVALID_LINE_TYPE)
		return false;
	if (_direction == Directions::INVALID_DIR)
		return false;

	if (_line < 0 || _line >= std::max(getColCount(), getLineCount()))
		return false;

	if (_type == LineType::TYPE_ROW && _direction != Directions::DIR_LEFT && _direction != Directions::DIR_RIGHT)
		return false;
	if (_type == LineType::TYPE_COLUMN && _direction != Directions::DIR_UP && _direction != Directions::DIR_DOWN)
		return false;

	bool orientation; //true = left/right; false = down/up

	int16_t fistX = 0;
	int16_t fistY = 0;
	int16_t lastX = 0;
	int16_t lastY = 0;
	
	int16_t start = 0;
	int16_t end = 0;
	int16_t ratio = 0;

	orientation = _type == LineType::TYPE_ROW;

	switch (_direction)
	{
	case Directions::DIR_LEFT:
		start = 0;
		end = getColCount() - 1;
		ratio = +1;
		orientation = true;
		break;
	case Directions::DIR_RIGHT:
		start = getColCount() - 1;
		end = 0;
		ratio = -1;
		orientation = true;
		break;
	case Directions::DIR_UP:
		start = 0;
		end = getRowCount() - 1;
		ratio = +1;
		orientation = false;
		break;
	case Directions::DIR_DOWN:
		start = getRowCount() - 1;
		end = 0;
		ratio = -1;
		orientation = false;
		break;
	}

	auto quickCheck = [&orientation](uint16_t a, uint16_t b) {return orientation ? a : b; };
	
	for (int16_t i = start; i != end; i += ratio) {
		int16_t currX = quickCheck(_line, i);
		int16_t currY = quickCheck(i, _line);

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

		uint16_t nextX = quickCheck(_line, i + ratio);
		uint16_t nextY = quickCheck(i + ratio, _line);

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

	for (int i = start; i != end; i += ratio)
	{
		uint16_t currX = quickCheck(_line, i);
		uint16_t currY = quickCheck(i, _line);

		uint16_t nextX = quickCheck(_line, i + ratio);
		uint16_t nextY = quickCheck(i + ratio, _line);

		m_matrix[currX][currY] = std::move(m_matrix[nextX][nextY]);
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

void Board::PlayCard(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD)
{
	if (m_matrix[_xS][_yS].back().GetColor() == Colours::RED) {
		m_rowChecker[_xS].first--;
		m_colChecker[_yS].first--;
	}
	else {
		m_rowChecker[_xS].second--;
		m_colChecker[_yS].second--;
	}
	if (m_matrix[_xD][_yD].back().GetColor() == Colours::RED) {
		m_rowChecker[_xD].first--;
		m_colChecker[_yD].first--;
	}
	else {
		m_rowChecker[_xD].second--;
		m_colChecker[_yD].second--;
	}

	m_matrix[_xD][_yD].push_back(std::move(m_matrix[_xS][_yS]).back());
	m_matrix[_xS][_yS].pop_back();

	if (m_matrix[_xS][_yS].back().GetColor() == Colours::RED) {
		m_rowChecker[_xS].first++;
		m_colChecker[_yS].first++;
	}
	else {
		m_rowChecker[_xS].second++;
		m_colChecker[_yS].second++;
	}
	if (m_matrix[_xD][_yD].back().GetColor() == Colours::RED) {
		m_rowChecker[_xD].first++;
		m_colChecker[_yD].first++;
	}
	else {
		m_rowChecker[_xD].second++;
		m_colChecker[_yD].second++;
	}
}

void Board::MoveStack(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD)
{
	if (m_matrix[_xS][_yS].empty() && m_matrix[_xD][_yD].empty())
		return;
	if (!m_matrix[_xS][_yS].empty()) {
		if (m_matrix[_xS][_yS].back().GetColor() == Colours::RED) { //can simplify this..
			m_rowChecker[_xS].first--;
			m_rowChecker[_xD].first++;
			m_colChecker[_yS].first--;
			m_colChecker[_yS].first++;
		}
		else {
			m_rowChecker[_xS].second--;
			m_rowChecker[_xD].second++;
			m_colChecker[_yS].second--;
			m_colChecker[_yS].second++;
		}
	}
	if (!m_matrix[_xD][_yD].empty()) {
		if (m_matrix[_xD][_yD].back().GetColor() == Colours::RED) {
			m_rowChecker[_xS].first++;
			m_rowChecker[_xD].first--;
			m_colChecker[_yS].first++;
			m_colChecker[_yS].first--;
		}
		else {
			m_rowChecker[_xS].second++;
			m_rowChecker[_xD].second--;
			m_colChecker[_yS].second++;
			m_colChecker[_yS].second--;
		}
	}

	m_matrix[_xD][_yD] = std::move(m_matrix[_xS][_yS]);
}

void Board::SwitchStacks(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD)
{
	CardStack& source = m_matrix[_xS][_yS];
	CardStack& destination = m_matrix[_xD][_yD];

	if (source.empty() && destination.empty())
		return;
	if (!source.empty()) {
		if (source.back().GetColor() == Colours::RED) { //can simplify this..
			m_rowChecker[_xS].first--;
			m_rowChecker[_xD].first++;
			m_colChecker[_yS].first--;
			m_colChecker[_yS].first++;
		}
		else {
			m_rowChecker[_xS].second--;
			m_rowChecker[_xD].second++;
			m_colChecker[_yS].second--;
			m_colChecker[_yS].second++;
		}
	}
	if (!destination.empty()) {
		if (destination.back().GetColor() == Colours::RED) {
			m_rowChecker[_xS].first++;
			m_rowChecker[_xD].first--;
			m_colChecker[_yS].first++;
			m_colChecker[_yS].first--;
		}
		else {
			m_rowChecker[_xS].second++;
			m_rowChecker[_xD].second--;
			m_colChecker[_yS].second++;
			m_colChecker[_yS].second--;
		}
	}

	CardStack aux = std::move(destination);
	destination = std::move(source);
	source = std::move(aux);
}

void Board::MirrorEdge(BoardChanges _margin)
{
	switch (_margin)
	{
	case BoardChanges::_TOP_BOUND:
		m_matrix.push_back(std::move(m_matrix[0]));
		m_matrix.pop_front();
		break;
	case BoardChanges::_BOT_BOUND:
		m_matrix.push_front(std::move(m_matrix[getRowCount() - 1]));
		m_matrix.pop_back();
		
		break;
	case BoardChanges::_LEFT_BOUND:
		for (int i = 0; i < getRowCount(); i++) {
			m_matrix[i].push_back(std::move(m_matrix[i][0]));
			m_matrix[i].pop_front();
			
		}
		
		m_colChecker.emplace_back(m_colChecker.back().first, m_colChecker.back().second);
		m_colChecker.pop_front();
		break;
	case BoardChanges::_RIGHT_BOUND:
		for (int i = 0; i < getRowCount(); i++) {
			m_matrix[i].push_front(std::move(m_matrix[i][getColCount() - 1]));
			m_matrix[i].pop_back();
		}

		m_colChecker.emplace_front(0, 0);
		m_colChecker.pop_back();
		break;
	default:
		break;
	}
}

bool Board::CheckTopIsEter(int16_t _x, int16_t _y)
{
	if (m_matrix[_x][_y].empty())
		return false;
	return m_matrix[_x][_y].back().GetIsEterCard();
}

void Board::RemoveIllusionProperty(int16_t _x, int16_t _y)
{
	m_matrix[_x][_y].back().SetIsIllusionCard(false);
}

//sper ca merge
const MinionCard& Board::ViewTop(int16_t _x, int16_t _y)
{
	//just in case if
	if (m_matrix[_x][_y].empty())
		return MinionCard::CreateHoleCard();
	return m_matrix[_x][_y].back();
}

AdjacentType Board::CheckAdjacent(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD)
{
	if (_xS == _xD && _yS == _yD)
		return AdjacentType::SAME_STACK;
	if (std::abs(_xS - _yD) == 1 && std::abs(_xD - _yS) == 1)
		return AdjacentType::CORNERING;
	if (_xS == _xD && std::abs(_yD - _yD) == 1 || _yS == _yD && std::abs(_xD - _xD) == 1)
		return AdjacentType::NEIGHBOURING;
	return AdjacentType::NOT_ADJACENT;
}

bool Board::isEmptySpace(int16_t _x, int16_t _y)
{
	if ((_x<0 || _y<0 || _x>=getRowCount() || _y >=getColCount()))
		return true;
	if (m_matrix[_x][_y].empty())
		return true;
	return false;
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

Colours Board::checkWin()
{
	for (const auto& diff : m_colChecker)
	{
		if (diff.first == m_max_size)
			return Colours::RED;
		if (diff.second == m_max_size)
			return Colours::BLUE;
	}
	for (const auto& diff : m_rowChecker)
	{
		if (diff.first == m_max_size)
			return Colours::RED;
		if (diff.second == m_max_size)
			return Colours::BLUE;
	}
	Colours diagWin = checkDiagWin();
	if (m_max_size == m_rowChecker.size() && m_max_size == m_colChecker.size() && diagWin != Colours::INVALID_COL)
		return diagWin;
	if (m_max_size == m_rowChecker.size() && m_max_size == m_colChecker.size())
	{
		return checkWinFullBoard();
	}
	return Colours::INVALID_COL;
}

Colours Board::checkWinFullBoard()
{
	int sumRed = 0, sumBlue = 0;
	for (int i = 0; i < getRowCount(); ++i) 
	{
		for (int j = 0; j < getColCount();++j)
		{
			if (!m_matrix[i][j].empty())
			{
				if(m_matrix[i][j].back().GetCardType()==CardType::MinionCard)
				{
					if (m_matrix[i][j].back().GetColor() == Colours::RED)
						sumRed += m_matrix[i][j].back().GetValue();
					else if(m_matrix[i][j].back().GetColor() == Colours::BLUE)
						sumBlue+= m_matrix[i][j].back().GetValue();
				}
			}
			else
			{
				return Colours::INVALID_COL;
			}
		}
	}
	if (sumBlue > sumRed)
		return Colours::BLUE;
	return Colours::RED;
}

Colours Board::checkDiagWin()
{
	if (m_firstDiag.second == m_max_size || m_seconDiag.second == m_max_size)
		return Colours::BLUE;
	if (m_firstDiag.first == m_max_size || m_seconDiag.first == m_max_size)
		return Colours::RED;
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

std::vector<MarginType> Board::checkForUpdates()
{
	std::vector<MarginType> marginsToRemove;
	while (!m_colChecker.empty() && m_colChecker.front().first == 0 && m_colChecker.front().second == 0) {
		removeLeftMargin();
		marginsToRemove.push_back(MarginType::MARGIN_LEFT);
	}

	while (!m_colChecker.empty() && m_colChecker.back().first == 0 && m_colChecker.back().second == 0) {
		removeRightMargin();
		marginsToRemove.push_back(MarginType::MARGIN_RIGHT);
	}

	while (!m_rowChecker.empty() && m_rowChecker.front().first == 0 && m_rowChecker.front().second == 0) {
		removeTopMargin();
		marginsToRemove.push_back(MarginType::MARGIN_TOP);
	}

	while (!m_rowChecker.empty() && m_rowChecker.back().first == 0 && m_rowChecker.back().second == 0) {
		removeBottomMargin();
		marginsToRemove.push_back(MarginType::MARGIN_BOT);
	}

	if (m_colChecker.size() + m_rowChecker.size() == 0) {
		m_colChecker.emplace_back(0, 0);
		m_rowChecker.emplace_back(0, 0);
		m_matrix.push_back(Line());
		m_matrix[0].push_back(CardStack());
	}

	return marginsToRemove;
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

//rewrtie it
void Board::printBoard(bool _debug)
{
	qDebug() << "R\\B ";
	for (int i = 0; i < getColCount(); i++)
		qDebug() << int(m_colChecker[i].first) << "|" << m_colChecker[i].second << " ";

	for (int i = 0; i < getRowCount(); i++) {
		qDebug() << "\n" << m_rowChecker[i].first << "|" << m_rowChecker[i].second << " ";
		for (int j = 0; j < getColCount(); j++)
		{
			if (!m_matrix[i][j].empty())
			{
				if (m_matrix[i][j].back().GetCardType() == CardType::HoleCard)
					qDebug() << "Hol ";
				else if (m_matrix[i][j].back().GetCardType() == CardType::BlizzardCard)
					qDebug() << "Bli ";
				else
					qDebug() <<i<<" "<<j<<":"<< m_matrix[i][j].back() << " ";
			}
			else
				qDebug() << "--- ";
		}
	}

	if (isMatMaxSize()) {
		qDebug() << "\nFirst diagonal: " << m_firstDiag.first << "|" << m_firstDiag.second << " | ";
		qDebug() << "Second diagonal: " << m_seconDiag.first << "|" << m_seconDiag.second << "\n";
	}
	else
		qDebug() << "\nThe matrix is not in a square form, so the diagonal scores will not be shown.\n";
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
		if (m_matrix[x][y].back().GetCardType() == CardType::BlizzardCard)
			return false;
		if (m_matrix[x][y].back().GetCardType() == CardType::HoleCard)
			return false;
		if (card.GetValue() <= m_matrix[x][y].back().GetValue() && !m_matrix[x][y].back().GetIsIllusionCard())
			return false;
	}
	return true;
}

void Board::AddLineToLeft()
{
	for (int i = 0; i < getRowCount(); i++) {
		m_matrix[i].push_front(CardStack());
	}
	m_colChecker.emplace_front(0, 0);
}

void Board::AddLineToRight()
{
	for (int i = 0; i < getRowCount(); i++) {
		m_matrix[i].push_back(CardStack());
	}
	m_colChecker.emplace_back(0, 0);
}

void Board::AddLineOnTop()
{
	m_matrix.push_front(Line(getColCount()));
	m_rowChecker.emplace_front(0, 0);
}

void Board::AddLineOnBottom()
{
	m_matrix.push_back(Line(getColCount()));
	m_rowChecker.emplace_back(0, 0);
}

bool Board::isValidPosition(int16_t _x, int16_t _y)
{
	return _x >= 0 && _x < m_rowChecker.size() && _y >= 0 && _y < m_colChecker.size();
}

void Board::PlaceIllusion(MinionCard&& _toPlace, int16_t _x, int16_t _y)
{
	_toPlace.SetIsIllusionCard(true);
	_toPlace.SetIsEterCard(false);
	_toPlace.SetIsHole(false);
	if (isBoardEmpty()) {
		m_matrix[0][0].emplace_back(_toPlace);
		if (_toPlace.GetColor() == Colours::RED)
		{
			m_rowChecker[0].first = 1;
			m_colChecker[0].first = 1;
		}
		else
		{
			m_rowChecker[0].second = 1;
			m_colChecker[0].second = 1;
		}
		return;
	}

	ExtendBoard(GetChangeFlag(_x, _y));
	if (_x == -1)
		_x = 0;
	if (_y == -1)
		_y = 0;

	if (!m_matrix[_x][_y].empty()) {
		return;
	}

	increaseOnColorRow(_x, _y, _toPlace.GetColor());
	increaseOnColorColumn(_x, _y, _toPlace.GetColor());
	if (!isMatMaxSize())
		m_reachedMaxSize = false;
	else if (_x == _y || _x + _y == m_max_size - 1)
		increaseOnColorDiagonal(_x, _y, _toPlace.GetColor());

	m_matrix[_x][_y].push_back(_toPlace);
}

bool Board::CanCoverIllusion(uint16_t _x, uint16_t _y, uint16_t _val)
{

	if (!m_matrix[_x][_y].empty() && m_matrix[_x][_y].back().GetIsIllusionCard() && _val!=0)
		return true;

	return false;
}

void Board::RevealIllusion(int16_t _x, int16_t _y)
{
	m_matrix[_x][_y].back().SetCardType(CardType::MinionCard);
	m_matrix[_x][_y].back().SetIsIllusionCard(false);
}

bool Board::isIllusionOnPos(int16_t _x, int16_t _y)
{
	if (!m_matrix[_x][_y].empty())
		return m_matrix[_x][_y].back().GetIsIllusionCard();
	return false;
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

std::vector<MarginType> Board::applyExplosionOnBoard(const ExplosionCard& explCard, Player& pl1, Player& pl2,bool isForTest)
{
	qDebug() << "sizes"<<m_rowChecker.size() << " " << m_colChecker.size() << '\n';
	explMap currExlpMap = explCard.GetExplosionMap();
	for (const auto& elem : currExlpMap)
	{
		auto [positionX, positionY] = elem.first;
		ReturnRemoveOrHoleCard effect = elem.second;

		if (effect == ReturnRemoveOrHoleCard::HoleCard)
			if (positionX>=0 && positionX<m_rowChecker.size() && positionY>=0 && positionY<m_colChecker.size() )
				//(!m_matrix[positionX][positionY].back().GetIsEterCard())
			{
				if (!isForTest)
				{
					removeStack(positionX, positionY);
				}
				MinionCard holeCard(100, Colours::INVALID_COL, false);
				holeCard.SetCardType(CardType::HoleCard);

				m_matrix[positionX][positionY].push_back(holeCard);
				m_matrix[positionX][positionY].back().SetCardType(CardType::HoleCard);
			}
	}
	for (const auto& elem : currExlpMap)
	{
		auto [positionX, positionY] = elem.first;
		ReturnRemoveOrHoleCard effect = elem.second;
		switch (effect)
		{
		case ReturnRemoveOrHoleCard::RemoveCard:
			if (!m_matrix[positionX][positionY].empty() && !m_matrix[positionX][positionY].back().GetIsEterCard())
			{
				MinionCard lastCard = m_matrix[positionX][positionY].back();
				lastCard.SetIsIllusionCard(false);
				if (!isForTest)
				{
					removePos(positionX, positionY);
					if (lastCard.GetColor() == pl1.GetPlayerColor())
						pl1.addToRemovedCards(lastCard);
					else
						pl2.addToRemovedCards(lastCard);
				}
			}
			break;
		case ReturnRemoveOrHoleCard::ReturnCard:
			if (!m_matrix[positionX][positionY].empty() && !m_matrix[positionX][positionY].back().GetIsEterCard())
			{
				MinionCard lastCard = m_matrix[positionX][positionY].back();
				lastCard.SetIsIllusionCard(false);
				if(!isForTest)
				{
					removePos(positionX, positionY);
					if (lastCard.GetColor() == pl1.GetPlayerColor())
						pl1.returnMinionCardToHand(lastCard);
					else
						pl2.returnMinionCardToHand(lastCard);
				}
			}
			break;
		case ReturnRemoveOrHoleCard::Default:
			break;
		default:
			break;
		}
	}
	std::vector<MarginType> margins = checkForUpdates();
	printBoard(true);
	return margins;
}

bool Board::tryApplyExplosionOnBoard(const ExplosionCard& explCard,Player& pl1,Player& pl2)
{
	ResizeableMatrix boardToTest = m_matrix;
	applyExplosionOnBoard(explCard, pl1, pl2,true);
	std::vector<std::pair<int, int>> adj = {
		{-1,-1},{-1,0},{-1,1},{0,1},
		{1,1},{1,0},{1,-1},{0,-1}
	};
	printBoard(true);
	for (int i = 0; i < m_rowChecker.size(); ++i)
	{
		for (int j = 0; j < m_colChecker.size(); ++j)
		{
			if (!m_matrix[i][j].empty())
			{
				bool isAdj = false;
				for (auto position : adj)
				{
					auto [row, col] = position;
					if (row + i >= 0 && row + i < m_rowChecker.size()&& col + j >= 0 && col + j < m_colChecker.size() && 
						!m_matrix[row + i][col + j].empty())
					{
						isAdj = true;
						break;
					}
				}
				if (isAdj == false)
				{
					m_matrix = boardToTest;
					return false;
				}
			}
		}
	}
	m_matrix = boardToTest;
	return true;
}

bool Board::canPlayExplosion()
{
	int counter = 0;
	for (int i = 0; i < m_rowChecker.size(); ++i)
	{
		if (m_rowChecker[i].first+m_rowChecker[i].second == m_max_size)
			counter++;
	}

	for (int i = 0; i < m_colChecker.size(); ++i)
	{
		if (m_colChecker[i].first+m_colChecker[i].second == m_max_size)
			counter++;
	}

	if (m_reachedMaxSize)
	{
		if (m_firstDiag.first + m_firstDiag.second == m_max_size)
			counter++;
		if (m_seconDiag.first + m_seconDiag.second == m_max_size)
			counter++;
	}
	
	if (counter >= 2)
		return true;
	return false;
}

MarginType GetMargin(char _type)
{
	switch (_type)
	{
	case 'U':
		return MarginType::MARGIN_TOP;
	case 'B':
		return MarginType::MARGIN_BOT;
	case 'L':
		return MarginType::MARGIN_LEFT;
	case 'R':
		return MarginType::MARGIN_RIGHT;
	default:
		return MarginType::INVALID_MARGIN;
	}
}

json Board::SerialiseMatrix()
{
	json serialisedMatrix;

	serialisedMatrix["matrix_size"] = m_max_size;
	serialisedMatrix["nr_rows"] = getRowCount();
	serialisedMatrix["nr_cols"] = getColCount();
	//serialisedMatrix["explosion_countdown"] = m_lineCnt; //?

	for (int i = 0; i < getRowCount(); i++)
		for (int j = 0; j < getColCount(); j++)
		{
			json serialisedStack = json::array();
			for (int k = 0; k < m_matrix[i][j].size(); k++)
			{
				serialisedStack.push_back(m_matrix[i][j][k].SerialiseCard());
			}
			serialisedMatrix[FormatPair(i, j)] = serialisedStack;
		}

	return serialisedMatrix;
}

std::string Board::FormatPair(int integer1, int integer2)
{
	return std::to_string(integer1) + "-" + std::to_string(integer2);
}

void Board::DeserializeMatrix(const json& jsonMatrix) {
	// Deserialize matrix size and dimensions
	m_max_size = jsonMatrix.at("matrix_size").get<int>();
	int rows = jsonMatrix.at("nr_rows").get<int>();
	int cols = jsonMatrix.at("nr_cols").get<int>();
	qDebug() << rows << " " << cols;
	m_matrix.resize(rows);
	for (auto& rowDeque : m_matrix) {
		rowDeque.resize(cols);
	}

	for (const auto& [key, value] : jsonMatrix.items()) {
		// Skip metadata keys
		if (key != "matrix_size" && key != "nr_rows" && key != "nr_cols") {
			// Parse the key to get the row and column indices
			auto indices = ParsePair(key); // ParsePair converts "row-col" back to (row, col)
			int row = indices.first, col = indices.second;

			// Clear the stack at (row, col)
			m_matrix[row][col].clear(); ///---- here

			// Deserialize each card in the stack
			for (const auto& cardJson : value) {
				MinionCard card;
				card.DeserializeCard(cardJson); // Use the DeserializeCard method for each card
				m_matrix[row][col].push_back(card); // Add the deserialized card to the stack
			}
		}
	}
}

std::pair<int, int> Board::ParsePair(const std::string& str) {
	size_t dashPos = str.find('-');
	int row = std::stoi(str.substr(0, dashPos));
	int col = std::stoi(str.substr(dashPos + 1));
	return { row, col };
}

void Board::updateRowCheckerDeserialize()
{
	m_rowChecker.resize(m_matrix.size(),{0,0});
	for (int i = 0; i < m_matrix.size(); ++i)
	{
		for(int j=0;j<m_matrix[i].size(); ++j)
			if (!m_matrix[i][j].empty())
			{
				if (m_matrix[i][j].back().GetColor() == Colours::RED)
					m_rowChecker[i].first += 1;
				else if (m_matrix[i][j].back().GetColor() == Colours::BLUE)
					m_rowChecker[i].second += 1;
			}
	}
}

void Board::updateColCheckerDeserialize()
{
	m_colChecker.resize(m_matrix[0].size(), { 0,0 });
	for (int i = 0; i < m_matrix.size(); ++i)
	{
		for (int j = 0; j < m_matrix[i].size(); ++j)
			if (!m_matrix[j][i].empty())
			{
				if (m_matrix[j][i].back().GetColor() == Colours::RED)
					m_colChecker[j].first += 1;
				else if (m_matrix[j][i].back().GetColor() == Colours::BLUE)
					m_colChecker[j].second += 1;
			}
	}
}

void Board::updateDiagsDeserialize()
{
	if (!(getColCount() == m_max_size && getRowCount() == m_max_size))
		return;
	for (int i = 0; i < m_max_size; i++)
	{
		if (!m_matrix[i][i].empty())
		{
			if (m_matrix[i][i].back().GetColor() == Colours::RED)
				m_firstDiag.first += 1;
			else
				m_firstDiag.second += 1;
		}
		if (!m_matrix[i][m_max_size - i - 1].empty())
		{
			if (m_matrix[i][m_max_size - i - 1].back().GetColor() == Colours::RED)
				m_seconDiag.first += 1;
			else
				m_seconDiag.second += 1;
		}
	}
}


