#include "Player.h"

Player::Player(char playerColor) 
	: m_playerColor{ playerColor }, m_illusionUsage{ false } 
{
}

Player::Player()
	: m_playerColor{ 'R' }, m_illusionUsage{ false }
{
}

Player::~Player()
{
	m_lastMinionCardPlayed = nullptr;
}

char Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetUsedIllusion() const
{
	return m_illusionUsage;
}

const std::unordered_map<MinionCard, uint16_t>& Player::GetHandCards() const
{
	return m_handCards;
}

MinionCard* Player::GetLastMinionCardPlayed() const
{
	return m_lastMinionCardPlayed;
}

void Player::SetPlayerColor(char playerColor)
{
	m_playerColor = playerColor;
}

void Player::SetIllusionUsage(bool illusionUsage)
{
	m_illusionUsage = illusionUsage;
}

void Player::SetHandCards(const std::unordered_map<MinionCard, uint16_t>& handCards)
{
	m_handCards = handCards;
}

void Player::SetLastMinionCardPlayed(MinionCard* cardPlayed)
{
	m_lastMinionCardPlayed = cardPlayed;
}

void Player::generateTrainingModeHand()
{
	//creating minion cards with their value and color
	MinionCard combatCard1(1, m_playerColor);
	MinionCard combatCard2(2, m_playerColor);
	MinionCard combatCard3(3, m_playerColor);
	MinionCard combatCard4(4, m_playerColor);

	//add the minions card in hand with their respective amount
	m_handCards[combatCard1] = 2; //2 of the combatCard1
	m_handCards[combatCard2] = 2;
	m_handCards[combatCard3] = 2;
	m_handCards[combatCard4] = 1;
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
	m_handCards[card]++;
}

void Player::returnLastMinionCardToHand()
{
	m_handCards[(*m_lastMinionCardPlayed)]++;
}
