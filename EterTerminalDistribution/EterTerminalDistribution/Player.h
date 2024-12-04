#pragma once
#include "MinionCard.h"

using Hand = std::unordered_map<MinionCard, uint16_t>;
//using coords = std::pair<uint16_t, uint16_t>;
using CoveredSet = std::unordered_set<position, hashPosition>;

//moved from board. when implementing game, move updateCover functiouns to it
using CardStack = std::deque<MinionCard>;
using Line = std::deque<CardStack>;
using ResizeableMatrix = std::deque<Line>;
using Score = std::pair <uint16_t, uint16_t>; //<R/B>
using LineChecker = std::deque<Score>;

class Player
{
private:
	Hand m_handCards;
	CoveredSet m_coveredCardSet;
	//char m_playerColor;
	Colours m_playerColor;
	Hand m_removedCards;
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
	Player(Colours playerColor);
	Player();
	~Player() = default;

	//getters
	//char GetPlayerColor() const;
	Colours GetPlayerColor() const;
	bool GetIllusionUsage() const;
	bool GetEterCardUsage() const;
	const Hand& GetHandCards() const;
	Hand& GetHandCards();
	Hand& GetRemovedCards();
	MinionCard* GetLastMinionCardPlayed() const;
	MinionCard* GetIllusionCard() const;
	CoveredSet& getCovered();

	//setters
	void SetEterCardUsage(bool eterCardUsage);
	//void SetPlayerColor(char playerColor);
	void SetPlayerColor(Colours playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const Hand& handCards);

	//Updates
	int UpdateCard(const MinionCard& card, int cnt);
	//primeste coveredul la celelalt player
	static void updateCover(uint16_t x, uint16_t y, CoveredSet& coveredCards, ResizeableMatrix& board);
	//T(a, b) + T(c, d) = T(a + c, b + d) <-- aplicam asemenea transofmrari pe un coveredSet cand miscam un stack de marime > 1 -- cam consuming dar tabla e pera mica ca sa se simta
	static void applyTansformToCovered(Player& p1, Player& p2, CardStack& stack, uint16_t oldX, uint16_t oldY, uint16_t newX, uint16_t newY);
	static void returnStackToHand(Hand& h1, Hand& h2, CardStack& stack);

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
	bool printCoveredCards(ResizeableMatrix& matrix);

	void printHandCards();
};

std::ostream& operator<<(std::ostream& os, const position& posTuple);

