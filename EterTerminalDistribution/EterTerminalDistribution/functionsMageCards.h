#pragma once
#include "Board.h"
#include "HoleCard.h"

	//remove opponent's card that covers one of player's cards
	void funcFireMage1(Board&, uint16_t, uint16_t);

	void funcFireMage2(line&);

	//cover opponent card with lower value card of yours
	void funcEarthMage1(Board&,Card&,uint16_t,uint16_t);

	//hole card,position to cover
	void funcEarthMage2(Board&, HoleCard&, uint16_t, uint16_t);

	//original position, destination position(player's card)
	void funcAirMage1(Board&,uint16_t,uint16_t,uint16_t,uint16_t);

	//position for additional Eter card
	void funcAirMage2(Board&, uint16_t, uint16_t);

	//original position, destination position(opponent's card)
	void funcWaterMage1(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

	//move row/column to other side of the board
	void funcWaterMage2(Board&,line&,line&);
