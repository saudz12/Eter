#include "functionsMageCards.h"
#include "MoveLaterToGameClass.h"

// remove opponent's card that covers one of player's cards
void funcFireMage1(Board& board, Player& pl)
{
	uint16_t x, y;
	std::cout << "select the position where you want to remove the opponent's card:\n";
	std::cin >> x >> y;

	ResizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].empty())
		return;

	CoveredSet& coveredSet = pl.getCovered();
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
	ResizeableMatrix& matrix = board.getMatrix();

	std::cout << "what to remove : 0.column , 1.row \n";
	uint16_t option;
	std::cin >> option;
	
	bool ok = true;

	if (option == 0)
	{
		std::cout << "which column:\n";
		uint16_t column;
		std::cin >> column;
		LineChecker& colChecker = board.getColChecker();
		if (pl.GetPlayerColor() == Colours::RED)
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
		LineChecker& lineChecker = board.getRowChecker();
		if (pl.GetPlayerColor() == Colours::RED)
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

 //cover opponent card with lower value card of yours
void funcEarthMage1(Board& board,Player& pl, uint16_t x , uint16_t y)
{
	Hand& currHand = pl.GetHandCards();
	Colours curr_col = pl.GetPlayerColor();
	for (auto& i : currHand) {
		std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
	}
	std::cout << "Choose a card from the hand and where to place it in the board\n";
	uint16_t val;
	std::cin >> val >> x >> y;
	MinionCard toSearch(val, curr_col, false);
	//check if card in hand. reduce and remove only if can place.
	if (currHand.find(toSearch) == currHand.end()) {
		std::cout << "\nYou don't own any cards of that type!\n";
		system("pause");
	}
	if (board.setPos(x, y, toSearch, pl) == 1) {
		std::cout << "\nYou can't place that card there!\n";
		system("pause");
	}
	ResizeableMatrix& matrix = board.getMatrix();
	matrix[x][y].back().SetValue(val);
	pl.UpdateCard(toSearch, -1);
}

// hole card, position to cover
void funcEarthMage2(Board& board)
{
	MinionCard holeCard(0,'N', false);
	holeCard.SetIsHole(true);
}

// original position, destination position (player's card)
void funcAirMage1(Board& board, Player& pl)
{
	Colours currColor = pl.GetPlayerColor();
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

	Board cloneBoard(3);
	Board::cloneMatrix(board, cloneBoard);

	ResizeableMatrix& matrix = board.getMatrix();

	if (matrix[x1][y1].empty())
	{
		std::cout << "no cards here\n";
		return;
	}

	if (matrix[x1][y1].back().GetIsEterCard())
	{
		std::cout << "Can't use Air Mage on eter card\n";
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
	LineChecker& colChecker=board.getColChecker(), &rowChecker=board.getRowChecker();

	if (!matrix[x1][y1].empty())
	{
		if (currColor == Colours::RED)
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
void funcWaterMage2(Board& board, Colours color,Player& pl)//opponent 
{
	int option;
	std::cout << " Select what you would want to move\n";
	std::cout << "0. Move top line\n1. Move bottom line\n2. Move left column\n3. Move right column\n";
	std::cin >> option;
	ResizeableMatrix& matrix = board.getMatrix();
	LineChecker& rowChecker = board.getRowChecker();
	LineChecker& colChecker = board.getColChecker();
	uint16_t lastLine = board.getRowCount() - 1;
	uint16_t lastColumn = board.getColCount() - 1;
	if (option==0)
	{
		bool ok = true;
		if (color == Colours::RED)
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
		if (color == Colours::RED)
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
		if (color == Colours::RED)
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
		if (color == Colours::RED)
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

bool searchInColumnStacks(ResizeableMatrix& matrix,Player& pl,uint16_t column)
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

bool searchInRowStacks(ResizeableMatrix& matrix, Player& pl, uint16_t row)
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
