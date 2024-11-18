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

void checkElementalCardFunction(Board*& b, Player*& p1, Player*& p2, char curr_col, hand& currHand, hand& removedCardsHand) {
    uint16_t x, y, val;
    std::cout << "\nELEMENTAL CARDS:\n1. Fire\n2. Ash\n3. Waterfall\n4. Avalanche\n5. Squall\n6. Hurricane\n7. Tide\n8. Cancel elemental card\n";
    int card;
    std::cin >> card;
    switch (card)
    {
    case 1:
    {
        std::cout << "\nChoose a value\n";
        int value;
        std::cin >> value;
        funcFire((*b), (*p1), (*p2), value);
        break;
    }
    case 2:
    {
        if (removedCardsHand.empty())
        {
            std::cout << "\nYou have no removed cards\n";
            break;
        }
        std::cout << "\nYour Removed Cards:\n";
        for (auto& i : removedCardsHand) {
            std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
        }
        std::cout << "\nWhich card and where: ";
        std::cin >> val >> x >> y;
        if (curr_col == 'R')
            funcAsh((*b), (*p1), val, x, y);
        else
            funcAsh((*b), (*p2), val, x, y);
        break;
    }
    case 3:
    {
        std::cout << "\nChoose a column\n";
        int columnIndex;
        std::cin >> columnIndex;
        funcWaterfall((*b), columnIndex);
        break;
    }
    case 4: {
        
        /*if (curr_col == 'R')
            funcSquall(*b, *p2);
        else
            funcSquall(*b, *p1);
        break;*/

    }
    case 5: {
        uint16_t x, y;
        //std::function<void(Board&, Player&, uint16_t, uint16_t)> myFunc(funcSquall);
        std::cout << "\nWhich(by {x, y}):";
        std::cin >> x >> y;
        if (curr_col == 'R') {
            funcSquall(*b, *p2, x, y);
        }
        else {
            funcSquall(*b, *p1, x, y);
        }
    }
    case 6: {
        funcHurricane(*b, p1->GetHandCards(), p2->GetHandCards());
        break;
    }
    case 7: {
        uint16_t x1, x2, y1, y2;
        std::cout << "Exchange stack on pos(x, y): ";
        std::cin >> x1 >> y1;
        std::cout << "\nwith: ";
        std::cin >> x2 >> y2;
        funcTide(*b, x1, y1, x2, y2);
    }
    case 8: {
        return;
    }
    default: {
        break;
    }
    }
    system("pause");
}

