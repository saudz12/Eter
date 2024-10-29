#include "Player.h"

bool Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetUsedIllusion() const
{
	return m_usedIllusion;
}

bool Player::GetHandSize() const
{
	return m_handSize;
}

std::map<MinionCard, int> Player::GetHandCards() const
{
	return m_handCards;
}
