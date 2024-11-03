#pragma once
#include "MinionCard.h"
#include <unordered_map>
#include <string>
#include <cstdint>
#include <string_view>

class Player
{
private:
	char m_playerColor;
	std::unordered_map<MinionCard, uint16_t> m_handCards;
	bool m_illusionUsage; //true if illusion has been used, false otherwise
public:
	//constructor
	Player(char playerColor);
	Player();
	//getters
	char GetPlayerColor() const;
	bool GetUsedIllusion() const;
	const std::unordered_map<MinionCard, uint16_t>& GetHandCards() const;

	//setters
	void SetPlayerColor(char playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const std::unordered_map<MinionCard, uint16_t>& handCards);

	void generateTrainingModeHand();
};