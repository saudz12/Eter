#include "functionsElementalCards.h"
#include "ErrorPrints.h"

//to note it may be more efficient to make m_board member public in Board class to not copy the contents of the matrix every time we modify it 

//generate a new explosion and use it
uint16_t funcControlledExplosion(Board& board, Player& pl1, Player& pl2)
{
	Board copyBoard(3);
	Board::cloneMatrix(board, copyBoard);

	Player copyPl1 = pl1;
	Player copyPl2 = pl2;

	if (board.GetRowCount() != board.getMaxSize() || board.GetColCount() != board.getMaxSize())
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
	//after moving the board to shared pointers and the covered and last played to weak pointers, rewrite it
	/*Board copyBoard(3);
	Board::cloneMatrix(board, copyBoard);

	MinionCard* toberemoved = player.GetLastMinionCardPlayed();
	if (toberemoved->GetIsEterCard())
	{
		std::cout << "Can't use Destruction elemental card on eter card\n";
		return 1;
	}

	ResizeableMatrix& matrix = board.getMatrix();
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
	board.checkForUpdates();*/

	return 0;
}

//reveals an illusion and then play a card
//first 2 uint16_t for revealing Illusion and the next for placing Card
//returns 1 if it failed to place card, 0 if it succeeded
//moved the if to checkInput
void funcFlame(Board& _board, int16_t _xi, int16_t _yi, Player& _player, int16_t _val, int16_t _xp, int16_t _yp)
{
	///*if (checkFuncFlame(board, x1, y1, x2, y2, CardToBePlaced, p) != 0)
	//	return 1;*/
	//if (board.setPos(x2, y2, CardToBePlaced, p) == 1)
	//	return 1;
	//ResizeableMatrix& matrix = board.getMatrix();
	//matrix[x1][y1].back().SetIsIllusionCard(false);


	//return 0;

	_board.RemoveIllusionProperty(_xi, _xi);
	_board.PlaceCard(_player.PlayCard(_val), _xp, _yp);
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
	ResizeableMatrix& matrix = board.getMatrix();
	for (int16_t i = 0; i < board.GetRowCount(); i++)
	{
		for (int16_t j = 0; j < board.GetColCount(); j++)
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

	for (int16_t i = 0; i < returningCards.size(); i++)
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
uint16_t funcAsh(Board& board, Player& player, const MinionCard& card, int16_t x, int16_t y)
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

//move a card which was covered by your opponent's card
uint16_t funcSpark(Board& board, Player& p)  //this function needs to be reworked
{

	int16_t x1, y1, x2, y2;

	std::cout << "choose where from to remove one of your cards:\n";
	std::cin >> x1 >> y1;

	std::cout << "choose a destination to place the card\n";
	std::cin >> x2 >> y2;

	/*if (checkFuncSpark(board, x1, y1, x2, y2) != 0)
		return 1;*/
	
	ResizeableMatrix& matrix = board.getMatrix();
	std::vector<std::pair<MinionCard,uint16_t>> plCards;

	
	if (!matrix[x1][y1].empty())
	{
		std::cout << "here are the cards that you can replace\n";
		int index = 0;
		for (int16_t k = 0; k < matrix[x1][y1].size(); ++k)
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
uint16_t funcSquall(Board& _board, Player& player, uint16_t x, uint16_t y)
{

	MinionCard& toReturn = _board.getCardOnPos(x, y);
	player.ReturnCard(std::move(toReturn));
	_board.RemoveCard(x, y, 0);

	_board.checkForUpdates();

	return 0;
}

//remove all cards which are covered by other cards
uint16_t funcGale(Board& board, Player& p1, Player& p2)
{
	ResizeableMatrix& matrix = board.getMatrix();
	for (int16_t i = 0; i < board.GetRowCount(); ++i)
	{
		for (int16_t j = 0; j < board.GetColCount(); ++j)
		{
			while (matrix[i][j].size() >= 2)
			{
				MinionCard& bottomCard = matrix[i][j].front();
				matrix[i][j].pop_front();
				if (bottomCard.GetColor() == p1.GetPlayerColor())
					p1.addToRemovedCards(bottomCard);
				else
					p2.addToRemovedCards(bottomCard);
			}
		}
	}
	


	return 0;
}

// modify board, handcard if modified
void funcHurricane(Board& _board, Hand& _h1, Hand& _h2, uint16_t _lineCnt, LineType _type, Directions _direction)
{
	int start, orientation;
	
	orientation = int16_t (_type == LineType::TYPE_ROW);

	if (_direction == Directions::DIR_LEFT || _direction == Directions::DIR_UP) {
		start = 0;
	}
	else if(_direction == Directions::DIR_RIGHT){
		start = _board.GetColCount() - 1;
	}
	else {
		start = _board.GetRowCount() - 1;
	}

	int firstX = orientation ? _lineCnt : start;
	int firstY = orientation ? start : _lineCnt;

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
	Player::ReturnStackToHand(_h1, _h2, _board.getStackOnPos(firstX, firstY)); //nu avem ce face :/

	_board.ShiftLine(_lineCnt, _type, _direction);

	_board.checkForUpdates(); //?move it outside? and check only once for all elementals/mages togehter with empty spaces???
}

// move a card onto a neighboring card of a lower value
uint16_t funcGust(Board& _board, Player& pl, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	/*if (checkFuncGust(board, x1, y1, x2, y2) != 0)
		return 1;*/
	MinionCard& toMove = _board.getCardOnPos(x1, y1);
	_board.PlaceCard(std::move(toMove), x2, y2);
	_board.RemoveCard(x1, y1, 0);
	//Board oldModel(3);
	//Board::cloneMatrix(board, oldModel);
	//Player copyPl = pl;

	//ResizeableMatrix& matrix = board.getMatrix();

	//MinionCard& movedCard = matrix[x1][y1].back();
	//MinionCard& movedCard = matrix[x1][y1].back();
	//if (_board.removePos(x1, y1) == 1)
	//	return 1;

	//if (_board.setPos(x2, y2, _movedCard, pl) == 1)
	//	return 1;

	//if (isolatedSpaces(board))
	//{
	//	pl = copyPl;
	//	Board::cloneMatrix(oldModel, board);
	//	std::cout << "Can't have isolated stacks/cards..\n";
	//	return 1;
	//}

	_board.checkForUpdates();

	return 0;
}
// exchange illusion card with other card
uint16_t funcMirage(Board& _board, Player& _p, int16_t x1, int16_t y1, MinionCard& chosenCard)
{
	/*if (checkFuncMirage(board, x1, y1, chosenCard) != 0)
		return 1;*/
	_board.RemoveIllusionProperty(x1, y1);
	MinionCard& returningCard = _board.getCardOnPos(x1, y1);
	_p.ReturnCard(std::move(returningCard));
	_board.RemoveCard(x1, y1, 0);
	_board.PlaceCard(std::move(chosenCard), x1, y1);
	//ResizeableMatrix& matrix = board.getMatrix();
	//returningCard.SetIsIllusionCard(false);

	//if (board.removePos(x1, y1) == 1)
	//	return 1;

//	p.returnMinionCardToHand(returningCard);

	//if (board.setPos(x1, y1, chosenCard, p) == 1)
		//return 1;

	return 0;
}


//remove stack of at least 2 cards
uint16_t funcStorm(Board& board, Player& p1, Player& p2, uint16_t x, uint16_t y)
{
	/*if (checkFuncStorm(board, x, y) != 0)
		return 1;*/

	Board oldModel(3);
	Board::cloneMatrix(board, oldModel);

	ResizeableMatrix& matrix = board.getMatrix();

	if (matrix[x][y].back().GetIsIllusionCard())
	{
		matrix[x][y].back().SetIsIllusionCard(false);
		if (matrix[x][y].back().GetColor() == Colours::RED)
			p1.SetIllusionCard(nullptr);
		else
			p2.SetIllusionCard(nullptr);

	}

	while (!matrix[x][y].empty())
	{
		if (matrix[x][y].back().GetColor() == p1.GetPlayerColor())
			p1.addToRemovedCards(matrix[x][y].back());
		else
			p2.addToRemovedCards(matrix[x][y].back());
		if (board.removePos(x, y) == 1)
			return 1;
	}

	if (isolatedSpaces(board))
	{
		Board::cloneMatrix(oldModel, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	board.checkForUpdates();

	return 0;
}

//swap cards or stack of cards
uint16_t funcTide(Board& board, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	ResizeableMatrix& matrix = board.getMatrix();

	CardStack& first = board.getStackOnPos(x1, y1);
	CardStack& second = board.getStackOnPos(x2, y2);

	if (first.back().GetColor() == Colours::RED) {
		if (x1 == y1)
		{
			board.updateFirstDiagChecker(RED_DEC);
		}

		if (x2 == y2)
		{
			board.updateFirstDiagChecker(RED_ADD);
		}

		if (x1 == matrix.size() - y1 - 1)
		{
			board.updateSeconDiagChecker(RED_DEC);
		}

		if (x2 == matrix.size() - y2 - 1)
		{
			board.updateSeconDiagChecker(RED_ADD);
		}

		board.updateRowChecker(x1, RED_DEC);
		board.updateColChecker(y1, RED_DEC);
		board.updateRowChecker(x2, RED_ADD);
		board.updateColChecker(y2, RED_ADD);
	}
	else {
		if (x1 == y1)
		{
			board.updateFirstDiagChecker(BLUE_DEC);
		}

		if (x2 == y2)
		{
			board.updateFirstDiagChecker(BLUE_ADD);
		}

		if (x1 == matrix.size() - y1 - 1)
		{
			board.updateSeconDiagChecker(BLUE_DEC);
		}

		if (x2 == matrix.size() - y2 - 1)
		{
			board.updateSeconDiagChecker(BLUE_ADD);
		}

		board.updateRowChecker(x1, BLUE_DEC);
		board.updateColChecker(y1, BLUE_DEC);
		board.updateRowChecker(x2, BLUE_ADD);
		board.updateColChecker(y2, BLUE_ADD);
	}

	if (second.back().GetColor() == Colours::RED) {
		if (x2 == y2)
		{
			board.updateFirstDiagChecker(RED_DEC);
		}

		if (x1 == y1)
		{
			board.updateFirstDiagChecker(RED_ADD);
		}

		if (x2 == matrix.size() - y2 - 1)
		{
			board.updateSeconDiagChecker(RED_DEC);
		}

		if (x1 == matrix.size() - y1 - 1)
		{
			board.updateSeconDiagChecker(RED_ADD);
		}

		board.updateRowChecker(x1, RED_ADD);
		board.updateColChecker(y1, RED_ADD);
		board.updateRowChecker(x2, RED_DEC);
		board.updateColChecker(y2, RED_DEC);
	}
	else {
		if (x2 == y2)
		{
			board.updateFirstDiagChecker(BLUE_DEC);
		}

		if (x1 == y1)
		{
			board.updateFirstDiagChecker(BLUE_ADD);
		}

		if (x2 == matrix.size() - y2 - 1)
		{
			board.updateSeconDiagChecker(BLUE_DEC);
		}

		if (x1 == matrix.size() - y1 - 1)
		{
			board.updateSeconDiagChecker(BLUE_ADD);
		}

		board.updateRowChecker(x1, BLUE_ADD);
		board.updateColChecker(y1, BLUE_ADD);
		board.updateRowChecker(x2, BLUE_DEC);
		board.updateColChecker(y2, BLUE_DEC);
	}

	CardStack aux = std::move(first);
	first = std::move(second);
	second = std::move(aux);

	//std::swap(first, second);

	return  0;
}

// play again an illusion (cannot have 2 illusions at the same time)
uint16_t funcMist(Board& board, Player& p, int16_t x, int16_t y, MinionCard& card)
{
	
	return  0;
}

// move a card/stack to an empty adjacent space and place new card in the empty space created
uint16_t funcWave(Board& board, Player& p, int16_t x1, int16_t y1, MinionCard newCard)
{
	ResizeableMatrix& matrix = board.getMatrix();
	for(int16_t i = -1; i < 2; i++)
	{
		for (int16_t j = -1; j < 2; j++)
		{
			if (!matrix[x1][y1].empty())
			{
				int16_t newX = x1 + i;
				int16_t newY = y1 + j;

				if (newX < 0 || newX >= board.GetColCount())
					continue;

				if (newY < 0 || newY >= board.GetRowCount())
					continue;

				if (matrix[newX][newY].empty())
				{
					if (board.getCardOnPos(x1, y1).GetColor() == Colours::RED)
					{
						if (x1 == y1)
							board.updateFirstDiagChecker(RED_DEC);

						if (x1 == matrix.size() - y1 - 1)
							board.updateSeconDiagChecker(RED_DEC);

						board.updateRowChecker(x1, RED_DEC);
						board.updateColChecker(y1, RED_DEC);
					}
					else
					{
						if (x1 == y1)
							board.updateFirstDiagChecker(BLUE_DEC);

						if (x1 == matrix.size() - y1 - 1)
							board.updateSeconDiagChecker(BLUE_DEC);

						board.updateRowChecker(x1, BLUE_DEC);
						board.updateColChecker(y1, BLUE_DEC);
					}

					while (!matrix[x1][y1].empty())
					{
						MinionCard card = matrix[x1][y1].front();
						//doesn't matter which player
						board.setPos(newX, newY, card, p);
						matrix[x1][y1].pop_front();
					}

					if (board.setPos(x1, y1, newCard, p) == 1)
						return 1;

					return 0;
				}
			}
		}
	}
}

void funcWhirlpool(Board& _board, uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, Preference _preference)
{
	int16_t xm = (_x1 + _x2) / 2;
	int16_t ym = (_y1 + _y2) / 2;
	if (_board.ViewTop(_x1, _y1).GetValue() == _board.ViewTop(_x2, _y2).GetValue()) {
		switch (_preference)
		{
		case Preference::FIRST:
			_board.PlayCard(_x1, _y1, xm, ym);
			_board.PlayCard(_x2, _y2, xm, ym);
			return;
		case Preference::SECOND:
			_board.PlayCard(_x2, _y2, xm, ym);
			_board.PlayCard(_x1, _y1, xm, ym);
			return;
		}
	}
	_board.PlayCard(_x1, _y1, xm, ym);
	_board.PlayCard(_x2, _y2, xm, ym);
}

// make the line unplayable for the next round
uint16_t funcBlizzard(Board& board, uint16_t index, char type)
{
	Board oldModel(3);
	Board::cloneMatrix(board, oldModel);

	MinionCard blizzard(0, Colours::INVALID_COL, false);
	blizzard.SetCardType(CardType::BlizzardCard);

	ResizeableMatrix& matrix = board.getMatrix();

	if (type == 'R')
	{
		for (size_t col = 0; col < board.GetColCount(); col++)
			matrix[index][col].push_back(blizzard);
	}
	else if (type == 'C')
	{
		for (size_t row = 0; row < board.GetRowCount(); row++)
			matrix[row][index].push_back(blizzard);
	}

	uint16_t emptySpaces = 0;

	for (size_t row = 0; row < board.GetRowCount(); row++)
	{
		for (size_t col = 0; col < board.GetColCount(); col++)
		{
			if (matrix[row][col].empty())
				emptySpaces++;
		}
	}

	if (!emptySpaces && board.isMatMaxSize())
	{
		Board::cloneMatrix(oldModel, board);
		std::cout << "\nNo empty spaces remaining for the opponent to place a card onto\n";
		return 1;
	}

	return 0;
}

//move all cards from a column at the bottom of that column
uint16_t funcWaterfall(Board& board, uint16_t x, uint16_t y)
{
	Board backupBoard;
	Board::cloneMatrix(board, backupBoard);

	ResizeableMatrix& matrix = board.getMatrix();

	//the card which will stay on top of the new stack
	MinionCard topCard = board.getCardOnPos(x, y);
	board.removePos(x, y);

	//the final stack of cards must have at least 3 cards
	int16_t condition = 1;

	std::stack<MinionCard> cards;

	for (size_t i = 0; i < board.GetRowCount(); i++)
	{
		if (!matrix[i][y].empty())
		{
			if (!matrix[i][y].back().GetIsEterCard())
			{
				condition += matrix[i][y].size();
				std::deque<MinionCard> cardsCopy = matrix[i][y];
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
		return 1;
	}
	else
	{
		for (size_t i = 0; i < board.GetRowCount(); i++)
		{
				board.removeStack(i, y);
		}

		uint16_t newX = board.GetRowCount() - 1;

		while (!cards.empty())
		{
			if (board.setPosWaterfall(newX, y, cards.top()) == 1)
				return 1;
			cards.pop();
		}

		if (board.setPosWaterfall(newX, y, topCard) == 1)
			return 1;

		if (topCard.GetColor() == Colours::RED)
		{
			if (newX == y)
			{
				board.updateFirstDiagChecker(RED_ADD);
			}

			if (newX == matrix.size() - y - 1)
			{
				board.updateSeconDiagChecker(RED_ADD);
			}

			board.updateColChecker(y, RED_ADD);
			board.updateRowChecker(newX, RED_ADD);
		}
		else if (topCard.GetColor() == Colours::BLUE)
		{
			if (newX == y)
			{
				board.updateFirstDiagChecker(BLUE_ADD);
			}

			if (newX == matrix.size() - y - 1)
			{
				board.updateSeconDiagChecker(BLUE_ADD);
			}

			board.updateColChecker(y, BLUE_ADD);
			board.updateRowChecker(newX, BLUE_ADD);
		}
	}

	if (isolatedSpaces(board))
	{
		Board::cloneMatrix(backupBoard, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	board.checkForUpdates();

	return  0;
}

// increase value of a card by one, marker also placed on the card (tournament mode)
uint16_t funcSupport(Board& board, uint16_t x, uint16_t y)
{
	ResizeableMatrix& matrix = board.getMatrix();
	int CardValue = matrix[x][y].back().GetValue();

	if (matrix[x][y].back().GetIsIllusionCard())
		matrix[x][y].back().SetIsIllusionCard(false);
	

	matrix[x][y].back().SetValue(CardValue + 1);
	matrix[x][y].back().SetMarker(true);

	return 0;
}

// remove all visible 1-value cards
uint16_t funcEarthquake(Board& board, Player& p1, Player& p2)
{
	Board backupBoard;
	Board::cloneMatrix(board, backupBoard);

	ResizeableMatrix& matrix = board.getMatrix();

	int16_t p1Cards{ 0 };
	int16_t p2Cards{ 0 };

	for (size_t i = 0; i < board.GetRowCount(); i++)
	{
		for (size_t j = 0; j < board.GetColCount(); j++)
		{
			if (!matrix[i][j].empty())
			{
				MinionCard card = board.getCardOnPos(i, j);
				if (card.GetValue() == 1)
				{
					if (card.GetColor() == p1.GetPlayerColor())
					{
						p1.addToRemovedCards(card);
						p1Cards++;
					}
					else
					{
						p2.addToRemovedCards(card);
						p2Cards++;
					}

					if (board.removePos(i, j) == 1)
						return 1;
				}
			}
		}
	}

	if (isolatedSpaces(board))
	{
		//Removing the cards from the removed cards pool
		while (p1Cards)
		{
			MinionCard card(1, p1.GetPlayerColor(), false);
			p1.placeMinionCardFromRemovedCard(card);
			p1Cards--;
		}

		while (p2Cards)
		{
			MinionCard card(1, p2.GetPlayerColor(), false);
			p2.placeMinionCardFromRemovedCard(card);
			p2Cards--;
		}

		Board::cloneMatrix(backupBoard, board);
		std::cout << "Can't have isolated stacks/cards..\n";
		return 1;
	}

	board.checkForUpdates();

	return 0;
}

// value of a card decreased by 1, marker placed on card
uint16_t funcCrumble(Board& _board,uint16_t _x, uint16_t _y)
{
	ResizeableMatrix& matrix = _board.getMatrix();
	int CardValue = matrix[_x][_y].back().GetValue();

	matrix[_x][_y].back().SetValue(CardValue - 1);
	matrix[_x][_y].back().SetMarker(true);

	return 0;
}

// defines a border in a position
uint16_t funcBorder(Board& board, int16_t x, int16_t y)
{

	if (x < 0)
	{
		x += board.GetRowCount();
		for (int16_t i = 0; i >= x; i--)
			board.AddLineOnTop();
	}

	if (y < 0)
	{
		y += board.GetColCount();
		for (int16_t i = 0; i >= y; i--)
			board.AddLineToLeft();
	}

	if (x > 0)
	{
		x -= board.GetRowCount();
		for (int16_t i = 0; i <= x; i++)
			board.AddLineOnBottom();
	}

	if (y > 0)
	{
		y -= board.GetColCount();
		for (int16_t i = 0; i <= y; i++)
			board.AddLineToRight();
	}

	return 0;
}

//Moves 2 stacks on the same lane by 1 square to a empty place ( - x x - ) --> can have ( - - x x ) or ( x x - - ).
void funcAvalanche(Board& _board, int16_t _x1 , int16_t _y1, int16_t _x2, int16_t _y2, Directions _direction)
{
	CardStack aux;
	LineType type;
	int16_t line;

	//we know the input is good from our input check
	if (_x1 == _x2) {
		type = LineType::TYPE_ROW;
		if (_direction == Directions::DIR_LEFT)
			aux = std::move(_board.getStackOnPos(_x1, std::min(_y1, _y2)));
		else
			aux = std::move(_board.getStackOnPos(_x1, std::max(_y1, _y2)));
		line = _x1;

	}
	else {
		type = LineType::TYPE_COLUMN;
		if (_direction == Directions::DIR_UP)
			aux = std::move(_board.getStackOnPos(std::min(_x1, _x2), _y1));
		else
			aux = std::move(_board.getStackOnPos(std::max(_x1, _x2), _y1));
		line = _x2;
	}

	_board.ShiftLine(line, type, _direction);
	//_board.PlaceStack(std::move(aux), _x1, _y1, BoardChanges::_NO_CHANGES); ///implement this
}

//cover a illusion with a card
uint16_t funcRock(Board& board, int16_t x, int16_t y, MinionCard& Card)
{
	MinionCard illusionCard = board.getCardOnPos(x, y);

	ResizeableMatrix& matrix = board.getMatrix();


	if (illusionCard.GetColor() == Colours::RED)
	{
		board.updateColChecker(y, RED_DEC);
		board.updateRowChecker(x, RED_DEC);
		if (x == y)
		{
			board.updateFirstDiagChecker(RED_DEC);
		}
		if (x == matrix.size() - 1)
		{
			board.updateSeconDiagChecker(RED_DEC);
		}
	}
	else if (illusionCard.GetColor() == Colours::BLUE)
	{
		board.updateColChecker(y, BLUE_DEC);
		board.updateRowChecker(x, BLUE_DEC);
		if (x == y)
		{
			board.updateFirstDiagChecker(BLUE_DEC);
		}
		if (x == matrix.size() - 1)
		{
			board.updateSeconDiagChecker(BLUE_DEC);
		}
	}

	//using setPosWaterfall because it doesn't mess up the illusion
	board.setPosWaterfall(x, y, Card);

	if (Card.GetColor() == Colours::RED)
	{
		board.updateColChecker(y, RED_ADD);
		board.updateRowChecker(x, RED_ADD);
		if (x == y)
		{
			board.updateFirstDiagChecker(RED_ADD);
		}
		if (x == matrix.size() - 1)
		{
			board.updateSeconDiagChecker(RED_ADD);
		}
	}
	else if (Card.GetColor() == Colours::BLUE)
	{
		board.updateColChecker(y, BLUE_ADD);
		board.updateRowChecker(x, BLUE_ADD);
		if (x == y)
		{
			board.updateFirstDiagChecker(BLUE_ADD);
		}
		if (x == matrix.size() - 1)
		{
			board.updateSeconDiagChecker(BLUE_ADD);
		}
	}

	return 0;
}

void funcDefault()
{
	return;
}
