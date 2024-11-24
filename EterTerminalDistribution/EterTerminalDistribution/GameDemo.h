#pragma once
#include "Board.h"
#include "Player.h"

class GameDemo
{
private:
    Board* m_board;
    Player* m_p1, * m_p2;
    Player* m_currPlayer;
    char m_currPlayerColor;
    bool m_wasPlaced;
    bool m_wasElementalCardUsed;
    uint16_t m_rounds;
    hand m_currHand;
    hand m_removedCardsHand;
    bool m_eterCardUsage;
    bool m_illusionUsage;
    score m_score;
public:
    GameDemo(uint16_t size,uint16_t numberOfRounds);
    void runDemo();

    void playerTurn(char color);
    void setStructuresForPlayer(Player*& player);
    bool placeEterCard(size_t&,size_t&);
    bool placeIllusionCard(size_t&, size_t&);
    bool placeMinionCard(size_t&, size_t&);

    void checkCoveredCards(const coveredSet& coveredCardSet);
    void checkStack(const cardStack& stackToCheck);
    void checkElementalCardFunction(Board*& b, Player*& p1, Player*& p2, Player* currPlayer, hand& currHand, hand& removedCardsHand, bool& wasUsed, bool& wasCardUsed);

};

