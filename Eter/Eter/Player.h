#pragma once
#include "MinionCard.h"

#include <unordered_map>

class Player
{
private:
	std::string m_playerColor;
	bool m_illusionUsage; //true if illusion has been used, false otherwise
	int m_handSize;
	std::unordered_map<MinionCard, int> m_handCards;
public:
	Player(std::string_view playerColor);

	//getters
	std::string GetPlayerColor() const;
	bool GetUsedIllusion() const;
	bool GetHandSize() const;
	std::unordered_map<MinionCard, int> GetHandCards() const;

	//setters
	void SetPlayerColor(std::string_view playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandSize(int handSize);
	void SetHandCards(std::unordered_map<MinionCard, int> handCards);
};