int main() //for now we implement training mode here, later we will move it to a function
{
    Board *myBoard = new Board();
    Player *p1 = new Player('R');
    Player *p2 = new Player('B');
    score myScore(0, 0);

    int16_t x, y;
    uint16_t val;
    
    bool ok = true;
    char curr_col = 'R';
    bool wasPlaced = false;
    int rounds = 3;
    int options = 0;
    hand currHand;
    hand removedCardsHand;

    bool elementalCardUsedTester = false;
    
    while (rounds) {
        //get current player data
        system("cls");
        myBoard->printBoard();
        wasPlaced = false;
        curr_col = ok?'R':'B';
        playerTurn(ok);
        if (curr_col == 'R')
        {
            currHand = p1->GetHandCards();
            removedCardsHand = p1->GetRemovedCards();
            MinionCard card(1, 'R');
            p1->addToRemovedCards(card);
        }
        else
        {
            currHand = p2->GetHandCards();
            removedCardsHand = p2->GetRemovedCards();

        }

        ///menu
        std::cout << "\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Show Covered\n4. Check Stack\n5. Use Elemental Power\n6. Test Isolated Spaces in Board\n7. Help\n8. Use explosion card\n9. Use Mage Card\n";
        std::cin >> options;
        switch (options)
        {
        case 1: {
            std::cout << "\nYour Hand:\n";
            for (auto& i : currHand) {
                std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
            }
            std::cout << "\nWhich card and where: ";
            std::cin >> val >> x >> y;

            //check if card in hand. reduce and remove only if can place.
            MinionCard toSearch(val, curr_col);
            if (currHand.find(toSearch) == currHand.end()) {
                std::cout << "\nYou don't own any cards of that type!\n";
                system("pause");
                break;
            }
            if (myBoard->setPos(x, y, val, curr_col) == 1) {
                std::cout << "\nYou can't place that card there!\n";
                system("pause");
                break;
            }
            if (curr_col == 'R') {
                p1->UpdateCard(val, -1);
                Player::updateCover(x, y, p2->getCovered(), myBoard->getMatrix());
            }
            else {
                p2->UpdateCard(val, -1);
                Player::updateCover(x, y, p1->getCovered(), myBoard->getMatrix());
            }

            wasPlaced = true;
            
            std::cout << "Succesfull move!\n";
            system("pause");
            break;
        }
        case 2: {
            std::cout << "\nYour Hand:\n";
            for (auto& i : currHand) {
                std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << " Left\n";
            }
            system("pause");
            break;
        }
        case 3: {
            if (curr_col == 'R')
                checkCoveredCards(p1->getCovered());
            else
                checkCoveredCards(p2->getCovered());
            system("pause");
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
            checkElementalCardFunction(myBoard, p1, p2, curr_col, currHand, removedCardsHand);
            elementalCardUsedTester = true;
            wasPlaced = true;
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
                        myBoard->applyExplosionOnBoard(explCard, *p1, *p2);
                        getOut = true;
                        break;
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
            if (curr_col == 'R')
                funcWaterMage2(*myBoard, 'B', *p2);
            else
                funcWaterMage2(*myBoard, 'R', *p1);
            system("pause");
            break;
        default:
            break;
        }
        if (wasPlaced) {
            wasPlaced = false;
            //check win condition
            if (elementalCardUsedTester == true) { ///big error  - elemental cards need different check ;-;
                elementalCardUsedTester = false;
                continue;
            }
            if (myBoard->entityWon(x, y, curr_col)) {
                if (curr_col == 'R')
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
            ///Tiebreaker - uodate it
            if (myBoard->isBoardFilled() || currHand.empty()) {
                //The other player has one more move left!
                ok = !ok;
                curr_col = ok ? 'R' : 'B';
                if (curr_col == 'R')
                    currHand = p1->GetHandCards();
                else
                    currHand = p2->GetHandCards();

                system("cls");
                myBoard->printBoard();
                curr_col = ok ? 'R' : 'B';
                playerTurn(ok);

                ///menu
                std::cin >> options;
                std::cout << "\n\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Skip\n4. Help\n";
                switch (options)
                {
                case 1: {
                    std::cout << "\nYour Hand:\n";
                    for (auto& i : currHand) {
                        std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
                    }
                    std::cout << "\nWhich card and where: ";
                    std::cin >> val >> x >> y;

                    //check if card in hand. reduce and remove only if can place.
                    MinionCard toSearch(val, curr_col);
                    if (currHand.find(toSearch) == currHand.end()) {
                        std::cout << "\nYou don't own any cards of that type!\n";
                        system("pause");
                        break;
                    }
                    if (myBoard->setPos(x, y, val, curr_col) == 1) {
                        std::cout << "\nYou can't place that card there!\n";
                        system("pause");
                        break;
                    }
                    if (curr_col == 'R') {
                        p1->UpdateCard(val, -1);
                    }
                    else {
                        p2->UpdateCard(val, -1);
                    }

                    std::cout << "Succesfull move!\n";
                    system("pause");
                    break;
                }
                case 2: {
                    std::cout << "\nYour Hand:\n";
                    for (auto& i : currHand) {
                        std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << "Left\n";
                    }
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
                if (myBoard->entityWon(x, y, curr_col)) {
                    if (curr_col == 'R')
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
            curr_col = ok ? 'R' : 'B';
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


