#pragma once
#include "ExplosionCard.h"
#include "MoveLaterToGameClass.h"

using handCard = std::unordered_map<MinionCard, uint16_t>;
//using position = std::pair<uint16_t, uint16_t>;

//maybe generate new ExplosionCard
uint16_t funcControlledExplosion(Board&, Player&, Player&);

//implement in player last card played
uint16_t funcDestruction(Board&, Player&);

//first 2 uint16_t for revealing Illusion and the next for placing Card
uint16_t funcFlame(Board&, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const MinionCard&, Player&);

//player Red,player Blue
uint16_t funcFire(Board&, Player&, Player&, uint16_t);

//maybe also keep all the removed cards in unordered set
uint16_t funcAsh(Board&, Player&, const MinionCard&, int16_t, int16_t);

uint16_t funcSpark(Board&, Player& p);

uint16_t funcSquall(Board&, Player&, uint16_t, uint16_t);

uint16_t funcGale(Board& board, Player&, Player&);

//shift a line 1 space in its orientation. Overflowing stacks return the respective cards to the users hand
void funcHurricane(Board& _board, Hand& _h1, Hand& _h2, uint16_t _lineCnt, LineType _type, Directions _direction);

//move card one position to antoher
uint16_t funcGust(Board&, Player&, int16_t, int16_t, int16_t, int16_t);

//exchange illusion card with other card
uint16_t funcMirage(Board&, Player&, int16_t, int16_t, const MinionCard&);

//remove stack of cards
uint16_t funcStorm(Board&, Player&, Player&, uint16_t, uint16_t);

//tide(board, first set of coordonates, second set of coordonates) -- exchange 2 stacks
uint16_t funcTide(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

//play again a illusion(cannot have 2 illsuion at the same time)
uint16_t funcMist(Board&, Player&, int16_t, int16_t, MinionCard&);

//move a card/stack to empty adj space and place new card to the empty space created
uint16_t funcWave(Board&, Player&, int16_t, int16_t, MinionCard);

//move 2 card separated by empty space into the empty space and place them as stacks 
uint16_t funcWhirlpool(Board&, uint16_t, uint16_t);

//make the line unplayable for the next round
uint16_t funcBlizzard(Board&, uint16_t, char);

//stack the cards of the row/column on thop of each other
uint16_t funcWaterfall(Board&, uint16_t, uint16_t);

//increase value of a card by one, marker also place on the card(tournament mode)
uint16_t funcSupport(Board&, uint16_t, uint16_t);

//remove all visible 1 value cards
uint16_t funcEarthquake(Board&, Player&, Player&);

//value of a card decreased by 1,marked placed on card
uint16_t funcCrumble(Board&, uint16_t, uint16_t);

//defines a border in a position
uint16_t funcBorder(Board&, int16_t, int16_t);

//move 2 neighboring cards/stacks vertically/horizontally
void funcAvalanche(Board& _board, int16_t _x1, int16_t _y1, int16_t _x2, int16_t _y2, Directions _direction);

//cover a illusion with a card
uint16_t funcRock(Board&, int16_t, int16_t, MinionCard&);

void funcDefault();

