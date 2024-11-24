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
uint16_t funcFlame(Board&, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard&, Player& );

//player Red,player Blue
uint16_t funcFire(Board&, Player&, Player&, uint16_t);

//maybe also keep all the removed cards in unordered set
uint16_t funcAsh(Board&, Player&, const MinionCard&, uint16_t, uint16_t);

void funcSpark(Board&, Player& p);

void funcSquall(Board&, Player&, uint16_t, uint16_t);

void funcGale(Board& board, Player&, Player&);

//shit a line 1 space in its orientation. Overflowing stacks return the respective cards to the users hand
void funcHurricane(Board&, hand&, hand&);

//move card one position to antoher
void funcGust(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

//exchange illusion card with other card
void funcMirage(Board&, Player&, uint16_t, uint16_t, const MinionCard&);

//remove stack of cards
void funcStorm(Board&, Player&, Player&, uint16_t, uint16_t);

//tide(board, first set of coordonates, second set of coordonates) -- exchange 2 stacks
void funcTide(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

//play again a illusion(cannot have 2 illsuion at the same time)
void funcMist(Board&, Player&, uint16_t, uint16_t, MinionCard&);

//move a card/stack to empty adj space and place new card to the empty space created
void funcWave(Board&, uint16_t, uint16_t, MinionCard);

//move 2 card separated by empty space into the empty space and place them as stacks 
void funcWhirlpool(Board&, uint16_t, uint16_t);

//make the line unplayable for the next round
void funcBlizzard(line&);

//stack the cards of the row/column on thop of each other
void funcWaterfall(Board&, uint16_t);

//increase value of a card by one, marker also place on the card(tournament mode)
void funcSupport(Board&, uint16_t, uint16_t);

//remove all visible 1 value cards
void funcEarthquake(Board&);

//value of a card decreased by 1,marked placed on card
void funcCrumble(Board&, uint16_t, uint16_t);

//defines a border in a position
void funcBorder(Board&, uint16_t, uint16_t);

//move 2 neighboring cards/stacks vertically/horizontally
void funcAvalanche(Board&, uint16_t, uint16_t, uint16_t, uint16_t, char);

//cover a illusion with a card
void funcRock(Board&, uint16_t, uint16_t, MinionCard&);

void funcDefault();

