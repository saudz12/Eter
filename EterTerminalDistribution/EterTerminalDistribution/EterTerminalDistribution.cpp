#include "ConsolePrints.h"
#include "functionsElementalCards.h"
#include "funcAssociationsToCard.h"

//Later add support for excat type
void checkCoveredCards(const coveredSet& coveredCardSet) {
    if (coveredCardSet.size() == 0) {
        std::cout << "You have no covered cards.\n";
        return;
    }
    std::cout << "Cards on position {x, y, pos_in_stack}:\n";
    for (auto& i : coveredCardSet) {
        std::cout << "{" << std::get<0>(i) << ", " << std::get<1>(i) << ": " << std::get<2>(i) << "}\n";
    }
}

void checkStack(const cardStack& stackToCheck) {
    std::cout << "Bottom: (";
    for (auto& i : stackToCheck) {
        std::cout << i << ", ";
    }
    std::cout << ")";
}

void checkElementalCardFunction(Board*& b, Player*& p1, Player*& p2, Player* currPlayer, hand& currHand, hand& removedCardsHand) {
    std::cout << "\nELEMENTAL CARDS:\n";
    std::cout << "1. Controlled Explosion\n2. Destruction\n3. Flame\n4. Fire\n5. Ash\n6. Spark\n7. Squall\n8. Gale\n";
    std::cout << "9. Hurricane\n10. Gust\n11. Mirage\n12. Storm\n13. Tide\n14. Mist\n15. Wave\n16. Whirlpool\n";
    std::cout << "17. Blizzard\n18. Waterfall\n19. Support\n20. Earthquake\n21. Crumble\n22. Border\n23. Avalanche\n24. Rock\n";
    std::cout << "25. Go back\n";
    uint16_t card;
    std::cin >> card;
    switch (card)
    {
    case 1: {
        funcControlledExplosion(*b, *p1, *p2);
        break;
    }
    case 2: {
        if (currPlayer->GetPlayerColor() == 'R')
            funcDestruction(*b, *p2);
        else
            funcDestruction(*b, *p1);
        break;
    }
    case 3: {
        uint16_t illusionX, illusionY, x, y, val;
        std::cout << "Type the coordonates of the illusion card you want to reveal\n";
        std::cin >> illusionX >> illusionY;

        currPlayer->printHandCards();
        uint16_t placeOption;
        std::cout << "Options:\n1. Place eter card\n2. Play a minion card as an illusion\n3. Play a minion card\n";
        std::cin >> placeOption;

        bool wasPlaced = false;

        switch (placeOption)
        {
        case 1:
        {
            if (currPlayer->GetEterCardUsage())
            {
                std::cout << "You have already used your eter card\n";
                break;
            }
            std::cout << "Choose the position: ";
            std::cin >> x >> y;
            MinionCard cardToPlace(1, currPlayer->GetPlayerColor(), true);

            if (currHand.find(cardToPlace) == currHand.end()) {
                std::cout << "\nYou don't own any cards of that type!\n";
                system("pause");
                break;
            }

            if (funcFlame(*b, illusionX, illusionY, x, y, cardToPlace, *currPlayer) == 1) {
                system("pause");
                break;
            }
            currPlayer->SetEterCardUsage(true);
            currPlayer->UpdateCard(cardToPlace, -1);
            wasPlaced = true;
            break;
        }
        case 2:
        {
            if (currPlayer->GetIllusionUsage())
            {
                std::cout << "You have already used your illusion\n";
                break;
            }
            std::cout << "\nChoose a card and the position: ";
            std::cin >> val >> x >> y;
            MinionCard cardToPlace(val, currPlayer->GetPlayerColor(), false);

            if (currHand.find(cardToPlace) == currHand.end()) {
                std::cout << "\nYou don't own any cards of that type!\n";
                system("pause");
                break;
            }

            cardToPlace.SetIsIllusionCard(true);

            if (funcFlame(*b, illusionX, illusionY, x, y, cardToPlace, *currPlayer) == 1) {
                system("pause");
                break;
            }

            cardToPlace.SetIsIllusionCard(false);
            currPlayer->UpdateCard(cardToPlace, -1);
            currPlayer->SetIllusionUsage(true);
            currPlayer->SetIllusionCard(&b->getCardOnPos(x, y));
            wasPlaced = true;
            break;
        }
        case 3:
        {
            std::cout << "\nChoose a card and the position: ";
            std::cin >> val >> x >> y;
            MinionCard cardToPlace(val, currPlayer->GetPlayerColor(), false);

            if (currHand.find(cardToPlace) == currHand.end()) {
                std::cout << "\nYou don't own any cards of that type!\n";
                system("pause");
                break;
            }

            if (funcFlame(*b, illusionX, illusionY, x, y, cardToPlace, *currPlayer) == 1) {
                system("pause");
                break;
            }
            currPlayer->UpdateCard(cardToPlace, -1);
            wasPlaced = true;
            break;
        }
        default:
            break;
        }

        if (wasPlaced)
        {
            currPlayer->SetLastMinionCardPlayed(&b->getCardOnPos(x, y));
            if (currPlayer->GetPlayerColor() == 'R')
                Player::updateCover(x, y, p2->getCovered(), b->getMatrix());
            else
                Player::updateCover(x, y, p1->getCovered(), b->getMatrix());

            std::cout << "Succesfull move!\n";
        }

        break;
    }
    case 4: {
        uint16_t value;
        std::cout << "Type a value for the card you want to return\n";
        std::cin >> value;
        funcFire(*b, *p1, *p2, value);
        break;
    }
    case 5: {
        std::cout << "Removed card:\n";
        for (auto& i : removedCardsHand)
        {
                std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
        }
        uint16_t x, y, val;
        std::cout << "Type which card you want place and the coordonates: ";
        std::cin >> val >> x >> y;

        MinionCard card(val, currPlayer->GetPlayerColor(), false);

        if (!currPlayer->placeMinionCardFromRemovedCard(card)) {
            std::cout << "\nYou don't own any cards of that type!\n";
            system("pause");
            break;
        }

        if (b->setPos(x, y, card, *currPlayer) == 1) {
            std::cout << "\nYou can't place that card there!\n";
            system("pause");
            break;
        }

        currPlayer->SetLastMinionCardPlayed(&b->getCardOnPos(x, y));
        if (currPlayer->GetPlayerColor() == 'R')
            Player::updateCover(x, y, p2->getCovered(), b->getMatrix());
        else
            Player::updateCover(x, y, p1->getCovered(), b->getMatrix());

        std::cout << "Succesfull move!\n";
        break;
    }
    case 6: {
        funcSpark(*b, *currPlayer);
        break;
    }
    case 7: {
        std::cout << "Type the coodonates of your opponent's card: ";
        uint16_t x, y;
        std::cin >> x >> y;
        if (currPlayer->GetPlayerColor() == 'R')
            funcSquall(*b, *p2, x, y);
        else
            funcSquall(*b, *p1, x, y);
        break;
    }
    case 8: {
        funcGale(*b, *p1, *p2);
        break;
    }
    }
}

