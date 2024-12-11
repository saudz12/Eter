#include "functionsMageCards.h"
#include "MoveLaterToGameClass.h"

void funcFireMage1(Board& _board, Player& _user, int16_t _x, int16_t _y, int16_t _pos) //does not update players covered and removed :/
{
	_board.RemoveCard(_x, _y, _pos);
}

void funcFireMage2(Board& _board, Player& _player, int16_t _line, char _type) //does not update players covered and removed :/
{
	_board.RemoveLine(_line, GetLineType(_type));
	//do sum like returnStackToHand or returnLineToHand care se foloseste de ala sa fie mai modular codu yhu feel me????
}

void funcEarthMage1(Board& _board,Player& _user, Player& _affected, int16_t _x , int16_t _y, int16_t _val) //don;t know if it works.
{
	//_board.PlaceCard(_user, _x, _y, _val, BoardChanges::_NO_CHANGES); //<-- uncomment and remove below when the code is moved to move semantics

	ResizeableMatrix& matrix = _board.getMatrix();

	_affected.getCovered().insert({ _x, _y, matrix[_x][_y].size() - 1 }); //<-- covered set? - depricated..

	matrix[_x][_y].emplace_back(_val, _user.GetPlayerColor(), false, false);

	//upon moving to move semantics remove until here and transform the below code in a fucntion in board if id does not exsist (function that are not in to be removed).
	
	LineChecker& colChecker = _board.getColChecker(), & rowChecker = _board.getRowChecker();

	_user.UpdateCard(matrix[_x][_y].back(), -1);

	if (_user.GetPlayerColor() == Colours::RED) {
		rowChecker[_x].first++;
		rowChecker[_x].second--;
		colChecker[_y].first++;
		colChecker[_x].second--;
	}
	else {
		rowChecker[_x].first--;
		rowChecker[_x].second++;
		colChecker[_y].first--;
		colChecker[_x].second++;
	}
}

void funcEarthMage2(Board& _board, int16_t _x, int16_t _y) //:)
{
	_board.CreateHole(_x, _y);
}

void funcAirMage1(Board& _board, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD) //does not update players covered cards :/
{
	_board.SwitchStacks(_xS, _yS, _xD, _yD);
}

// position for additional Eter card
void funcAirMage2(Board& _board, Colours _colour, uint16_t _x, uint16_t _y)
{
	_board.PlaceCard(MinionCard::CreateEterCard(_colour), _x, _y, _board.GetChangeFlag(_x, _y));
}

// original position, destination position (opponent's card)
void funcWaterMage1(Board& _board, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD) //INPUT CHECKING DIFERIT PRIN == CU COLOUR ASTA CRAPA DACA E DIFERIT CELALALT DACA E LA FEl
{
	_board.SwitchStacks(_xS, _yS, _xD, _yD);
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
		for (int16_t i = 0; i < board.getRowCount(); ++i)
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
