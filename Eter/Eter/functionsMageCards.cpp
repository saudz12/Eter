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
	//_board.PlaceCard(_user.MoveCard(_val), _x, _y, BoardChanges::_NO_CHANGES); 
	//_user.UpdateCard(_val, CardAction::REMOVE); //<-- uncomment both and remove below when the code is moved to move semantics

	ResizeableMatrix& matrix = _board.getMatrix();

	_affected.getCovered().insert({ _x, _y, matrix[_x][_y].size() - 1 }); //<-- covered set? - rework it

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
	_board.PlaceCard(MinionCard::CreateEterCard(_colour), _x, _y);
}

// original position, destination position (opponent's card)
void funcWaterMage1(Board& _board, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD) //INPUT CHECKING DIFERIT PRIN == CU COLOUR ASTA CRAPA DACA E DIFERIT CELALALT DACA E LA FEl
{
	_board.SwitchStacks(_xS, _yS, _xD, _yD);
}

// move row/column to other side of the board
void funcWaterMage2(Board& _board, BoardChanges _margin) //change the function further when reimplementing covered cards? or the iterators will keep in mind?
{
	_board.MirrorEdge(_margin);
}