int main() //for now we implement training mode here, later we will move it to a function
{
    Board *myBoard = new Board();
    Player *p1 = new Player('R');
    Player *p2 = new Player('B');
    score myScore(0, 0);

    int16_t x, y;
    uint16_t val;
    
    Player* currPlayer = nullptr;

    bool ok = true;
    bool wasPlaced = false;
    int rounds = 3;
    int options = 0;
    hand currHand;
    hand removedCardsHand;
    bool eterCardUsage;
    bool illusionUsage;

    bool elementalCardUsedTester = false;
    
    while (rounds) {
        //get current player data
        system("cls");
        myBoard->printBoard();
        wasPlaced = false;
        currPlayer = ok ? p1 : p2;
        playerTurn(ok);
        if (currPlayer->GetPlayerColor() == 'R')
        {
            currHand = p1->GetHandCards();
            removedCardsHand = p1->GetRemovedCards();
            eterCardUsage = p1->GetEterCardUsage();
            illusionUsage = p1->GetIllusionUsage();
        }
        else
        {
            currHand = p2->GetHandCards();
            removedCardsHand = p2->GetRemovedCards();
            eterCardUsage = p2->GetEterCardUsage();
            illusionUsage = p2->GetIllusionUsage();
        }

        ///menu
        std::cout << "\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Show Covered\n4. Check Stack\n";
        std::cout <<  "5. Use Elemental Power\n6. Test Isolated Spaces in Board\n7. Help\n8. Use explosion card\n9. Use Mage Card\n";
        std::cin >> options;
        switch (options)
        {
        case 1: {
            currPlayer->printHandCards();
            uint16_t placeOption;
            std::cout << "\nOptions:\n1. Place eter card\n2. Play a minion card as an illusion\n3. Play a minion card\n";
            std::cin >> placeOption;

            switch (placeOption)
            {
            case 1:
            {
                if (currPlayer->GetEterCardUsage())
                {
                    std::cout << "You have already used your eter card\n";
                    break;
                }
                std::cout << "Choose the position: ";
                std::cin >> x >> y;
                MinionCard cardToPlace(1, currPlayer->GetPlayerColor(), true);

                if (currHand.find(cardToPlace) == currHand.end()) {
                    std::cout << "\nYou don't own any cards of that type!\n";
                    system("pause");
                    break;
                }

                if (myBoard->setPos(x, y, cardToPlace, *currPlayer) == 1) {
                    std::cout << "\nYou can't place that card there!\n";
                    system("pause");
                    break;
                }
                currPlayer->SetEterCardUsage(true);
                currPlayer->UpdateCard(cardToPlace, -1);
                wasPlaced = true;
                break;
            }
            case 2:
            {
                if (currPlayer->GetIllusionUsage())
                {
                    std::cout << "You have already used your illusion\n";
                    break;
                }
                std::cout << "\nChoose a card and the position: ";
                std::cin >> val >> x >> y;
                MinionCard cardToPlace(val, currPlayer->GetPlayerColor(), false);

                if (currHand.find(cardToPlace) == currHand.end()) {
                    std::cout << "\nYou don't own any cards of that type!\n";
                    system("pause");
                    break;
                }

                cardToPlace.SetIsIllusionCard(true);

                if (myBoard->setPos(x, y, cardToPlace, *currPlayer) == 1) {
                    std::cout << "\nYou can't place that card there!\n";
                    system("pause");
                    break;
                }

                cardToPlace.SetIsIllusionCard(false);
                currPlayer->UpdateCard(cardToPlace, -1);
                currPlayer->SetIllusionUsage(true);
                currPlayer->SetIllusionCard(&myBoard->getCardOnPos(x, y));
                wasPlaced = true;
                break;
            }
            case 3:
            {
                std::cout << "\nChoose a card and the position: ";
                std::cin >> val >> x >> y;
                MinionCard cardToPlace(val, currPlayer->GetPlayerColor(), false);

                if (currHand.find(cardToPlace) == currHand.end()) {
                    std::cout << "\nYou don't own any cards of that type!\n";
                    system("pause");
                    break;
                }

                if (myBoard->setPos(x, y, cardToPlace, *currPlayer) == 1) {
                    std::cout << "\nYou can't place that card there!\n";
                    system("pause");
                    break;
                }
                currPlayer->UpdateCard(cardToPlace, -1);
                wasPlaced = true;
                break;
            }
            default:
                break;
            }

            if (wasPlaced)
            {
                currPlayer->SetLastMinionCardPlayed(&myBoard->getCardOnPos(x, y));
                if (currPlayer->GetPlayerColor() == 'R')
                    Player::updateCover(x, y, p2->getCovered(), myBoard->getMatrix());
                else
                    Player::updateCover(x, y, p1->getCovered(), myBoard->getMatrix());

                std::cout << "Succesfull move!\n";
            }
            system("pause");
            break;
        }
        case 2: {
            currPlayer->printHandCards();
            system("pause");
            break;
        }
        case 3: {
            checkCoveredCards(currPlayer->getCovered());
            break;
        }
        case 4: {
            std::cout << "Check stack on position: ";
            std::cin >> x >> y;
            if (x < 0 || x >= myBoard->getRowCount() || y < 0 || y >= myBoard->getColCount()) {
                std::cout << "\nThat is not a valid position!\n";
                system("pause");
                break;
            }
            checkStack(myBoard->getMatrix()[x][y]);
            system("pause");
            break;
        }
        case 5:
        {
            checkElementalCardFunction(myBoard, p1, p2, currPlayer, currHand, removedCardsHand);
            elementalCardUsedTester = true;
            wasPlaced = true;
            system("pause");
            break;
        }
        case 6: {
            TestIsolatedSpacesFunc(*myBoard);
            system("pause");
            break;
        }
        case 7: {
            helpOption();
            system("pause");
            break;
        }
        case 8:
            if (myBoard->getLineCount() == 2)
            {
                ExplosionCard explCard(myBoard->getMaxSize());
                
                std::cout << "0. Don't use the explosion\n1. Use the explosion\n2. Rotate the explosion\n";
                uint16_t explosionOption;
                bool getOut = false;
                std::cin >> explosionOption;
                do
                {
                    switch (explosionOption)
                    {
                    case 0:
                        getOut = true;
                        break;
                    case 1:
                    {
                        Board copyBoard;
                        Board::cloneMatrix(*myBoard, copyBoard);
                        Player copyPl1 = *p1;
                        Player copyPl2 = *p2;
                        myBoard->applyExplosionOnBoard(explCard, *p1, *p2);
                        if (isolatedSpaces(*myBoard))
                        {
                            Board::cloneMatrix(copyBoard, *myBoard);
                            *p1 = copyPl1;
                            *p2 = copyPl2;
                            std::cout << "Can't have isolated stacks/cards..\n";
                        }
                        else 
                            getOut = true;
                        break;
                    }
                    case 2:
                        explCard.RotateToRight(myBoard->getMaxSize());
                        explCard.showExpl(myBoard->getMaxSize());
                        std::cin >> explosionOption;
                        break;
                    default:
                        break;
                    }
                } while (getOut==false);
                
            }
            else
            {
                wasPlaced = false;
                std::cout << "you cannot place a explosion card right now\n";
            }
            system("pause");
            break;
        case 9:
            
            system("pause");
            break;
        default:
            break;
        }

        if (wasPlaced) {
            wasPlaced = false;
            //check win condition
            /*if (elementalCardUsedTester == true) { ///big error  - elemental cards need different check ;-;
                elementalCardUsedTester = false;
                continue;
            }*/
            if (myBoard->entityWon(x, y, currPlayer->GetPlayerColor())) {
                if (currPlayer->GetPlayerColor() == 'R')
                    myScore.first++;
                else
                    myScore.second++;
                rounds--;
                std::cout << "Player1: " << myScore.first << " | Player2: " << myScore.second << "\n";
                delete myBoard;
                delete p1;
                delete p2;
                if (rounds != 0) {
                    myBoard = new Board();
                    p1 = new Player('R');
                    p2 = new Player('B');
                }
                system("pause");
                continue;
            }
            ///Tiebreaker - update it
            if (myBoard->isBoardFilled() || currHand.empty()) {
                //The other player has one more move left!
                ok = !ok;
                currPlayer = ok ? p1 : p2;
                currHand = currPlayer->GetHandCards();

                system("cls");
                myBoard->printBoard();
                currPlayer = ok ? p1 : p2;
                playerTurn(ok);

                ///menu
                std::cin >> options;
                std::cout << "\n\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Skip\n4. Help\n";
                switch (options)
                {
                case 1: {
                    currPlayer->printHandCards();
                    uint16_t placeOption;
                    std::cout << "\nOptions:\n1. Place eter card\n2. Play a minion card as an illusion\n3. Play a minion card\n";
                    std::cin >> placeOption;

                    switch (placeOption)
                    {
                    case 1:
                    {
                        if (currPlayer->GetEterCardUsage())
                        {
                            std::cout << "You have already used your eter card\n";
                            break;
                        }
                        std::cout << "Choose the position: ";
                        std::cin >> x >> y;
                        MinionCard cardToPlace(1, currPlayer->GetPlayerColor(), true);

                        if (currHand.find(cardToPlace) == currHand.end()) {
                            std::cout << "\nYou don't own any cards of that type!\n";
                            system("pause");
                            break;
                        }

                        if (myBoard->setPos(x, y, cardToPlace, *currPlayer) == 1) {
                            std::cout << "\nYou can't place that card there!\n";
                            system("pause");
                            break;
                        }
                        currPlayer->SetEterCardUsage(true);
                        currPlayer->UpdateCard(cardToPlace, -1);
                        wasPlaced = true;
                        break;
                    }
                    case 2:
                    {
                        if (currPlayer->GetIllusionUsage())
                        {
                            std::cout << "You have already used your illusion\n";
                            break;
                        }
                        std::cout << "\nChoose a card and the position: ";
                        std::cin >> val >> x >> y;
                        MinionCard cardToPlace(val, currPlayer->GetPlayerColor(), false);

                        if (currHand.find(cardToPlace) == currHand.end()) {
                            std::cout << "\nYou don't own any cards of that type!\n";
                            system("pause");
                            break;
                        }

                        cardToPlace.SetIsIllusionCard(true);

                        if (myBoard->setPos(x, y, cardToPlace, *currPlayer) == 1) {
                            std::cout << "\nYou can't place that card there!\n";
                            system("pause");
                            break;
                        }

                        cardToPlace.SetIsIllusionCard(false);
                        currPlayer->UpdateCard(cardToPlace, -1);
                        currPlayer->SetIllusionUsage(true);
                        currPlayer->SetIllusionCard(&myBoard->getCardOnPos(x, y));
                        wasPlaced = true;
                        break;
                    }
                    case 3:
                    {
                        std::cout << "\nChoose a card and the position: ";
                        std::cin >> val >> x >> y;
                        MinionCard cardToPlace(val, currPlayer->GetPlayerColor(), false);

                        if (currHand.find(cardToPlace) == currHand.end()) {
                            std::cout << "\nYou don't own any cards of that type!\n";
                            system("pause");
                            break;
                        }

                        if (myBoard->setPos(x, y, cardToPlace, *currPlayer) == 1) {
                            std::cout << "\nYou can't place that card there!\n";
                            system("pause");
                            break;
                        }
                        currPlayer->UpdateCard(cardToPlace, -1);
                        wasPlaced = true;
                        break;
                    }
                    default:
                        break;
                    }

                    if (wasPlaced)
                    {
                        currPlayer->SetLastMinionCardPlayed(&myBoard->getCardOnPos(x, y));
                        if (currPlayer->GetPlayerColor() == 'R')
                            Player::updateCover(x, y, p2->getCovered(), myBoard->getMatrix());
                        else
                            Player::updateCover(x, y, p1->getCovered(), myBoard->getMatrix());

                        std::cout << "Succesfull move!\n";
                    }
                    system("pause");
                    break;
                }
                case 2: {
                    currPlayer->printHandCards();
                    system("pause");
                    break;
                }
                case 3: {
                    helpOption();
                    system("pause");
                    break;
                }
                case 4: {
                    break;
                }
                default:
                    break;
                }
                if (myBoard->entityWon(x, y, currPlayer->GetPlayerColor())) {
                    if (currPlayer->GetPlayerColor() == 'R')
                        myScore.first++;
                    else
                        myScore.second++;
                    rounds--;
                    std::cout << "Player1: " << myScore.first << " | Player2: " << myScore.second << "\n";
                    delete myBoard;
                    delete p1;
                    delete p2;
                    if (rounds != 0) {
                        myBoard = new Board();
                        p1 = new Player('R');
                        p2 = new Player('B');
                    }
                    system("pause");
                }
            }
            ok = !ok;
            currPlayer = ok ? p1 : p2;
        }
    }

    if (myScore.first > myScore.second)
        std::cout << "\nPlayer 1 WON IT ALL!";
    else if(myScore.first < myScore.second)
        std::cout << "\nPlayer 2 WON IT ALL!";
    else
        std::cout << "\nTie!";

    //for testing board class 
    //std::cin >> x >> y >> val; 
    //while (x < 5 && y < 5) {
    //    system("cls");
    //    MinionCard m(uint16_t(val), ok ? 'R' : 'B');
    //    if (b.setPos(uint16_t(x), uint16_t(y), uint16_t(val), ok?'R':'B')) {
    //        std::cout << "Invalid Move!\n\n";
    //    }
    //    else
    //        ok = !ok;
    //    b.printBoard();
    //    //system("pause");
    //    std::cin >> x >> y >> val;
    //}

}


