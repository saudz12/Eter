#pragma once
#include "Board.h"
#include "Player.h"
#include "MoveLaterToGameClass.h"
#include "InputChecking.h"
#include "ConsolePrints.h"
#include "ErrorPrints.h"
#include "functionsElementalCards.h"

class GameDemo
{
private:
    Board* m_board;
    Player* m_p1, * m_p2;
    Player* m_currPlayer;
    hand m_currHand;
    hand m_removedCardsHand;
    score m_score;
    char m_currPlayerColor;
    uint16_t m_rounds;
    bool m_wasPlaced;
    bool m_wasElementalCardUsed;
    bool m_eterCardUsage;
    bool m_illusionUsage;
public:
    GameDemo(uint16_t size,uint16_t numberOfRounds);
    void runDemo();

    void playerTurn(char color);
    void setStructuresForPlayer(Player*& player);
    bool placeEterCard(size_t&,size_t&);
    bool placeIllusionCard(size_t&, size_t&);
    bool placeMinionCard(size_t&, size_t&);
    bool useExplosionCard();

    void restartRound();

    void checkCoveredCards(const coveredSet& coveredCardSet);
    void checkStack(const CardStack& stackToCheck);
    void checkElementalCardFunction(Board& b, Player*& p1, Player*& p2, Player* currPlayer, hand& currHand, hand& removedCardsHand, bool& wasUsed, bool& wasCardUsed);

};

