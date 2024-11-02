#include "Player.h"

Player::Player(std::string_view playerColor) : m_playerColor{ playerColor }, m_illusionUsage{ false } {}

std::string Player::GetPlayerColor() const
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

void Player::SetPlayerColor(std::string_view playerColor)
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

void Player::generateTrainingModeHand()
{
	MinionCard combatCard1(1, m_playerColor);
	MinionCard combatCard2(2, m_playerColor);
	MinionCard combatCard3(3, m_playerColor);
	MinionCard combatCard4(4, m_playerColor);

	m_handCards[combatCard1] = 2;
	m_handCards[combatCard2] = 2;
	m_handCards[combatCard3] = 2;
	m_handCards[combatCard4] = 1;
}
