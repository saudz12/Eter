
#include "functionsElementalCards.h"

//to note it may be more efficient to make m_board member public in Board class to not copy the contents of the matrix every time we modify it 

// maybe generate new ExplosionCard
void funcControlledExplosion(Board& board, ExplosionCard& explCard)
{
}

// implement in player last card played
void funcDestruction(Board& board,Player& player)
{
	MinionCard* toberemoved = player.GetLastMinionCardPlayed();
	resizeableMatrix matrix = board.getMatrix();
	for (int i = 0;i < board.getRowCount();i++)
		for (int j = 0;j < board.getColCount();j++)
			if (&matrix[i][j].front() == toberemoved) {
				matrix[i][j].pop_front();
				break;
			}
	player.returnLastMinionCardToHand();
	board.setMatrix(matrix);
}

// first 2 uint16_t for revealing Illusion and the next for placing Card
void funcFlame(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,MinionCard& CardToBePlaced)
{
	resizeableMatrix matrix = board.getMatrix();
	matrix[x1][y1].front().SetIsIllusionCard(false);
	matrix[x2][y2].push_front(CardToBePlaced);
	board.setMatrix(matrix); 

}

// player Red, player Blue
void funcFire(Board& board, handCard& cardsPl1, handCard& cardsPl2)
{
}
// maybe also keep all the removed cards in unordered set
void funcAsh(Board& board, uint16_t x, uint16_t y)
{
}

void funcSpark(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
}

void funcSquall(Board& board, Player& player, uint16_t x, uint16_t y)
{
	resizeableMatrix matrix = board.getMatrix();
	hand Cards = player.GetHandCards();
	Cards.emplace(matrix[x][y].front());
	matrix[x][y].pop_front();
	player.SetHandCards(Cards);
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
	resizeableMatrix matrix = board.getMatrix();
	int CardValue = matrix[x][y].front().GetValue();
	if (CardValue > 3)	//check according to game rules
	{
		std::cout << "Card value is too great, choose a lower value card. \n";
		return;
	}
	matrix[x][y].front().SetValue(CardValue + 1);
	matrix[x][y].front().SetMarker(true);
	board.setMatrix(matrix);
}

// remove all visible 1-value cards
void funcEarthquake(Board& board)
{
	resizeableMatrix matrix = board.getMatrix();
	for (int i = 0;i < board.getRowCount();i++)
		for (int j = 0;j < board.getColCount();j++)
			if (matrix[i][j].front().GetValue() == 1)
				matrix[i][j].pop_front();
	board.setMatrix(matrix);
}

// value of a card decreased by 1, marker placed on card
void funcCrumble(Board& board,uint16_t x, uint16_t y)
{
	resizeableMatrix matrix = board.getMatrix();
	int CardValue = matrix[x][y].front().GetValue();
	if (CardValue < 2)	//check according to game rules
	{
		std::cout << "Card value is too low, choose a higher value card. \n";
		return;
	}
	matrix[x][y].front().SetValue(CardValue - 1);
	matrix[x][y].front().SetMarker(true);
	board.setMatrix(matrix);
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
