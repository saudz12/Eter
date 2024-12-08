#pragma once
#include "Board.h"
#include "Player.h"
#include "MoveLaterToGameClass.h"
#include "InputChecking.h"
#include "ConsoleView.h"
#include "ErrorPrints.h"
#include "functionsElementalCards.h"

class GameDemo
{
private:
    Board* m_board;
    Player* m_p1, * m_p2;
    Player* m_currPlayer;
    Hand m_currHand;
    Hand m_removedCardsHand;
    Score m_score;
    //char m_currPlayerColor;
    Colours m_currPlayerColor;
    uint16_t m_rounds;
    bool m_wasPlaced;
    bool m_wasElementalCardUsed;
    bool m_eterCardUsage;
    bool m_illusionUsage;
public:
    GameDemo(uint16_t size,uint16_t numberOfRounds);
    void runDemo();

    void showPlayerTurn(Colours color);
    void setStructuresForPlayer(Player*& player);
    bool placeEterCard(int16_t&, int16_t&);
    bool placeIllusionCard(int16_t&, int16_t&);
    bool placeMinionCard(int16_t&, int16_t&);
    bool useExplosionCard();

    void restartRound();

    void checkCoveredCards(const CoveredSet& coveredCardSet);
    void checkStack(const CardStack& stackToCheck);
    void checkElementalCardFunction(Board& b, Player*& p1, Player*& p2, Player* currPlayer, Hand& currHand, Hand& removedCardsHand, bool& wasUsed, bool& wasCardUsed);

    void advanceTurn();
};

