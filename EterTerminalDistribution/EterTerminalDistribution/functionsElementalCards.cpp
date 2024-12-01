#include "functionsElementalCards.h"

//to note it may be more efficient to make m_board member public in Board class to not copy the contents of the matrix every time we modify it 

//generate a new explosion and use it
uint16_t funcControlledExplosion(Board& board, Player& pl1, Player& pl2)
{
	Board copyBoard(3);
	Board::cloneMatrix(board, copyBoard);

	Player copyPl1 = pl1;
	Player copyPl2 = pl2;

	if (board.getRowCount() != board.getMaxSize() || board.getColCount() != board.getMaxSize())
	{
		std::cout << "This card cannot be placed because the board is not to it's max size\n";
		return 1;
	}
	ExplosionCard explCard(board.getMaxSize());
	board.applyExplosionOnBoard(explCard, pl1, pl2);
	if (isolatedSpaces(board)) {
		Board::cloneMatrix(copyBoard, board);
		pl1 = copyPl1;
		pl2 = copyPl2;
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	return 0;
}

//remove from play last card played by opponent
uint16_t funcDestruction(Board& board, Player& player)
{
	Board copyBoard(3);
	Board::cloneMatrix(board, copyBoard);

	MinionCard* toberemoved = player.GetLastMinionCardPlayed();
	if (toberemoved->GetIsEterCard())
	{
		std::cout << "Can't use Destruction elemental card on eter card\n";
		return 1;
	}

	resizeableMatrix& matrix = board.getMatrix();
	for (int i = 0; i < board.getRowCount(); i++)
		for (int j = 0; j < board.getColCount(); j++)
			if (!matrix[i][j].empty() && &board.getCardOnPos(i, j) == &*toberemoved) {
				if (board.removePos(i, j) == 1)
				{
					std::cout << "Failed to remove card\n";
					return 1;
				}
				break;
			}

	if (isolatedSpaces(board)) {
		Board::cloneMatrix(copyBoard, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	player.addToRemovedCards(*toberemoved);
	player.SetLastMinionCardPlayed(nullptr);
	board.checkForUpdates();

	return 0;
}

//reveals an illusion and then play a card
//first 2 uint16_t for revealing Illusion and the next for placing Card
//returns 1 if it failed to place card, 0 if it succeeded
//moved the if to checkInput
uint16_t funcFlame(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard& CardToBePlaced, Player& p)
{
	/*if (checkFuncFlame(board, x1, y1, x2, y2, CardToBePlaced, p) != 0)
		return 1;*/
	resizeableMatrix& matrix = board.getMatrix();
	matrix[x1][y1].back().SetIsIllusionCard(false);
	return 0;
}

//return to hand all cards with a specific value
uint16_t funcFire(Board& board, Player& player1, Player& player2, uint16_t value)
{
	/*if (checkFuncFire(board, value) != 0)
		return 1;*/

	Board copyBoard(3);
	Board::cloneMatrix(board, copyBoard);
	Player copyPl1 = player1;
	Player copyPl2 = player2;

	//at least 2 card for elemental power to work
	uint16_t cardCount = 0;
	//minion card on top, x and y coordonates
	std::vector<std::tuple<MinionCard, int, int>> returningCards;
	resizeableMatrix& matrix = board.getMatrix();
	for (size_t i = 0; i < board.getRowCount(); i++)
	{
		for (size_t j = 0; j < board.getColCount(); j++)
		{
			if (!matrix[i][j].empty())
			{
				MinionCard cardOnPos = board.getCardOnPos(i, j);
				if (cardOnPos.GetValue() == value && !cardOnPos.GetIsEterCard())
				{
					cardCount++;
					returningCards.push_back({ cardOnPos, i, j });
				}
			}
		}
	}

	if (cardCount < 2)
	{
		std::cout << "Not enough cards on board with chosen value\n";
		return 1;
	}

	for (size_t i = 0; i < returningCards.size(); i++)
	{
		MinionCard card = std::get<0>(returningCards[i]);
		int xCoordonate = std::get<1>(returningCards[i]);
		int yCoordonate = std::get<2>(returningCards[i]);

		if (board.removePos(xCoordonate, yCoordonate) == 1)
			return 1;

		//checking which player is getting his card returned to hand
		if (card.GetColor() == player1.GetPlayerColor())
		{
			player1.returnMinionCardToHand(card);
		}
		else
		{
			player2.returnMinionCardToHand(card);
		}
	}

	if (isolatedSpaces(board))
	{
		Board::cloneMatrix(copyBoard, board);
		player1 = copyPl1;
		player2 = copyPl2;
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}
	board.checkForUpdates();

	return 0;
}

//play a card which was removed
uint16_t funcAsh(Board& board, Player& player, const MinionCard& card, uint16_t x, uint16_t y)
{
	/*if (checkFuncAsh(board, card, x, y) != 0)
		return 1;*/

	if (player.placeMinionCardFromRemovedCard(card) == true)
	{
		if (board.setPos(x, y, card, player) == 1)
			return 1;
	}
	else
	{
		player.addToRemovedCards(card);
		return 1;
	}

	return 0;
}

/* versiune saud cu set si move -- ramane de terminat do not touch!!! 
uint16_t funcSpark(Board& board, Player& player, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
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

//move a card which was covered by your opponent's card
uint16_t funcSpark(Board& board, Player& p)  //this function needs to be reworked
{

	int x1, y1, x2, y2;

	std::cout << "choose where from to remove one of your cards:\n";
	std::cin >> x1 >> y1;

	std::cout << "choose a destination to place the card\n";
	std::cin >> x2 >> y2;

	/*if (checkFuncSpark(board, x1, y1, x2, y2) != 0)
		return 1;*/
	
	resizeableMatrix& matrix = board.getMatrix();
	std::vector<std::pair<MinionCard,uint16_t>> plCards;

	
	if (!matrix[x1][y1].empty())
	{
		std::cout << "here are the cards that you can replace\n";
		int index = 0;
		for (size_t k = 0; k < matrix[x1][y1].size(); ++k)
		{
			if (matrix[x1][y1][k].GetColor() == p.GetPlayerColor())
			{
				plCards.emplace_back(matrix[x1][y1][k], k);
				std::cout << k + 1 << " .value:" << matrix[x1][y1][k] << '\n';
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

		matrix[x1][y1].erase(matrix[x1][y1].begin() + chosenIndex - 1);
		if (board.setPos(x2, y2, plCards[chosenIndex - 1].first, p) == 1)
		{
			std::cout << "Failed to place minion card\n";
			return 1;
		}
	}
	else
	{
		std::cout << "invalid position, no cards here\n";
		return 1;
	}

	return 0;
}

//return to your opponent's hand one of his visible cards
uint16_t funcSquall(Board& board, Player& player, uint16_t x, uint16_t y)
{
	/*if (checkFuncSquall(board, x, y) != 0)
		return 1;*/

	Board oldModel(3);
	Board::cloneMatrix(board, oldModel);

	resizeableMatrix& matrix = board.getMatrix();

	MinionCard toReturn = matrix[x][y].back();

	if (toReturn.GetColor() != player.GetPlayerColor()) {
		std::cout << "Not oponent card..\n";
		return 1;
	}

	board.removePos(x, y);
	
	if (isolatedSpaces(board)) {
		Board::cloneMatrix(oldModel, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	player.returnMinionCardToHand(toReturn);
	board.checkForUpdates();

	return 0;
}

//remove all cards which are covered by other cards
uint16_t funcGale(Board& board, Player& p1, Player& p2)
{
	resizeableMatrix& matrix = board.getMatrix();
	for (size_t i = 0; i < board.getRowCount(); ++i)
	{
		for (size_t j = 0; j < board.getColCount(); ++j)
		{
			while (matrix[i][j].size() >= 2)
			{
				MinionCard& bottomCard = matrix[i][j].front();
				matrix[i][j].pop_front();
				if (bottomCard.GetBelongsTo() == p1.GetPlayerColor())
					p1.addToRemovedCards(bottomCard);
				else
					p2.addToRemovedCards(bottomCard);
			}
		}
	}
	
	return 0;
}

// modify board, handcard if modified
uint16_t funcHurricane(Board& board, hand& h1, hand& h2, uint16_t lineCnt, std::string_view type, std::string_view direction)
{
	Board oldModel(3);
	Board::cloneMatrix(board, oldModel);

	resizeableMatrix& matrix = board.getMatrix();

	int start, end, ratio, orientation;
	
	if (type == ID_ROW) {
		if (direction == DIR_LEFT) {
			start = 0;
			end = board.getColCount() - 1;
			ratio = +1;
		}
		else {
			start = board.getColCount() - 1;
			end = 0;
			ratio = -1;
		}
		orientation = 1;
	}
	else {
		if (direction == DIR_UP) {
			start = 0;
			end = board.getRowCount() - 1;
			ratio = +1;
		}
		else {
			start = board.getRowCount() - 1;
			end = 0;
			ratio = -1;
		}
		orientation = 0;
	}
	

	int firstX = orientation ? lineCnt : start;
	int firstY = orientation ? start : lineCnt;

	/*
	int firstX;
	int firstY;

	auto setup = [&firstX, &firstY](uint16_t start, uint16_t lineCnt, uint16_t orientation) {
		if (orientation) {
			firstX = lineCnt;
			firstY = start;
		}
		else {
			firstX = start;
			firstY = lineCnt;
		}
	};

	setup(start, lineCnt, orientation);
	*/

	board.shiftLine(start, end, ratio, lineCnt, orientation);

	if (isolatedSpaces(board))
	{
		Board::cloneMatrix(oldModel, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	cardStack& firstStack = matrix[firstX][firstY];
	Player::returnStackToHand(h1, h2, firstStack);

	board.checkForUpdates();

	return 0;
}

// move a card onto a neighboring card of a lower value
uint16_t funcGust(Board& board, Player& pl, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	/*if (checkFuncGust(board, x1, y1, x2, y2) != 0)
		return 1;*/

	Board oldModel(3);
	Board::cloneMatrix(board, oldModel);
	Player copyPl = pl;

	resizeableMatrix& matrix = board.getMatrix();

	MinionCard& movedCard = matrix[x1][y1].back();
	if (board.removePos(x1, y1) == 1)
		return 1;

	if (board.setPos(x2, y2, movedCard, pl) == 1)
		return 1;

	if (isolatedSpaces(board))
	{
		pl = copyPl;
		Board::cloneMatrix(oldModel, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	board.checkForUpdates();

	return 0;
}

// exchange illusion card with other card
uint16_t funcMirage(Board& board, Player& p, uint16_t x1, uint16_t y1, const MinionCard& chosenCard)
{
	/*if (checkFuncMirage(board, x1, y1, chosenCard) != 0)
		return 1;*/

	resizeableMatrix& matrix = board.getMatrix();
	MinionCard returningCard = board.getCardOnPos(x1, y1);
	returningCard.SetIsIllusionCard(false);

	if (board.removePos(x1, y1) == 1)
		return 1;

	p.returnMinionCardToHand(returningCard);

	if (board.setPos(x1, y1, chosenCard, p) == 1)
		return 1;

	return 0;
}

// remove stack of cards
void funcStorm(Board& board, Player& p1, Player& p2, uint16_t x, uint16_t y)
{
	resizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].back().GetIsIllusionCard())
		matrix[x][y].back().SetIsIllusionCard(false);

	while (!matrix[x][y].empty())
	{
		if (matrix[x][y].back().GetColor() == p1.GetPlayerColor())
			p1.addToRemovedCards(matrix[x][y].back());
		else
			p2.addToRemovedCards(matrix[x][y].back());
		matrix[x][y].pop_back();
	}
}

// swap cards or stack of cards
void funcTide(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	cardStack& first = board.getStackOnPos(x1, y1);
	cardStack& second = board.getStackOnPos(x2, y2);

	if (first.back().GetColor() == Colours::RED) {
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
	if (second.back().GetColor() == Colours::RED) {
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
void funcMist(Board& board, Player& p, uint16_t x, uint16_t y, MinionCard& card)
{
	if (!p.GetIllusionUsage() || p.GetIllusionCard() == nullptr) {
		card.SetIsIllusionCard(true);
		p.SetIllusionUsage(true);
	}
}

// move a card/stack to an empty adjacent space and place new card in the empty space created
void funcWave(Board& board, uint16_t x1, uint16_t y1, MinionCard newCard)
{
	resizeableMatrix& matrix = board.getMatrix();
	for(int i = -1; i < 2; i++)
		for(int j = -1; j < 2; j++)
		if (!matrix[x1 + i][y1 + j].empty()) 
		{
			while (!matrix[x1][y1].empty())
			{
				matrix[x1 + i][y1 + j].push_back(matrix[x1][y1].front());
			}
			matrix[x1][y1].push_front(newCard);
			break;
		}
}

// move 2 cards separated by empty space into the empty space and place them as stacks
void funcWhirlpool(Board& board, uint16_t x, uint16_t y)
{
	resizeableMatrix& matrix = board.getMatrix();
	
	std::cout << "Type R if you want to whirlpool the row or C if you want to whirlpool the column\n";
	char lineType;
	std::cin >> lineType;

	if (lineType == 'R')
	{
		MinionCard leftCard = matrix[x][y - 1].back();
		matrix[x][y - 1].pop_back();
		if (leftCard.GetColor() == Colours::RED)
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
		if (rightCard.GetColor() == Colours::RED)
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
		if (matrix[x][y].back().GetColor() == Colours::RED)
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
		MinionCard upCard = matrix[x - 1][y].back();
		matrix[x - 1][y].pop_back();
		if (upCard.GetColor() == Colours::RED)
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
		if (downCard.GetColor() == Colours::RED)
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
		if (matrix[x][y].back().GetColor() == Colours::RED)
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

	resizeableMatrix& matrix = board.getMatrix();
	//the final stack of cards must have at least 3 cards
	uint16_t condition = 0;

	std::stack<MinionCard> cards;

	for (size_t i = 0; i < board.getRowCount(); i++)
	{
		if (!matrix[i][columnIndex].empty())
		{
			if (!matrix[i][columnIndex].back().GetIsEterCard())
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
			if (board.setPosWaterfall(board.getRowCount() - 1, columnIndex, cards.top()) == 0)
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
	resizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].back().GetIsEterCard())
	{
		std::cout << "Can't use Support elemental card on eter card\n";
		return;
	}

	if (matrix[x][y].back().GetIsIllusionCard())
	{
		std::cout << "Can't use Support elemental card on illusion card\n";
		return;
	}

	int CardValue = matrix[x][y].back().GetValue();
	if (CardValue > 3)	//check according to game rules
	{
		std::cout << "Card value is too great, choose a lower value card. \n";
		return;
	}

	if (matrix[x][y].back().GetIsIllusionCard())
	{
		matrix[x][y].back().SetIsIllusionCard(false);
	}

	matrix[x][y].back().SetValue(CardValue + 1);
	matrix[x][y].back().SetMarker(true);
}

// remove all visible 1-value cards
void funcEarthquake(Board& board)
{
	resizeableMatrix& matrix = board.getMatrix();

	for (int i = 0;i < board.getRowCount();i++)
		for (int j = 0;j < board.getColCount();j++)
			if (matrix[i][j].back().GetValue() == 1 && !matrix[i][j].back().GetIsEterCard() && !matrix[i][j].back().GetIsIllusionCard())
				matrix[i][j].pop_back();
}

// value of a card decreased by 1, marker placed on card
void funcCrumble(Board& board,uint16_t x, uint16_t y)
{
	resizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].back().GetIsEterCard())
	{
		std::cout << "Can't use Crumble elemental card on eter card\n";
		return;
	}

	if (matrix[x][y].back().GetIsIllusionCard())
	{
		std::cout << "Can't use Crumble elemental card on illusion card\n";
		return;
	}

	int CardValue = matrix[x][y].back().GetValue();
	if (CardValue < 2)	//check according to game rules
	{
		std::cout << "Card value is too low, choose a higher value card. \n";
		return;
	}
	matrix[x][y].back().SetValue(CardValue - 1);
	matrix[x][y].back().SetMarker(true);
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

		if (leftStack.back().GetIsEterCard() || rightStack.back().GetIsEterCard())
		{
			std::cout << "Can't use Avalanche elemental card on eter card\n";
			return;
		}
		
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
void funcRock(Board& board, uint16_t x, uint16_t y, MinionCard& Card)
{
	resizeableMatrix matrix = board.getMatrix();
	if (!matrix[x][y].back().GetIsIllusionCard())
	{
		std::cout << "Chosen card is not an illusion, choose an illusion card. \n.";
		return;
	}
	matrix[x][y].push_back(Card);
}

void funcDefault()
{
	return;
}
