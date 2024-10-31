#pragma once
#include "MinionCard.h"
#include <unordered_map>
#include <string>
#include <cstdint>
#include <string_view>

class Player
{
private:
	std::string m_playerColor;
	bool m_illusionUsage; //true if illusion has been used, false otherwise
	std::unordered_map<MinionCard, uint16_t> m_handCards;
public:
	//constructor
	Player(std::string_view playerColor);

	//getters
	std::string GetPlayerColor() const;
	bool GetUsedIllusion() const;
	const std::unordered_map<MinionCard, uint16_t>& GetHandCards() const;

	//setters
	void SetPlayerColor(std::string_view playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const std::unordered_map<MinionCard, uint16_t>& handCards);
};