#include "Player.h"

Player::Player(char playerColor = 'R')
	: m_playerColor{ playerColor }, m_illusionUsage{ false } 
{
	generateTrainingModeHand();
}

char Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetUsedIllusion() const
{
	return m_illusionUsage;
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

void Player::SetPlayerColor(char playerColor)
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
int Player::UpdateCard(int value, int cnt)
{
	//bounds
	if (value < 1 && value > 4 || cnt != 1 && cnt != -1)
		return 1;
	//change if found
	MinionCard toUpdate(value, m_playerColor);
	if (m_handCards.find(toUpdate) == m_handCards.end())
		return 1;
	m_handCards[toUpdate] += cnt;
	if (m_handCards[toUpdate] == 0)
		m_handCards.erase(toUpdate);
	return 0;
}

void Player::updateCover(uint16_t x, uint16_t y, covered& coveredCardSet, resizeableMatrix& board)
{
	if (board[x][y].size() == 1)
		return;

	int pos = board[x][y].size() - 2;
	MinionCard& lastPlaced = board[x][y].back();
	MinionCard& coveredCard = board[x][y][pos];
	if (lastPlaced.GetColor() != coveredCard.GetColor())
		coveredCardSet.emplace(x, y, pos);
}

void Player::generateTrainingModeHand()
{
	//creating minion cards with their value and color
	MinionCard combatCard1(1, m_playerColor);
	MinionCard combatCard2(2, m_playerColor);
	MinionCard combatCard3(3, m_playerColor);
	MinionCard combatCard4(4, m_playerColor);

	m_handCards.emplace(combatCard1, 2);
	m_handCards.emplace(combatCard2, 2);
	m_handCards.emplace(combatCard3, 2);
	m_handCards.emplace(combatCard4, 1);
}

MinionCard* Player::GetLastMinionCardPlayed() const
{
	return m_lastMinionCardPlayed;
}

covered& Player::getCovered()
{
	return this->m_coveredCardSet;
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

bool Player::placeMinionCardFromRemovedCard(uint16_t value)
{
	bool placed = false;
	for (auto& card : m_removedCards)
	{
		if (card.first.GetValue() == value && card.second > 0)
		{
			m_removedCards[card.first]--;
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

std::ostream& operator<<(std::ostream& os, const position& posTuple)
{
	os << "{" << std::get<0>(posTuple) << ", " << std::get<0>(posTuple) << ": " << std::get<0>(posTuple) << "}";

	return os;
}
