#pragma once
#include "MinionCard.h"

using hand = std::unordered_map<MinionCard, uint16_t>;

class Player
{
private:
	char m_playerColor;
	hand m_handCards;
	bool m_illusionUsage; //true if illusion has been used, false otherwise
	
	void generateTrainingModeHand();
	MinionCard* m_lastMinionCardPlayed; //pointer towards the last card played
public:
	//constructor
	Player(char playerColor);
	//getters
	char GetPlayerColor() const;
	bool GetUsedIllusion() const;
	const hand& GetHandCards() const;
	MinionCard* GetLastMinionCardPlayed() const;

	//setters
	void SetPlayerColor(char playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const hand& handCards);
	int UpdateCard(int value, int cnt);

	void SetLastMinionCardPlayed(MinionCard* cardPlayed);
	bool placeMinionCardFromHand(MinionCard& card); //returns true if card was found in handCards, false otherwise
	void returnMinionCardToHand(const MinionCard& card); //returns a specific minion card to hand
	void returnLastMinionCardToHand(); //returns last played minion card to hand
};