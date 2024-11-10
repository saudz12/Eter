
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

//still need to implement if this move is valid or not
void funcFire(Board& board, Player& player1, Player& player2, uint16_t value)
{
	uint16_t cardCount = 0; //at least 2 card for elemental power to work
	std::vector<std::tuple<MinionCard, int, int>> returningCards; //minion card on top, x and y coordonates
	resizeableMatrix matrix = board.getMatrix();
	for (size_t i = 0; i < board.getRowCount(); i++)
	{
		for (size_t j = 0; j < board.getColCount(); j++)
		{
			MinionCard cardOnPos = board.getCardOnPos(i, j);
			if (cardOnPos.GetValue() == value)
			{
				cardCount++;
				returningCards.push_back({ cardOnPos, i, j });
			}
		}
	}

	if (cardCount < 2)
	{
		std::cout << "Not enough cards on board with chosen value\n";
		return;
	}

	for (size_t i = 0; i < returningCards.size(); i++)
	{
		MinionCard card = std::get<0>(returningCards[i]);
		int xCoordonate = std::get<1>(returningCards[i]);
		int yCoordonate = std::get<2>(returningCards[i]);
		if (board.removePos(xCoordonate, yCoordonate, matrix[xCoordonate][yCoordonate].size()) == 1)
			std::cout << "Failed to remove card at position (" << xCoordonate << " , " << yCoordonate << ")\n";
		else
			std::cout << "Successfully removed card at position(" << xCoordonate << ", " << yCoordonate << ")\n";
		if (card.GetColor() == player1.GetPlayerColor()) //checking which player is getting his card returned to hand
		{
			player1.returnMinionCardToHand(card);
		}
		else
		{
			player2.returnMinionCardToHand(card);
		}
	}
}

// maybe also keep all the removed cards in unordered set
void funcAsh(Board& board, Player& player, MinionCard& card, uint16_t x, uint16_t y)
{
	if (player.placeMinionCardFromRemovedCard(card) == true)
	{
		std::cout << "Successfully placed card from removed cards pool at position(" << x << ", " << y << ")\n";
	}
	else
	{
		std::cout << "Failed to place card from removed cards pool at position (" << x << " , " << y << ")\n";
	}

	board.setPos(x, y, card.GetValue(), player.GetPlayerColor());
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
	resizeableMatrix matrix = board.getMatrix();
	while (!matrix[x][y].empty())
		matrix[x][y].pop_front();
	board.setMatrix(matrix);
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
void funcWave(Board& board, uint16_t x1, uint16_t y1,MinionCard newCard)
{
	resizeableMatrix matrix = board.getMatrix();
	for(int i=-1;i<2;i++)
		for(int j=-1;j<2;j++)
		if (!matrix[x1+i][y1+j].empty()) 
		{
			while (!matrix[x1][y1].empty())
			{
				matrix[x1+i][y1+j].push_back(matrix[x1][y1].front());
			}
			matrix[x1][y1].push_front(newCard);
			break;
		}
	board.setMatrix(matrix);
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
void funcRock(Board& board, uint16_t x, uint16_t y,MinionCard& Card)
{
	resizeableMatrix matrix = board.getMatrix();
	if (!matrix[x][y].front().GetIsIllusionCard())
	{
		std::cout << "Chosen card is not an illusion, choose an illusion card. \n.";
	}
	matrix[x][y].push_front(Card);
}

void funcDefault()
{
	return;
}
