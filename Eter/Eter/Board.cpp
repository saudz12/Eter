#include "Board.h"

int Board::getPos(int x, int y)
{
    if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
        return -1; //add error message in qt console/logger
    return *m_board[x][y].rbegin();
}

int Board::setPos(int x, int y, int val)
{
    if (getColCount() == m_max_size && x < 0 && x >= m_max_size || getRowCount() == m_max_size && y >= m_max_size && y < 0)
        return -1; //add error message in qt console/logger
    if (val > *m_board[x][y].rbegin())
        m_board[x][y].push_back(val);
    else
        return 1; //cannot move on it
    return 0;//no problems
}

int Board::removePos(int x, int y, int pos) {
    if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
        return -1; //err
    if (pos > m_board[x][y].size() || m_board[x][y].size() == 0)
        return 1;
    m_board[x][y].erase(m_board[x][y].begin() + pos);
    return 0;
}

char Board::entityWon(int x, int y) //updates row and column col counter after move and check then OR check independently after move - talk and decide
{
    if (x < 0 || y < 0 || x >= m_max_size || y >= m_max_size)
        return -1; //add error message in qt console/logger
    if (++m_colChecker[x].first > m_max_size)
        return 'R';
    if (++m_rowChecker[y].first > m_max_size)
        return 'R';
   
    if (++m_colChecker[x].second > m_max_size)
        return 'B';
    if (++m_rowChecker[y].second > m_max_size)
        return 'B';
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
