#include "functionsElementalCards.h"

//to note it may be more efficient to make m_board member public in Board class to not copy the contents of the matrix every time we modify it 

// maybe generate new ExplosionCard
void funcControlledExplosion(Board& board,Player& pl1,Player& pl2)
{
	if (board.getRowCount() != board.getMaxSize() || board.getColCount() != board.getMaxSize())
	{
		std::cout << "this card cannot be placed because the board is not to it's max size";
		return;
	}
	ExplosionCard explCard(board.getMaxSize());
	board.applyExplosionOnBoard(explCard, pl1, pl2);
}

// implement in player last card played
void funcDestruction(Board& board,Player& player)
{
	MinionCard* toberemoved = player.GetLastMinionCardPlayed();
	resizeableMatrix& matrix = board.getMatrix();
	for (int i = 0;i < board.getRowCount();i++)
		for (int j = 0;j < board.getColCount();j++)
			if (&matrix[i][j].front() == toberemoved) {
				matrix[i][j].pop_front();
				break;
			}
	player.returnLastMinionCardToHand();
}

// first 2 uint16_t for revealing Illusion and the next for placing Card
void funcFlame(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,MinionCard& CardToBePlaced)
{
	resizeableMatrix& matrix = board.getMatrix();
	matrix[x1][y1].front().SetIsIllusionCard(false);
	matrix[x2][y2].push_front(CardToBePlaced);

}

