#include "Player.h"

Player::Player(char playerColor = 'R')
	: m_playerColor{ playerColor }, m_illusionUsage{ false }, m_eterCardUsage{ false }
{
	//generateTrainingModeHand();
	generateHand();
}

Player::Player(Colours playerColor = Colours::RED)
	: m_playerColor{ playerColor }, m_illusionUsage{ false }, m_eterCardUsage{ false }
{
	generateHand();
}

Player::Player()
	: m_playerColor{ 'R' }, m_illusionUsage{ false }, m_eterCardUsage{ false }
{
	generateHand();
}

//char Player::GetPlayerColor() const
//{
//	return m_playerColor;
//}

Colours Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetIllusionUsage() const
{
	return m_illusionUsage;
}

bool Player::GetEterCardUsage() const
{
	return m_eterCardUsage;
}

const hand& Player::GetHandCards() const
{
	return m_handCards;
}

hand& Player::GetHandCards()
{
	return m_handCards;
}

const hand& Player::GetRemovedCards() const
{
	return m_removedCards;
}

void Player::SetEterCardUsage(bool eterCardUsage)
{
	m_eterCardUsage = eterCardUsage;
}

//void Player::SetPlayerColor(char playerColor)
//{
//	m_playerColor = playerColor;
//}

void Player::SetPlayerColor(Colours playerColor)
{
	m_playerColor = playerColor;
}

void Player::SetIllusionUsage(bool illusionUsage)
{
	m_illusionUsage = illusionUsage;
}

void Player::SetHandCards(const hand& handCards)
{
	m_handCards = handCards;
}

//1 if unsucessfull, 0 updates was completed
int Player::UpdateCard(const MinionCard& card, int cnt)
{
	//bounds
	if (cnt != 1 && cnt != -1)
		return 1;
	//change if found
	if (m_handCards.find(card) == m_handCards.end())
		return 1;
	m_handCards[card] += cnt;
	if (m_handCards[card] == 0)
		m_handCards.erase(card);
	return 0;
}

void Player::updateCover(uint16_t x, uint16_t y, coveredSet& coveredCardSet, resizeableMatrix& board)
{
	if (board[x][y].size() == 1)
		return;

	int pos = board[x][y].size() - 2;
	MinionCard& lastPlaced = board[x][y].back();
	MinionCard& coveredCard = board[x][y][pos];
	if (lastPlaced.GetColor() != coveredCard.GetColor())
		coveredCardSet.emplace(x, y, pos);
}

void Player::applyTansformToCovered(Player& p1, Player& p2, cardStack& stack, uint16_t oldX, uint16_t oldY, uint16_t newX, uint16_t newY)
{
	auto& p1Covered = p1.getCovered();
	auto& p2Covered = p2.getCovered();

	coveredSet p1Moved;
	coveredSet p2Moved;

	for (int i = 0; i < stack.size() - 1; i++) {
		position toFind{ oldX, oldY, i };
		auto currCardColor = stack[i].GetColor();
		if (currCardColor == Colours::RED) {
			p1Moved.insert({ newX, newY, i });
			p1Covered.erase(p1Covered.find(toFind));
		}
		else {
			p2Moved.insert({newX, newY, i});
			p2Covered.erase(p2Covered.find(toFind));
		}
	}
	for (auto& newPosition : p1Moved) {
		p1Covered.insert(newPosition);
	}
	for (auto& newPosition : p2Moved) {
		p2Covered.insert(newPosition);
	}
}

void Player::returnStackToHand(hand& h1, hand& h2, cardStack& stack)
{
	hand& currHand = h1;
	for (auto& card : stack) {
		if (card.GetColor() == Colours::RED)
			currHand = h1;
		else
			currHand = h2;

		if (currHand.find(card) != currHand.end())
			currHand[card]++;
		else
			currHand.insert({ card, 1 });
	}
}

void Player::generateTrainingModeHand()
{
	m_handCards.clear();

	//creating minion cards with their value and color
	MinionCard combatCard1(1, m_playerColor, false);
	MinionCard combatCard2(2, m_playerColor, false);
	MinionCard combatCard3(3, m_playerColor, false);
	MinionCard combatCard4(4, m_playerColor, false);

	m_handCards.emplace(combatCard1, 2);
	m_handCards.emplace(combatCard2, 2);
	m_handCards.emplace(combatCard3, 2);
	m_handCards.emplace(combatCard4, 1);
}

