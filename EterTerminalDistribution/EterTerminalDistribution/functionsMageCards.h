#pragma once
#include "Board.h"
#include "HoleCard.h"

//remove opponent's card that covers one of player's cards
void funcFireMage1(Board&, Player&);

void funcFireMage2(Board&, Player&);

//cover opponent card with lower value card of yours
void funcEarthMage1(Board&, Player&, uint16_t, uint16_t);

//hole card,position to cover
void funcEarthMage2(Board&);

//original position, destination position(player's card)
void funcAirMage1(Board&, Player& pl);

//position for additional Eter card
void funcAirMage2(Board&, uint16_t, uint16_t);

//original position, destination position(opponent's card)
void funcWaterMage1(Board&, Player&);

//move row/column to other side of the board
void funcWaterMage2(Board& board, Colours color, Player& pl);

bool searchInColumnStacks(ResizeableMatrix& matrix, Player& pl, uint16_t column);

bool searchInRowStacks(ResizeableMatrix& matrix, Player& pl, uint16_t row);
