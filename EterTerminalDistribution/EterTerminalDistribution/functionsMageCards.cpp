#include "functionsMageCards.h"
#include "MoveLaterToGameClass.h"
// remove opponent's card that covers one of player's cards
void funcFireMage1(Board& board,Player& pl)
{
	uint16_t x, y;
	std::cout << "select the position where you want to remove the opponent's card:\n";
	std::cin >> x >> y;

	resizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].empty())
		return;

	coveredSet& coveredSet = pl.getCovered();
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
			std::cout << "less than 3 cards on this row";
			return;
		}
		board.removeRow(row);
	}
	board.checkForUpdates();
}

// cover opponent card with lower value card of yours
void funcEarthMage1(Board& board,Player& pl, uint16_t x , uint16_t y)
{
	hand& currHand = pl.GetHandCards();
	char curr_col = pl.GetPlayerColor();
	for (auto& i : currHand) {
		std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
	}
	std::cout << "Choose a card from the hand and where to place it in the board\n";
	uint16_t val;
	std::cin >> val >> x >> y;
	MinionCard toSearch(val, curr_col);
	//check if card in hand. reduce and remove only if can place.
	if (currHand.find(toSearch) == currHand.end()) {
		std::cout << "\nYou don't own any cards of that type!\n";
		system("pause");
	}
	if (board.setPos(x, y, 5, curr_col) == 1) {
		std::cout << "\nYou can't place that card there!\n";
		system("pause");
	}
	resizeableMatrix& matrix = board.getMatrix();
	matrix[x][y].back().SetValue(val);
	pl.UpdateCard(val, -1);
}

// hole card, position to cover
void funcEarthMage2(Board& board)
{
	MinionCard holeCard(0,'N');
	holeCard.SetIsHole(true);
}

// original position, destination position (player's card)
void funcAirMage1(Board& board,Player& pl)
{
	char currColor = pl.GetPlayerColor();
	uint16_t x1, y1, x2, y2;
	std::cout << "from where\n";
	std::cin >> x1 >> y1;

	std::cout << "to where\n";
	std::cin >> x2 >> y2;

	if (x1 < 0 || x2 < 0 || y2 >= board.getColCount() || y1 >= board.getColCount())
	{
		std::cout << "invalid positions\n";
		return;
	}

	Board cloneBoard;
	Board::cloneMatrix(board, cloneBoard);

	resizeableMatrix& matrix = board.getMatrix();

	if (matrix[x1][y1].empty())
	{
		std::cout << "no cards here\n";
		return;
	}
	if (matrix[x1][y1].back().GetColor() != pl.GetPlayerColor())
	{
		std::cout << "on this position there are no cards of your color\n";
		return;
	}
	std::cout << "Select what you would want to do with the card\n0. move the card\n1. move the stack of cards\n";
	uint16_t option;
	std::cin >> option;
	lineChecker& colChecker=board.getColChecker(), &rowChecker=board.getRowChecker();

	if (!matrix[x1][y1].empty())
	{
		if (currColor == 'R')
		{
			if (x1 != x2)
			{
				rowChecker[x1].first--;
				rowChecker[x2].first++;
			}
			
			if (y1 != y2)
			{
				colChecker[y1].first --;
				colChecker[y2].first++;
			}
		}
		else
		{
			if (x1 != x2)
			{
				rowChecker[x2].second ++;
				rowChecker[x1].second --;
			}
			if (y1 != y2)
			{
				colChecker[y1].second --;
				colChecker[y2].second++;
			}
		}
	}

	if (option == 0)
	{
		MinionCard& lastCard = matrix[x1][y1].back();
		matrix[x1][y1].pop_back();
		if (!matrix[x2][y2].empty())
		{
			std::cout << "second position is not empty\n";
			return;
		}
		matrix[x2][y2].emplace_back(lastCard);
		if (isolatedSpaces(board))
		{
			std::cout << "this card cannot be placed because creates isolated spaces\n";
			Board::cloneMatrix(cloneBoard, board);
			return;
		}
	}
	else
	{
		std::deque<MinionCard>& stackCardOnPosition = matrix[x1][y1];
		
		matrix[x1][y1].clear();
		if (!matrix[x2][y2].empty())
		{
			std::cout << "second position is not empty\n";
			return;
		}
		matrix[x2].insert(matrix[x2].begin() + y2, stackCardOnPosition);
		if (isolatedSpaces(board))
		{
			std::cout << "this card cannot be placed because creates isolated spaces\n";
			Board::cloneMatrix(cloneBoard, board);
			return;
		}
	}

	//board.checkForUpdates();
}

