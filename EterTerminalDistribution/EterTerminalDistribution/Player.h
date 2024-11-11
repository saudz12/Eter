#pragma once
#include "MinionCard.h"
#include <unordered_set>

using hand = std::unordered_map<MinionCard, uint16_t>;
//using coords = std::pair<uint16_t, uint16_t>;
using position = std::tuple< uint16_t, uint16_t, uint16_t>;
using covered = std::unordered_set<position, hashPosition>;

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
	covered m_coveredCardSet;
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
	const hand& GetRemovedCards() const;
	MinionCard* GetLastMinionCardPlayed() const;
	covered& getCovered();

	//setters
	void SetPlayerColor(char playerColor);
	void SetIllusionUsage(bool illusionUsage);
	void SetHandCards(const hand& handCards);

	//Updates
	int UpdateCard(int value, int cnt);
	//primeste coveredul la celelalt player
	void updateCover(uint16_t x, uint16_t y, covered& coveredCards, resizeableMatrix& board);

	void SetLastMinionCardPlayed(MinionCard* cardPlayed);
	bool placeMinionCardFromHand(MinionCard& card); //returns true if card was found in handCards, false otherwise
	void returnMinionCardToHand(const MinionCard& card); //returns a specific minion card to hand
	void returnLastMinionCardToHand(); //returns last played minion card to hand

	void addToRemovedCards(const MinionCard& card);
	bool placeMinionCardFromRemovedCard(const MinionCard& card); //returns true if card was found in removedCards, false otherwise
};

//namespace std
//{
//	template<>
//	struct hash <position>
//	{
//		size_t operator()(const position& t) const {
//			int x = std::get<0>(t);
//			int y = std::get<1>(t);
//			int pos = std::get<2>(t);
//
//			//gpt :)
//			/*size_t hash_value = std::hash<int>()(row);
//			hash_value ^= std::hash<int>()(col) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
//			hash_value ^= std::hash<int>()(level) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
//
//			return hash_value;*/
//
//			return std::hash<int>()(x) ^ std::hash<int>()(y) ^ std::hash<int>()(pos);
//		}
//	};
//}
