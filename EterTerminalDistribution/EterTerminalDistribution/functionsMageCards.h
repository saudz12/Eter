#pragma once
#include "Board.h"
#include "HoleCard.h"

void funcFireMage1(Board&, uint16_t, uint16_t);//remove opponent's card that covers one of player's cards
void funcFireMage2(line&);
void funcEarthMage1(Board&,Card&,uint16_t,uint16_t);//cover opponent card with lower value card of yours
void funcEarthMage2(Board&, HoleCard&, uint16_t, uint16_t);//hole card,position to cover
void funcAirMage1(Board&,uint16_t,uint16_t,uint16_t,uint16_t);//original position, destination position(player's card)
void funcAirMage2(Board&, uint16_t, uint16_t);//position for additional Eter card
void funcWaterMage1(Board&, uint16_t, uint16_t, uint16_t, uint16_t);//original position, destination position(opponent's card)
void funcWaterMage2(Board&,line&,line&);//move row/column to other side of the board