// position for additional Eter card
void funcAirMage2(Board& board, uint16_t x, uint16_t y)
{
	//MinionCard eterCard;
	//eterCard.SetIsEterCard(true);
}

// original position, destination position (opponent's card)
void funcWaterMage1(Board& board,Player& pl)
{
	//call this function for pl1 with pl2
	funcAirMage1(board, pl);
}

// move row/column to other side of the board
void funcWaterMage2(Board& board,char color,Player& pl)//opponent 
{
	int option;
	std::cout << " Select what you would want to move\n";
	std::cout << "0. Move top line\n1. Move bottom line\n2. Move left column\n3. Move right column\n";
	std::cin >> option;
	resizeableMatrix& matrix = board.getMatrix();
	lineChecker& rowChecker = board.getRowChecker();
	lineChecker& colChecker = board.getColChecker();
	uint16_t lastLine = board.getRowCount()-1;
	uint16_t lastColumn = board.getColCount()-1;
	if (option==0)
	{
		bool ok = true;
		if (color == 'R')
		{
			if (rowChecker[0].first == 0)//no visible cards for red
			{
				ok = false;
				return;
			}
		}
		else if (rowChecker[0].second == 0)//no visible cards for blue
		{
			ok = false;
			return;
		}
		if (ok == false || searchInRowStacks(matrix, pl, 0) == false)
		{
			std::cout << "no cards belong to you in this row";
			return;
		}
		if (rowChecker[0].first + rowChecker[0].second < 3)
		{
			std::cout << "less than 3 cards on this row";
			return;
		}
	}
	else if (option == 1)
	{
		bool ok = true;
		if (color == 'R')
		{
			if (rowChecker[lastLine].first == 0)//no visible cards for red
			{
				ok = false;
				return;
			}
		}
		else if (rowChecker[lastLine].second == 0)//no visible cards for blue
		{
			ok = false;
			return;
		}
		if (ok == false || searchInRowStacks(matrix, pl, lastLine) == false)
		{
			std::cout << "no cards belong to you in this row";
			return;
		}
		if (rowChecker[lastLine].first + rowChecker[lastLine].second < 3)
		{
			std::cout << "less than 3 cards on this column";
			return;
		}
	}
	else if (option == 3)
	{
		bool ok = true;
		if (color == 'R')
		{
			if (colChecker[lastColumn].first == 0)//no visible cards for red
			{
				ok = false;
				return;
			}
		}
		else if (colChecker[lastColumn].second == 0)//no visible cards for blue
		{
			ok = false;
			return;
		}
		if (ok == false || searchInColumnStacks(matrix, pl, lastColumn) == false)
		{
			std::cout << "no cards belong to you in this column";
			return;
		}
		if (colChecker[lastColumn].first + colChecker[lastColumn].second < 3)
		{
			std::cout << "less than 3 cards on this column";
			return;
		}
	}
	else if (option == 2)
	{
		bool ok = true;
		if (color == 'R')
		{
			if (colChecker[0].first == 0)//no visible cards for red
			{
				ok = false;
				return;
			}
		}
		else if (colChecker[0].second == 0)//no visible cards for blue
		{
			ok = false;
			return;
		}
		if (ok == false || searchInColumnStacks(matrix, pl, 0) == false)
		{
			std::cout << "no cards belong to you in this column";
			return;
		}
		if (colChecker[0].first + colChecker[0].second < 3)
		{
			std::cout << "less than 3 cards on this column";
			return;
		}
	}
	if (option == 0 || option == 1)
	{
		std::swap(matrix[0], matrix[board.getRowCount() - 1]);
	}
	else if(option==2 || option==3)
	{
		for (size_t i = 0; i < board.getRowCount(); ++i)
		{
			std::swap(matrix[i][0], matrix[i][board.getColCount() - 1]);
		}
	}
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
