#include "Player.h"

Player::Player(std::string_view playerColor) : m_playerColor{ playerColor }, m_illusionUsage{ false }, m_handSize{ 0 } {}

std::string Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetUsedIllusion() const
{
	return m_illusionUsage;
}

bool Player::GetHandSize() const
{
	return m_handSize;
}

std::unordered_map<MinionCard, int> Player::GetHandCards() const
{
	return m_handCards;
}

void Player::SetPlayerColor(std::string_view playerColor)
{
	m_playerColor = playerColor;
}

void Player::SetIllusionUsage(bool illusionUsage)
{
	m_illusionUsage = illusionUsage;
}

void Player::SetHandSize(int handSize)
{
	m_handSize = handSize;
}

void Player::SetHandCards(std::unordered_map<MinionCard, int> handCards)
{
	m_handCards = handCards;
}
