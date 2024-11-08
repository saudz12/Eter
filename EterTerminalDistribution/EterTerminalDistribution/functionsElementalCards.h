#pragma once
#include "ExplosionCard.h"
#include "unordered_map"
#include "MinionCard.h"
#include "Board.h"
#include "Player.h"
using handCard = std::unordered_map<MinionCard, uint16_t>;
using position = std::pair<uint16_t, uint16_t>;

//maybe generate new ExplosionCard
void funcControlledExplosion(Board&,ExplosionCard&);

//implement in player last card played
void funcDestruction(Board&, Player&);

//first 2 uint16_t for revealing Illusion and the next for placing Card
void funcFlame(Board&,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,MinionCard& CardToBePlaced);

//player Red,player Blue
void funcFire(Board&,handCard&,handCard&);

//maybe also keep all the removed cards in unordered set
void funcAsh(Board&,uint16_t,uint16_t);

void funcSpark(Board&,uint16_t,uint16_t,uint16_t,uint16_t);

void funcSquall(Board&,Player&,uint16_t,uint16_t);

void funcGale(Board&,handCard&);

//modify board,handcard if modified
void funcHurricane(Board&,handCard&);

//move card one position to antoher
void funcGust(Board&,uint16_t,uint16_t,uint16_t,uint16_t);

//exchange illusion card with other card
void funcMirage(Board&,handCard&,uint16_t,uint16_t);

//remove stack of cards
void funcStorm(Board&,uint16_t,uint16_t);

//swap cards or stack of cards
void funcTide(Board&,uint16_t,uint16_t,uint16_t,uint16_t);

//play again a illusion(cannot have 2 illsuion at the same time)
void funcMist(Board&, uint16_t, uint16_t);

//move a card/stack to empty adj space and place new card to the empty space created
void funcWave(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

//move 2 card separated by empty space into the empty space and place them as stacks 
void funcWhirlpool(Board&,uint16_t,uint16_t,uint16_t,uint16_t);

//make the line unplayable for the next round
void funcBlizzard(line&);

//stack the cards of the row/column on thop of each other
void funcWaterfall(line&);

//increase value of a card by one, marker also place on the card(tournament mode)
void funcSupport(Board&,uint16_t, uint16_t);

//remove all visible 1 value cards
void funcEarthquake(Board&);

//value of a card decreased by 1,marked placed on card
void funcCrumble(Board&,uint16_t,uint16_t);

//defines a border in a position
void funcBorder(Board&, uint16_t, uint16_t);

//move 2 neighboring cards/stacks vertically/horizontally
void funcAvalanche(Board&, uint16_t, uint16_t, uint16_t, uint16_t,char direction);

//cover a illusion with a card
void funcRock(Board&,uint16_t,uint16_t);

void funcDefault();


