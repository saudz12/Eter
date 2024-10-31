#include "Player.h"

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

std::unordered_map<Card, int> Player::GetHandCards() const
{
	return m_handCards;
}