void Player::generateHand()
{
	m_handCards.clear();

	m_handCards.emplace(MinionCard{ 1, m_playerColor, false }, 2);
	m_handCards.emplace(MinionCard{ 2, m_playerColor, false }, 3);
	m_handCards.emplace(MinionCard{ 3, m_playerColor, false }, 3);
	m_handCards.emplace(MinionCard{ 4, m_playerColor, false }, 1);
	m_handCards.emplace(MinionCard{ 1, m_playerColor, true }, 1); //eter card has the value 1 
}

MinionCard* Player::GetLastMinionCardPlayed() const
{
	return m_lastMinionCardPlayed;
}

MinionCard* Player::GetIllusionCard() const
{
	return m_illusionCard;
}

coveredSet& Player::getCovered()
{
	return this->m_coveredCardSet;
}

void Player::SetIllusionCard(MinionCard* illusionCard)
{
	m_illusionCard = illusionCard;
}

void Player::SetLastMinionCardPlayed(MinionCard* cardPlayed)
{
	m_lastMinionCardPlayed = cardPlayed;
}


bool Player::placeMinionCardFromHand(MinionCard& card)
{
	if (m_handCards.at(card) != 0)
	{
		card.SetBelongsTo(m_playerColor);
		m_handCards[card]--;
		m_lastMinionCardPlayed = &card;
		return true;
	}
	else
	{
		return false;
	}
}

void Player::returnMinionCardToHand(const MinionCard& card)
{
	if (m_handCards.find(card) != m_handCards.end())
		m_handCards[card]++;
	else
		m_handCards.emplace(card, 1);
}

void Player::returnLastMinionCardToHand()
{
	m_handCards[(*m_lastMinionCardPlayed)]++;
}

void Player::addToRemovedCards(const MinionCard& card)
{
	if (m_removedCards.find(card) != m_removedCards.end())
		m_removedCards[card]++;
	else
		m_removedCards.emplace(card, 1);
}

bool Player::placeMinionCardFromRemovedCard(const MinionCard& card)
{
	bool placed = false;
	if (m_removedCards.find(card) != m_removedCards.end())
	{
		if (m_removedCards[card] != 0)
		{
			m_removedCards[card]--;
			placed = true;
		}
	}
	return placed;
}

bool Player::printCoveredCards(resizeableMatrix& matrix)
{
	if (m_coveredCardSet.size() == 0) {
		std::cout << "You have no covered cards..\n";
		return false;
	}
	int i = 0;
	std::cout << "Covered cards:\n";
	for (auto& card :m_coveredCardSet) {
		auto [x, y, posInStack] = card;

		std::cout << ++i << ". " <<"position:"<< posInStack << "," 
			<<"color"<<matrix[x][y][posInStack].GetColor()<<","
			<<"value"<< matrix[x][y][posInStack].GetValue() << "\n";
	}
	return true;
}

void Player::printHandCards()
{
	std::cout << "\nYour Hand:\n";
	for (auto& i : m_handCards) 
	{
		if (i.first.GetIsEterCard() && m_eterCardUsage == false)
			std::cout << "Eter Card: " << i.second << " Left\n";
		else 
			std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << " Left\n";
	}
}

Player& Player::operator=(const Player& p)
{
	if (this == &p)
	{
		return *this;
	}

	m_handCards = p.m_handCards;
	m_coveredCardSet = p.m_coveredCardSet;
	m_playerColor = p.m_playerColor;
	m_illusionUsage = p.m_illusionUsage;
	m_eterCardUsage = p.m_eterCardUsage;
	m_lastMinionCardPlayed = p.m_lastMinionCardPlayed;
	m_illusionCard = p.m_illusionCard;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const position& posTuple)
{
	os << "{" << std::get<0>(posTuple) << ", " << std::get<0>(posTuple) << ": " << std::get<0>(posTuple) << "}";

	return os;
}
