#pragma once
#include "MinionCard.h"

using hand = std::unordered_map<MinionCard, uint16_t>;
//using coords = std::pair<uint16_t, uint16_t>;
using coveredSet = std::unordered_set<position, hashPosition>;

//moved from board. when implementing game, move updateCover functiouns to it
using cardStack = std::deque<MinionCard>;
using line = std::deque<cardStack>;
using resizeableMatrix = std::deque<line>;
using score = std::pair <uint16_t, uint16_t>; //<R/B>
using lineChecker = std::deque<score>;

class Player
{
private:
	hand m_handCards;
	coveredSet m_coveredCardSet;
	char m_playerColor;
	hand m_removedCards;
	bool m_illusionUsage; //true if illusion has been used, false otherwise
	MinionCard* m_lastMinionCardPlayed; //pointer towards the last card played

	void generateTrainingModeHand();
	
public:
	//constructor
	Player(char playerColor);

	//getters
	char GetPlayerColor() const;
	bool GetUsedIllusion() const;
	const hand& GetHandCards() const;
	hand& GetHandCards();
	const hand& GetRemovedCards() const;
	MinionCard* GetLastMinionCardPlayed() const;
	coveredSet& getCovered();

	//setters
	void SetPlayerColor(char playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const hand& handCards);

	//Updates
	int UpdateCard(int value, int cnt);
	//primeste coveredul la celelalt player
	static void updateCover(uint16_t x, uint16_t y, coveredSet& coveredCards, resizeableMatrix& board);
	//T(a, b) + T(c, d) = T(a + c, b + d) <-- aplicam asemenea transofmrari pe un coveredSet cand miscam un stack de marime > 1 -- cam consuming dar tabla e pera mica ca sa se simta
	static void applyTansformToCovered(Player& p1, Player& p2, cardStack& stack, uint16_t oldX, uint16_t oldY, uint16_t newX, uint16_t newY);
	static void returnStackToHand(hand& h1, hand& h2, cardStack& stack);

	void SetLastMinionCardPlayed(MinionCard* cardPlayed);
	bool placeMinionCardFromHand(MinionCard& card); //returns true if card was found in handCards, false otherwise
	void returnMinionCardToHand(const MinionCard& card); //returns a specific minion card to hand
	void returnLastMinionCardToHand(); //returns last played minion card to hand

	void addToRemovedCards(const MinionCard& card);
	bool placeMinionCardFromRemovedCard(uint16_t value); //returns true if card was found in removedCards, false otherwise

	//true if there are covered cards
	bool printCoveredCards(resizeableMatrix& matrix);
};

std::ostream& operator<<(std::ostream& os, const position& posTuple);

