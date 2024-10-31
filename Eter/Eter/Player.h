#pragma once
#include "MinionCard.h"
#include <unordered_map>
#include <string>

class Player
{
private:
	std::string m_playerColor;
	bool m_illusionUsage; //true if illusion has been used, false otherwise
	int m_handSize;
	std::unordered_map<Card, int> m_handCards;
public:
	//getters
	std::string GetPlayerColor() const;
	bool GetUsedIllusion() const;
	bool GetHandSize() const;
	std::unordered_map<Card, int> GetHandCards() const;
}