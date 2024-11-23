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
	//true if illusion has been used, false otherwise
	bool m_illusionUsage; 
	//true if eter card has been used, false otherwise
	bool m_eterCardUsage;
	//pointer towards the last card played
	MinionCard* m_lastMinionCardPlayed;
	//pointer towards the illusion card
	MinionCard* m_illusionCard;

	void generateTrainingModeHand(); //hand for training mode
	void generateHand(); //hand for other modes;
public:
	//constructor
	Player(char playerColor);
	~Player() = default;

	//getters
	char GetPlayerColor() const;
	bool GetIllusionUsage() const;
	bool GetEterCardUsage() const;
	const hand& GetHandCards() const;
	hand& GetHandCards();
	const hand& GetRemovedCards() const;
	MinionCard* GetLastMinionCardPlayed() const;
	MinionCard* GetIllusionCard() const;
	coveredSet& getCovered();

	//setters
	void SetEterCardUsage(bool eterCardUsage);
	void SetPlayerColor(char playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const hand& handCards);

	//Updates
	int UpdateCard(const MinionCard& card, int cnt);
	//primeste coveredul la celelalt player
	static void updateCover(uint16_t x, uint16_t y, coveredSet& coveredCards, resizeableMatrix& board);
	//T(a, b) + T(c, d) = T(a + c, b + d) <-- aplicam asemenea transofmrari pe un coveredSet cand miscam un stack de marime > 1 -- cam consuming dar tabla e pera mica ca sa se simta
	static void applyTansformToCovered(Player& p1, Player& p2, cardStack& stack, uint16_t oldX, uint16_t oldY, uint16_t newX, uint16_t newY);
	static void returnStackToHand(hand& h1, hand& h2, cardStack& stack);

	void SetIllusionCard(MinionCard* illusionCard);
	void SetLastMinionCardPlayed(MinionCard* cardPlayed);
	//returns true if card was found in handCards, false otherwise
	bool placeMinionCardFromHand(MinionCard& card);
	//returns a specific minion card to hand
	void returnMinionCardToHand(const MinionCard& card);
	//returns last played minion card to hand
	void returnLastMinionCardToHand();

	void addToRemovedCards(const MinionCard& card);
	//returns true if card was found in removedCards, false otherwise
	bool placeMinionCardFromRemovedCard(const MinionCard& card);

	//true if there are covered cards
	bool printCoveredCards(resizeableMatrix& matrix);

	void printHandCards();
	
	Player& operator=(const Player& p);
};

std::ostream& operator<<(std::ostream& os, const position& posTuple);

