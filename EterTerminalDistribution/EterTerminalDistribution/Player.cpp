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

void Player::SetLastMinionCardPlayed(MinionCard* cardPlayed)
{
	m_lastMinionCardPlayed = cardPlayed;
}


bool Player::placeMinionCardFromHand(MinionCard& card)
{
	if (m_handCards.at(card) != 0)
	{
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
	if (m_removedCards.find(card) != m_removedCards.end() && m_removedCards[card] > 0)
	{
		m_removedCards[card]--;
		placed = true;
	}
	
	if (m_removedCards[card] == 0)
		m_removedCards.erase(card);

	return placed;
}
