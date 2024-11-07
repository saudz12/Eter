#include "Player.h"
#include "Board.h"
#include "ConsolePrints.h"

int main() //for now we implement training mode here, later we will move it to a function
{
    Board *b = new Board();
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
    
    while (rounds) {
        //get current player data
        system("cls");
        b->printBoard();
        wasPlaced = false;
        curr_col = ok?'R':'B';
        playerTurn(ok);
        if (curr_col == 'R')
            currHand = p1->GetHandCards();
        else
            currHand = p2->GetHandCards();

        ///menu
        std::cout << "\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Help\n";
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
            if (b->setPos(x, y, val, curr_col) == 1) {
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

            wasPlaced = 1;
            
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
            helpOption();
            system("pause");
            break;
        }
        default:
            break;
        }
        if (wasPlaced) {
            wasPlaced = false;
            //check win condition
            if (b->entityWon(x, y, curr_col)) {
                if (curr_col == 'R')
                    myScore.first++;
                else
                    myScore.second++;
                rounds--;
                std::cout << "Player1: " << myScore.first << " | Player2: " << myScore.second << "\n";
                delete b;
                delete p1;
                delete p2;
                if (rounds != 0) {
                    b = new Board();
                    p1 = new Player('R');
                    p2 = new Player('B');
                }
                system("pause");
                continue;
            }
            ///Tiebreaker
            if (b->isBoardFilled() || currHand.empty()) {
                //The other player has one more move left!
                ok = !ok;
                curr_col = ok ? 'R' : 'B';
                if (curr_col == 'R')
                    currHand = p1->GetHandCards();
                else
                    currHand = p2->GetHandCards();

                system("cls");
                b->printBoard();
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
                    if (b->setPos(x, y, val, curr_col) == 1) {
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
                if (b->entityWon(x, y, curr_col)) {
                    if (curr_col == 'R')
                        myScore.first++;
                    else
                        myScore.second++;
                    rounds--;
                    std::cout << "Player1: " << myScore.first << " | Player2: " << myScore.second << "\n";
                    delete b;
                    delete p1;
                    delete p2;
                    if (rounds != 0) {
                        b = new Board();
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
