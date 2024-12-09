#pragma once
#include "MinionCard.h"

using Hand = std::unordered_map<MinionCard, uint16_t>;

using CardCounter = std::unordered_map<int16_t, int16_t>; //new
using CardList = std::vector<std::vector<MinionCard>>; //new

//using coords = std::pair<uint16_t, uint16_t>;
using CoveredSet = std::unordered_set<position, hashPosition>;

//moved from board. when implementing game, move updateCover functiouns to it
//REMOVE RESIZABLE MATRIX DEPENDENCIES FROM PLAYER
using CardStack = std::deque<MinionCard>;
using Line = std::deque<CardStack>;
using ResizeableMatrix = std::deque<Line>;
using Score = std::pair <uint16_t, uint16_t>; //<R/B>
using LineChecker = std::deque<Score>;

class Player
{
private:
	Hand m_handCards;
	
	CardCounter m_remainingCounter; //new
	CardList m_remainingCards; //new

	CoveredSet m_coveredCardSet; //change to pointers and positions?

	Colours m_playerColor;
	Hand m_removedCards;

	bool m_illusionUsage; 

	bool m_eterCardUsage;

	MinionCard* m_lastMinionCardPlayed;

	MinionCard* m_illusionCard;

	void generateTrainingModeHand(); 
	void generateHand(); 
	void GenerateHand(bool training); //new
public:
	//constructor
	Player(Colours playerColor);
	Player(Colours _playerColor, bool _training); //new
	Player();

	//getters
	Colours GetPlayerColor() const;
	bool GetIllusionUsage() const;
	bool GetEterCardUsage() const;
	const Hand& GetHandCards() const;
	Hand& GetHandCards();
	Hand& GetRemovedCards();
	MinionCard* GetLastMinionCardPlayed() const;
	MinionCard* GetIllusionCard() const;
	CoveredSet& getCovered();

	bool CheckCoveredPopulation(); //new
	bool CheckCoveredProperty(int16_t _x, int16_t _y, int16_t _pos); //new
	MinionCard&& MoveCard(int16_t _val); //new

	bool HasCardOfValue(uint16_t value);

	//setters
	void SetEterCardUsage(bool eterCardUsage);
	void SetPlayerColor(Colours playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const Hand& handCards);

	//Updates
	int UpdateCard(const MinionCard& card, int cnt);

	//primeste coveredul la celelalt player
	static void updateCover(uint16_t x, uint16_t y, CoveredSet& coveredCards, ResizeableMatrix& board);

	//T(a, b) + T(c, d) = T(a + c, b + d) <-- aplicam asemenea transofmrari pe un coveredSet cand miscam un stack de marime > 1 
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

