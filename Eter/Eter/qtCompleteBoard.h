#pragma once
#include "Board.h"
#include "qwidget.h"
#include <queue>

class qtCompleteBoard
{
private:
	//matrice de qlabel
	Board m_board;

public:
	qtCompleteBoard(uint16_t boardSize);
	void placeCard();
};

