#include "functionsElementalCards.h"

// maybe generate new ExplosionCard
void funcControlledExplosion(Board& board, ExplosionCard& explCard)
{
}

// implement in player last card played
void funcDestruction(Board& board)
{
}

// first 2 uint16_t for revealing Illusion and the next for placing Card
void funcFlame(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// player Red, player Blue
void funcFire(Board& board,handCard& cardsPl1, handCard& cardsPl2)
{
}

// maybe also keep all the removed cards in unordered set
void funcAsh(Board& board, uint16_t x, uint16_t y)
{
}

void funcSpark(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

void funcSquall(Board& board, handCard& cards, uint16_t x, uint16_t y)
{
}

void funcGale(Board& board, handCard& cards)
{
}

// modify board, handcard if modified
void funcHurricane(Board& board, handCard& cards)
{
}

// move card one position to another
void funcGust(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// exchange illusion card with other card
void funcMirage(Board& board, handCard& cards, uint16_t x1, uint16_t y1)
{
}

// remove stack of cards
void funcStorm(Board& board, uint16_t x, uint16_t y)
{
}

// swap cards or stack of cards
void funcTide(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// play again an illusion (cannot have 2 illusions at the same time)
void funcMist(Board& board, uint16_t x, uint16_t y)
{
}

// move a card/stack to an empty adjacent space and place new card in the empty space created
void funcWave(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// move 2 cards separated by empty space into the empty space and place them as stacks
void funcWhirlpool(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

// make the line unplayable for the next round
void funcBlizzard(line& line)
{
}

// stack the cards of the row/column on top of each other
void funcWaterfall(line& line)
{
}

// increase value of a card by one, marker also placed on the card (tournament mode)
void funcSupport(Board& board, uint16_t x, uint16_t y)
{
}

// remove all visible 1-value cards
void funcEarthquake(Board& board)
{
}

// value of a card decreased by 1, marker placed on card
void funcCrumble(Board& board,uint16_t x, uint16_t y)
{
}

// defines a border in a position
void funcBorder(Board& board, uint16_t x, uint16_t y)
{
}

void funcAvalanche(Board& board, uint16_t x1 , uint16_t y1, uint16_t x2, uint16_t y2, char direction)
{
}

//cover a illusion with a card
void funcRock(Board& board, uint16_t x, uint16_t y)
{
}

void funcDefault()
{
	return;
}