//this function still needs a way to check whether or not the move is valid
void funcFire(Board& board, Player& player1, Player& player2, uint16_t value)
{
	uint16_t cardCount = 0; //at least 2 card for elemental power to work
	std::vector<std::tuple<MinionCard, int, int>> returningCards; //minion card on top, x and y coordonates
	resizeableMatrix& matrix = board.getMatrix();
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
		if (board.removePos(xCoordonate, yCoordonate, matrix[xCoordonate][yCoordonate].size() - 1) == 1)
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

void funcAsh(Board& board, Player& player, uint16_t value, uint16_t x, uint16_t y)
{
	if (player.placeMinionCardFromRemovedCard(value) == true)
	{
		std::cout << "Successfully placed card from removed cards pool at position(" << x << ", " << y << ")\n";
		board.setPos(x, y, value, player.GetPlayerColor());
	}
	else
	{
		std::cout << "Failed to place card from removed cards pool at position (" << x << " , " << y << ")\n";
	}
}

/* versiune saud cu set si move -- ramane de terminat do not touch!!! 
void funcSpark(Board& board, Player& player, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (!player.printCoveredCards()) {
		return;
	}
	covered& coveredCards = player.getCovered();
	resizeableMatrix& matrix = board.getMatrix();

	//can't create isolated spaces

	int i;
	std::cout << "Chose a covered card to move: ";
	std::cin >> i;
}
*/

void funcSpark(Board& board,char plColor) 
{
	int x1, y1, x2, y2;

	std::cout << "choose a wherefrom to remove one of your cards:\n";
	std::cin >> x1 >> y1;

	std::cout << "choose a destination to place the card\n";
	std::cin >> x2 >> y2;

	uint16_t lines = board.getRowCount(), cols = board.getColCount();

	if (x1<0 || x1>lines||
		x2<0 || x2>lines ||
		 y1<0 || y1>cols||
		  y2<0 || y2>cols )
			return;

	resizeableMatrix& matrix = board.getMatrix();
	std::vector<std::pair<MinionCard,uint16_t>> plCards;

	if (!matrix[x1][y1].empty())
	{
		std::cout<<"here are the cards that you can replace\n";
		int index = 0;
		for (size_t k = 0; k < matrix[x1][y1].size(); ++k)
		{
			if (matrix[x1][y1][k].GetColor() == plColor)
			{
				plCards.emplace_back(matrix[x1][y1][k],k);
				std::cout << k << " .value:" << matrix[x1][y1][k] << '\n';
			}
		}
		std::cout << "which card (index) would you like to take out and place on a different place?\n";
		int chosenIndex;
		std::cin >> chosenIndex;
		while (!(chosenIndex >= 1 && chosenIndex < matrix[x1][y1].size()))
		{
			std::cout << "invalid index, try an index that belongs to the range\n";
			std::cin >> chosenIndex;
		}
	
		matrix[x1][y1].erase(matrix[x1][y1].begin()+chosenIndex );
		matrix[x2][y2].push_back(plCards[chosenIndex-1].first);
		board.setMatrix(matrix);
	}
	else
		std::cout << "invalid position, no cards here\n";
}

void funcSquall(Board& board, Player& player, uint16_t x, uint16_t y)
{
	Board oldModel;
	Board::cloneMatrix(board, oldModel);

	//funcionToCheck(currModel, T...);

	resizeableMatrix& matrix = board.getMatrix();

	
	if (matrix[x][y].empty()) {
		std::cout << "Empty Space..\n";
		return;
	}
	MinionCard toReturn = matrix[x][y].back();

	if (toReturn.GetColor() != player.GetPlayerColor()) {
		std::cout << "Not oponent card..\n";
		return;
	}

	matrix[x][y].pop_back();
	
	if (isolatedSpaces(board)) {
		Board::cloneMatrix(board, oldModel);
		std::cout << "Can't have isolated stacks/cards..\n";
		return;
	}

	hand& otherHand = player.GetHandCards();
	if (otherHand.find(toReturn) != otherHand.end()) {
		otherHand[toReturn]++;
	}
	else
		otherHand.insert({toReturn, 1});

	

	
	return;
}

void funcGale(Board& board, handCard& cardsPlRed,handCard& cardsPlBlue)
{
	resizeableMatrix& matrix = board.getMatrix();
	for (size_t i = 0; i < board.getRowCount(); ++i)
	{
		for (size_t j = 0; j < board.getColCount(); ++j)
		{
			while (matrix[i][j].size() >= 2)
			{
				MinionCard& topCard = matrix[i][j].back();
				matrix[i][j].pop_back();
				if (topCard.GetBelongsTo() == 'R')
					cardsPlRed.insert({ topCard, 1 });
				else
					cardsPlBlue.insert({ topCard,1 });
			}
		}
	}
	board.setMatrix(matrix);
}

// modify board, handcard if modified
void funcHurricane(Board& board, hand& h1, hand& h2)
{
	resizeableMatrix& matrix = board.getMatrix();

	//--from here
	std::string type;
	std::cout << "\nMove Row(R) or Column(C): ";
	std::cin >> type;

	if (type != "R" && type != "C") {
		std::cout << "Invalid Type..\n";
		return;
	}

	uint16_t lineCnt;
	std::cout << "\nWhich line: ";
	std::cin >> lineCnt;

	if (lineCnt < 0  && (type == "R" && lineCnt > board.getLineCount() - 1 || type == "C" && lineCnt > board.getColCount() - 1)) {
		std::cout << "Invalid line..\n";
		return;
	}
	if (type == "R") {
		for(auto& stack : matrix[lineCnt])
			if (stack.empty()) {
				std::cout << "Row has empty spaces..\n";
				return;
			}
	}
	if (type == "C") {
		for(auto& row : matrix)
			if (row[lineCnt].empty()) {
				std::cout << "Column has empty spaces..\n";
				return;
			}
	}

	std::string dir;
	std::cout << "\nWhich direction (left(L)/right(R) for Row, up(U)/down(D) for Column): ";
	std::cin >> dir;

	if (type == "R" && dir != "L" && dir != "R" || type == "C" && dir != "U" && dir != "D") {
		std::cout << "Ivalid direction..\n";
		return;
	}
	//--to here can be moved outside of function - either a checkHurricane(input) and get input in game OR do check full in game, then pass them as parameters
	
	//code looks ugly - can fix it later by request

	hand& cards = h1; //like this for the moment so we have it init

	//if type = row
	if (type == "R") {

		//if we shift to left
		if (dir == "L") {
			cardStack& firstStack = matrix[lineCnt][0];
			
			//update hand by card stack -- can move to function 
			Player::returnStackToHand(h1, h2, firstStack);

			//update counts
			board.shiftLine(0, board.getColCount() - 1, +1, lineCnt, 1);

			board.checkForUpdates();
			return;
		}
		//we know we are shifting to right
		cardStack& firstStack = matrix[lineCnt][board.getColCount() - 1];
		
		Player::returnStackToHand(h1, h2, firstStack);

		board.shiftLine(board.getColCount() - 1, 0, -1, lineCnt, 1);

		board.checkForUpdates();
		return;
	}

	//we know we are shifting a column
	if (dir == "U") {
		cardStack& firstStack = matrix[0][lineCnt];
		
		Player::returnStackToHand(h1, h2, firstStack);

		board.shiftLine(0, board.getRowCount() - 1, +1, lineCnt, 0);

		board.checkForUpdates();
		return;
	}
	//only down remains
	cardStack& firstStack = matrix[board.getRowCount() - 1][lineCnt];
	
	Player::returnStackToHand(h1, h2, firstStack);

	board.shiftLine(board.getRowCount() - 1, 0, -1, lineCnt, 0);
	
	board.checkForUpdates();
	return;
}

// move card one position to another
void funcGust(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	/*
	int x1, y1, x2, y2;
                std::cout << "from (x1,y1):";
                std::cin >> x1 >> y1;
                std::cout << "to (x2,y2):";
                std::cin >> x2 >> y2;
                funcGust(*b, x1, y1, x2,y2);
	*/
	resizeableMatrix& matrix = board.getMatrix();

	if (!((x1 == x2 && std::abs(y1 - y2) == 1) || (y1 == y2) && std::abs(x1 - x2)))
		return;
	if (!(matrix[x1][y1].back().GetValue() > matrix[x2][y2].back().GetValue()))
		return;

	MinionCard& movedCard = matrix[x1][y1].back();
	matrix[x1][y1].pop_back();

	matrix[x2][y2].push_back(movedCard);

	board.setMatrix(matrix);
}

// exchange illusion card with other card
void funcMirage(Board& board, handCard& cards, uint16_t x1, uint16_t y1,const MinionCard& chosenCard)
{
	resizeableMatrix& matrix = board.getMatrix();
	if (!matrix[x1][y1].front().GetIsIllusionCard()) {
		std::cout << "Chosen card position is not an illusion\n";
		return;
	}
	///trebuie facuta adaugare la nr de carti / insertie in handcard si schimbarea valorii cartii de pe tabla
	cards[matrix[x1][y1].front()]++;
	cards[chosenCard]--;
	matrix[x1][y1].front() = chosenCard;

}

// remove stack of cards
void funcStorm(Board& board, uint16_t x, uint16_t y)
{
	resizeableMatrix& matrix = board.getMatrix();
	if (matrix[x][y].size() >= 2)
		matrix[x][y].clear();
	else
		std::cout << "The stack does not have enough cards..\n";
}

// swap cards or stack of cards
void funcTide(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	cardStack& first = board.getStackOnPos(x1, y1);
	cardStack& second = board.getStackOnPos(x2, y2);

	if (first.back().GetColor() == 'R') {
		board.updateRowChecker(x1, RED_DEC);
		board.updateColChecker(y1, RED_DEC);
		board.updateRowChecker(x2, RED_ADD);
		board.updateColChecker(y2, RED_ADD);
	}
	else {
		board.updateRowChecker(x1, BLUE_DEC);
		board.updateColChecker(y1, BLUE_DEC);
		board.updateRowChecker(x2, BLUE_ADD);
		board.updateColChecker(y2, BLUE_ADD);
	}
	if (second.back().GetColor() == 'R') {
		board.updateRowChecker(x1, RED_ADD);
		board.updateColChecker(y1, RED_ADD);
		board.updateRowChecker(x2, RED_DEC);
		board.updateColChecker(y2, RED_DEC);
	}
	else {
		board.updateRowChecker(x1, BLUE_ADD);
		board.updateColChecker(y1, BLUE_ADD);
		board.updateRowChecker(x2, BLUE_DEC);
		board.updateColChecker(y2, BLUE_DEC);
	}



	cardStack aux = std::move(first);
	first = std::move(second);
	second = std::move(aux);

	//std::swap(first, second);
}

// play again an illusion (cannot have 2 illusions at the same time)
void funcMist(Board& board, uint16_t x, uint16_t y)
{

}

// move a card/stack to an empty adjacent space and place new card in the empty space created
void funcWave(Board& board, uint16_t x1, uint16_t y1, MinionCard newCard)
{
	resizeableMatrix& matrix = board.getMatrix();
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
void funcWhirlpool(Board& board, uint16_t x, uint16_t y)
{
	resizeableMatrix& matrix = board.getMatrix();

	if (!matrix[x][y].empty())
	{
		std::cout << "Chosen space must be empty\n";
		return;
	}

	if ((x < 0 || x >= board.getRowCount()) || (y < 0 || y >= board.getColCount()))
	{
		std::cout << "Chosen space is out of bounds\n";
		return;
	}
	
	std::cout << "Type R if you want to whirlpool the row or C if you want to whirlpool the column\n";
	char lineType;
	std::cin >> lineType;

	if (lineType == 'R')
	{
		if (y - 1 < 0 || y + 1 >= board.getColCount()) //check if the adjacent spaces are out of bounds
		{
			std::cout << "Adjacent spaces are out of bounds\n";
			return;
		}

		if (matrix[x][y - 1].empty() || matrix[x][y + 1].empty()) //check if the adjancent spaces are empty;
		{
			std::cout << "One or both of the adjacents spaces are empty\n";
			return;
		}

		MinionCard leftCard = matrix[x][y - 1].back();
		matrix[x][y - 1].pop_back();
		if (leftCard.GetColor() == 'R')
		{
			board.updateRowChecker(x, RED_DEC);
			board.updateColChecker(y - 1, RED_DEC);
		}
		else
		{
			board.updateRowChecker(x, BLUE_DEC);
			board.updateColChecker(y - 1, BLUE_DEC);
		}

		MinionCard rightCard = matrix[x][y + 1].back();
		matrix[x][y + 1].pop_back();
		if (rightCard.GetColor() == 'R')
		{
			board.updateRowChecker(x, RED_DEC);
			board.updateColChecker(y + 1, RED_DEC);
		}
		else
		{
			board.updateRowChecker(x, BLUE_DEC);
			board.updateColChecker(y + 1, BLUE_DEC);
		}

		if (leftCard.GetValue() < rightCard.GetValue())
		{
			matrix[x][y].push_back(leftCard);
			matrix[x][y].push_back(rightCard);
		}
		else if (leftCard.GetValue() > rightCard.GetValue())
		{
			matrix[x][y].push_back(rightCard);
			matrix[x][y].push_back(leftCard);
		}
		else if (leftCard.GetValue() == rightCard.GetValue())
		{
			std::cout << "Cards are equal in value, type L if you want the left card on top, type R if you want the right card on top\n";
			char direction;
			std::cin >> direction;
			if (direction == 'L')
			{
				matrix[x][y].push_back(rightCard);
				matrix[x][y].push_back(leftCard);
			}
			else if (direction == 'R')
			{
				matrix[x][y].push_back(leftCard);
				matrix[x][y].push_back(rightCard);
			}
			else
			{
				"You didn't type L or R";
			}
		}
		if (matrix[x][y].back().GetColor() == 'R')
		{
			board.updateRowChecker(x, RED_ADD);
			board.updateColChecker(y, RED_ADD);
		}
		else
		{
			board.updateRowChecker(x, BLUE_ADD);
			board.updateColChecker(y, BLUE_ADD);
		}
	}
	else if (lineType == 'C')
	{
		if (x - 1 < 0 || x + 1 >= board.getRowCount()) //check if the adjacent spaces are out of bounds
		{
			std::cout << "Adjacent spaces are out of bounds\n";
			return;
		}

		if (matrix[x - 1][y].empty() || matrix[x + 1][y].empty()) //check if the adjancent spaces are empty;
		{
			std::cout << "One or both of the adjacents spaces are empty\n";
			return;
		}

		MinionCard upCard = matrix[x - 1][y].back();
		matrix[x - 1][y].pop_back();
		if (upCard.GetColor() == 'R')
		{
			board.updateRowChecker(x - 1, RED_DEC);
			board.updateColChecker(y, RED_DEC);
		}
		else
		{
			board.updateRowChecker(x - 1, BLUE_DEC);
			board.updateColChecker(y, BLUE_DEC);
		}

		MinionCard downCard = matrix[x + 1][y].back();
		matrix[x + 1][y].pop_back();
		if (downCard.GetColor() == 'R')
		{
			board.updateRowChecker(x + 1, RED_DEC);
			board.updateColChecker(y, RED_DEC);
		}
		else
		{
			board.updateRowChecker(x + 1, BLUE_DEC);
			board.updateColChecker(y, BLUE_DEC);
		}

		if (upCard.GetValue() < downCard.GetValue())
		{
			matrix[x][y].push_back(upCard);
			matrix[x][y].push_back(downCard);
		}
		else if (upCard.GetValue() > downCard.GetValue())
		{
			matrix[x][y].push_back(downCard);
			matrix[x][y].push_back(upCard);
		}
		else if (upCard.GetValue() == downCard.GetValue())
		{
			std::cout << "Cards are equal in value, type U if you want the above card on top, type D if you want the below card on top\n";
			char direction;
			std::cin >> direction;
			if (direction == 'U')
			{
				matrix[x][y].push_back(downCard);
				matrix[x][y].push_back(upCard);
			}
			else if (direction == 'D')
			{
				matrix[x][y].push_back(upCard);
				matrix[x][y].push_back(downCard);
			}
			else
			{
				"You didn't type U or D";
				return;
			}
		}
		if (matrix[x][y].back().GetColor() == 'R')
		{
			board.updateRowChecker(x, RED_ADD);
			board.updateColChecker(y, RED_ADD);
		}
		else
		{
			board.updateRowChecker(x, BLUE_ADD);
			board.updateColChecker(y, BLUE_ADD);
		}
	}
	else
	{
		std::cout << "You didn't type R or C\n";
		return;
	}
	board.checkForUpdates();
	std::cout << "Whirlpool used successfully on " << x << " " << y << '\n';
}

// make the line unplayable for the next round
void funcBlizzard(line& line)
{
}

//still needs validation 
void funcWaterfall(Board& board, uint16_t columnIndex)
{
	if (columnIndex > board.getColCount() || columnIndex < 0)
	{
		std::cout << "Chosen column doesn't exit\n";
		return;
	}

	resizeableMatrix matrix = board.getMatrix();
	uint16_t condition = 0; //the final stack of cards must have at least 3 cards

	std::stack<MinionCard> cards;

	for (size_t i = 0; i < board.getRowCount(); i++)
	{
		if (!matrix[i][columnIndex].empty())
		{
			condition += matrix[i][columnIndex].size();
			std::deque<MinionCard> cardsCopy = matrix[i][columnIndex];
			while (!cardsCopy.empty())
			{
				cards.push(cardsCopy.back());
				cardsCopy.pop_back();
			}
		}
	}

	if (condition < 3)
	{
		std::cout << "There must be at least 3 cards in this column for this elemental power card to work\n";
		return;
	}
	else
	{
		for (size_t i = 0; i < board.getRowCount(); i++)
		{
				board.removeStack(i, columnIndex);
		}
		while (!cards.empty())
		{
			if (board.setPosWaterfall(board.getRowCount() - 1, columnIndex, cards.top().GetValue(), cards.top().GetColor()) == 0)
			{
				std::cout << "card placed successfully on " << board.getRowCount() - 1 << " " << columnIndex << '\n';
			}
			else
			{
				std::cout << "failed to place card on " << board.getRowCount() - 1 << " " << columnIndex << '\n';
			}
			cards.pop();
		}
		std::cout << "Waterfall used successfully on column " << columnIndex << "\n";
	}
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
	resizeableMatrix& matrix = board.getMatrix();
	for (int i = 0;i < board.getRowCount();i++)
		for (int j = 0;j < board.getColCount();j++)
			if (matrix[i][j].front().GetValue() == 1)
				matrix[i][j].pop_front();
}

// value of a card decreased by 1, marker placed on card
void funcCrumble(Board& board,uint16_t x, uint16_t y)
{
	resizeableMatrix& matrix = board.getMatrix();
	int CardValue = matrix[x][y].front().GetValue();
	if (CardValue < 2)	//check according to game rules
	{
		std::cout << "Card value is too low, choose a higher value card. \n";
		return;
	}
	matrix[x][y].front().SetValue(CardValue - 1);
	matrix[x][y].front().SetMarker(true);
}

// defines a border in a position
void funcBorder(Board& board, uint16_t x, uint16_t y)
{
}

//will clean it later
//Moves 2 stacks on the same lane by 1 square to a empty place ( - x x - ) --> can have ( - - x x ) or ( x x - - ).
void funcAvalanche(Board& board, uint16_t x1 , uint16_t y1, uint16_t x2, uint16_t y2, char direction)
{
	if (std::abs(y1 - y2) != 1 && x1 == x2) { //horizontal - side to side in the sime row
		if (direction != 'L' && direction != 'R') {
			std::cout << "Invalid direction.\n";
			return;
		}
		auto& leftStack = board.getStackOnPos(x1, std::min(y1, y2));
		auto& rightStack = board.getStackOnPos(x2, std::max(y1, y2));
		
		//check left
		if (direction == 'L'){
			if (std::min(y1, y2) == 0) {
				std::cout << "Invalid direction.\n";
				return;
			}
			auto& destinationStack = board.getStackOnPos(x1, std::min(y1, y2) - 1);
			if (!destinationStack.empty()) {
				std::cout << "Not an empty space!.\n";
				return;
			}
			destinationStack = std::move(leftStack);
			leftStack = std::move(rightStack);
			rightStack = std::move(cardStack());

			return;
		}

		//now we only have right available
		if (std::max(y1, y2) == board.getColCount() - 1) {
			std::cout << "Invalid direction.\n";
			return;
		}
		auto& destinationStack = board.getStackOnPos(x1, std::max(y1, y2) + 1);
		if (!destinationStack.empty()) {
			std::cout << "Not an empty space!.\n";
			return;
		}
		destinationStack = std::move(rightStack);
		rightStack = std::move(rightStack);
		leftStack = std::move(cardStack());
		return;
	}
	else if (std::abs(x1 - x2) != 1 && y1 == y2) {//vertical - side to side in the same column
		if (direction != 'U' && direction != 'D') {
			std::cout << "Invalid direction.\n";
			return;
		}
		auto& upperStack = board.getStackOnPos(std::min(x1, x2), y1);
		auto& lowerStack = board.getStackOnPos(std::max(x1, x2), y2);

		//check up
		if (direction == 'U') {
			if (std::min(x1, x2) == 0) {
				std::cout << "Invalid direction.\n";
				return;
			}
			auto& destinationStack = board.getStackOnPos(std::min(x1, x2) - 1, y1);
			if (!destinationStack.empty()) {
				std::cout << "Not an empty space!.\n";
				return;
			}
			destinationStack = std::move(upperStack);
			upperStack = std::move(lowerStack);
			lowerStack = std::move(cardStack());

			return;
		}

		//now we only have right available
		if (std::min(x1, x2) == board.getRowCount() - 1) {
			std::cout << "Invalid direction.\n";
			return;
		}
		auto& destinationStack = board.getStackOnPos(std::max(x1, x2) + 1, y1);
		if (!destinationStack.empty()) {
			std::cout << "Not an empty space!.\n";
			return;
		}
		destinationStack = std::move(lowerStack);
		lowerStack = std::move(upperStack);
		upperStack = std::move(cardStack());

		return;
	}
	std::cout << "Stacks MUST be Adjacent.\n";
	return;
}

//cover a illusion with a card
void funcRock(Board& board, uint16_t x, uint16_t y,MinionCard& Card)	
{
	resizeableMatrix matrix = board.getMatrix();
	if (!matrix[x][y].front().GetIsIllusionCard())
	{
		std::cout << "Chosen card is not an illusion, choose an illusion card. \n.";
		return;
	}
	matrix[x][y].push_front(Card);
}

void funcDefault()
{
	return;
}
