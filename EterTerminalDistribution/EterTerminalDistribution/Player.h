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
	MinionCard* m_lastMinionCardPlayed; //pointer towards the last card played
public:
	//constructor
	Player(char playerColor);
	Player();
	~Player();
	//getters
	char GetPlayerColor() const;
	bool GetUsedIllusion() const;
	const std::unordered_map<MinionCard, uint16_t>& GetHandCards() const;
	MinionCard* GetLastMinionCardPlayed() const;

	//setters
	void SetPlayerColor(char playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const std::unordered_map<MinionCard, uint16_t>& handCards);
	void SetLastMinionCardPlayed(MinionCard* cardPlayed);

	void generateTrainingModeHand();
	bool placeMinionCardFromHand(MinionCard& card); //returns true if card was found in handCards, false otherwise
	void returnMinionCardToHand(const MinionCard& card); //returns a specific minion card to hand
	void returnLastMinionCardToHand(); //returns last played minion card to hand
};