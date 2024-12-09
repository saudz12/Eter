#pragma once
#include "Board.h"
#include "HoleCard.h"

//remove opponent's card that covers one of player's cards
void funcFireMage1(Board& _board, Player& _user, int16_t _x, int16_t _y, int16_t _pos);

void funcFireMage2(Board& _board, Player& _player, int16_t _line, char _type);

//cover opponent card with lower value card of yours
void funcEarthMage1(Board& _board, Player& _user, Player& _affected, int16_t _x, int16_t _y, int16_t _val);

//hole card,position to cover
void funcEarthMage2(Board& _board, int16_t _x, int16_t _y);

//original position, destination position(player's card)
void funcAirMage1(Board& _board, Colours _colour, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);

//position for additional Eter card
void funcAirMage2(Board&, uint16_t, uint16_t);

//original position, destination position(opponent's card)
void funcWaterMage1(Board&, Player&);

//move row/column to other side of the board
void funcWaterMage2(Board& board, Colours color, Player& pl);

bool searchInColumnStacks(ResizeableMatrix& matrix, Player& pl, uint16_t column);

bool searchInRowStacks(ResizeableMatrix& matrix, Player& pl, uint16_t row);
