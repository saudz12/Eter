#include "functionsMageCards.h"

// remove opponent's card that covers one of player's cards
void funcFireMage1(Board& board,Player& pl)
{
	uint16_t x, y;
	std::cout << "select the position where you want to remove the opponent's card:\n";
	std::cin >> x >> y;

	resizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].empty())
		return;

	covered& coveredSet = pl.getCovered();
	if (!coveredSet.empty())
	{
		pl.printCoveredCards(matrix);
		std::cout << "choose one of the cards to remove it\n";
		int chosenPositionToRemove;
		std::cin >> chosenPositionToRemove;
		matrix[x][y].erase(matrix[x][y].begin() + chosenPositionToRemove);
	}
}

void funcFireMage2(Board& board,Player& pl)
{
	resizeableMatrix& matrix = board.getMatrix();

	std::cout << "what would to remove : 0.column , 1.row \n";
	uint16_t option;
	std::cin >> option;
	
	bool ok = true;

	if (option == 0)
	{
		std::cout << "which column:\n";
		uint16_t column;
		std::cin >> column;
		lineChecker& colChecker = board.getColChecker();
		if (pl.GetPlayerColor() == 'R')
		{
			if (colChecker[column].first == 0)//no visible cards for red
			{
				ok = false;
				return;
			}
		}
		else if (colChecker[column].second == 0)//no visible cards for blue
		{
			ok = false;
			return;
		}
		if (ok == false || searchInColumnStacks(matrix,pl,column) == false)
		{
			std::cout << "no cards belong to you in this column";
			return;
		}
		if (colChecker[column].first + colChecker[column].second < 3)
		{
			std::cout << "less than 3 cards on this column";
			return;
		}
		board.removeColumn(column);
	}
	else if (option == 1)
	{
		std::cout << "which row:\n";
		uint16_t row;
		std::cin >> row;
		lineChecker& lineChecker = board.getRowChecker();
		if (pl.GetPlayerColor() == 'R')
		{
			if (lineChecker[row].first == 0)//no visible cards for red
			{
				ok = false;
				return;
			}
		}
		else if (lineChecker[row].second == 0)//no visible cards for blue
		{
			ok = false;
			return;
		}
		if (ok == false || searchInRowStacks(matrix, pl, row) == false)
		{
			std::cout << "no cards belong to you in this row";
			return;
		}
		if (lineChecker[row].first + lineChecker[row].second < 3)
		{
			std::cout << "less than 3 cards on this column";
			return;
		}
		board.removeRow(row);
	}
	board.checkForUpdates();
}

// cover opponent card with lower value card of yours
void funcEarthMage1(Board& board, Card& card, uint16_t x , uint16_t y)
{
}

// hole card, position to cover
void funcEarthMage2(Board& board, HoleCard& hCard, uint16_t x, uint16_t y)
{
}

// original position, destination position (player's card)
void funcAirMage1(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// position for additional Eter card
void funcAirMage2(Board& board, uint16_t x, uint16_t y)
{
}

// original position, destination position (opponent's card)
void funcWaterMage1(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// move row/column to other side of the board
void funcWaterMage2(Board& board, line& line1, line& line2)
{
}

bool searchInColumnStacks(resizeableMatrix& matrix,Player& pl,uint16_t column)
{
	for (int x = 0; x < matrix.size(); ++x)
	{
		for (auto& card : matrix[x][column])
		{
			if (card.GetColor() == pl.GetPlayerColor())
				return true;
		}
	}
	return false;
}

bool searchInRowStacks(resizeableMatrix& matrix, Player& pl, uint16_t row)
{
	for (int y = 0; y < matrix[row].size(); ++y)
	{
		for (auto& card : matrix[row][y])
		{
			if (card.GetColor() == pl.GetPlayerColor())
				return true;
		}
	}
	return false;
}
