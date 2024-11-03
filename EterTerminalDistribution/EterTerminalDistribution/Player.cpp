#include "Player.h"

Player::Player(std::string_view playerColor) : m_playerColor{ playerColor }, m_illusionUsage{ false } {}
Player::Player()
	: m_playerColor{ 'R' }, m_illusionUsage{ false }
{
}
std::string Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetUsedIllusion() const
{
	return m_illusionUsage;
}

const std::unordered_map<int, uint16_t>& Player::GetHandCards() const
{
	return m_handCards;
}

void Player::SetPlayerColor(char playerColor)
{
	m_playerColor = playerColor;
}

void Player::SetIllusionUsage(bool illusionUsage)
{
	m_illusionUsage = illusionUsage;
}

void Player::SetHandCards(const std::unordered_map<int, uint16_t>& handCards)
{
	m_handCards = handCards;
}