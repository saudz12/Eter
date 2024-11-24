#include "GameDemo.h"

GameDemo::GameDemo(uint16_t size,uint16_t numberOfRounds)
{
    m_board = new Board(size);
    m_p1 = new Player('R');
    m_p2 = new Player('B');
    m_currPlayer = nullptr;
    m_currPlayerColor = 'R';
    m_wasPlaced = false;
    m_wasElementalCardUsed = false;
    m_rounds = numberOfRounds;
    m_score = { 0,0 };
}

void GameDemo::runDemo()
{
    bool elementalCardUsedTester = false;
    while (m_rounds) {
        //get current player data
        system("cls");
        m_board->printBoard();
        m_wasPlaced = false;
        m_currPlayer = m_currPlayerColor=='R' ? m_p1 : m_p2;
        playerTurn(m_currPlayerColor);
        if (m_currPlayer->GetPlayerColor() == 'R')
            setStructuresForPlayer(m_p1);
        else
            setStructuresForPlayer(m_p2);
        ///menu
        printMenu();
        uint16_t options;
        std::cin >> options;
        size_t x, y;
        switch (options)
        {
        case 1: {
            m_currPlayer->printHandCards();
            uint16_t placeOption;
            printOptionsForCards();
            std::cin >> placeOption;
            
            switch (placeOption)
            {
            case 1:
            {
                m_wasPlaced = placeEterCard(x,y);
                break;
            }
            case 2:
            {
                m_wasPlaced = placeIllusionCard(x,y);
                break;
            }
            case 3:
            {
                m_wasPlaced = placeMinionCard(x,y);
                break;
            }
            default:
                break;
            }

            if (m_wasPlaced)
            {
                m_currPlayer->SetLastMinionCardPlayed(&m_board->getCardOnPos(x, y));
                if (m_currPlayer->GetPlayerColor() == 'R')
                    Player::updateCover(x, y, m_p2->getCovered(), m_board->getMatrix());
                else
                    Player::updateCover(x, y, m_p1->getCovered(), m_board->getMatrix());

                std::cout << "Succesfull move!\n";
            }
            system("pause");
            break;
        }
        case 2: {
            m_currPlayer->printHandCards();
            system("pause");
            break;
        }
        case 3: {
            checkCoveredCards(m_currPlayer->getCovered());
            system("pause");
            break;
        }
        case 4: {
            size_t x, y;
            std::cout << "Check stack on position: ";
            std::cin >> x >> y;
            if (x < 0 || x >= m_board->getRowCount() || y < 0 || y >= m_board->getColCount())
            {
                std::cout << "\nThat is not a valid position!\n";
                system("pause");
                break;
            }
            checkStack(m_board->getMatrix()[x][y]);
            system("pause");
            break;
        }
        case 5:
        {
            checkElementalCardFunction(*m_board, m_p1, m_p2, m_currPlayer, m_currHand, m_removedCardsHand, m_wasPlaced, m_wasElementalCardUsed);
            system("pause");
            break;
        }
        case 6: {
            TestIsolatedSpacesFunc(*m_board);
            system("pause");
            break;
        }
        case 7: {
            helpOption();
            system("pause");
            break;
        }
        case 8:
            m_wasPlaced = useExplosionCard();
            system("pause");
            break;
        case 9:

            system("pause");
            break;
        default:
            break;
        }

        if (m_wasPlaced) {
            m_wasPlaced = false;
            //check win condition
            /*if (elementalCardUsedTester == true) { ///big error  - elemental cards need different check ;-;
                elementalCardUsedTester = false;
                continue;
            }*/
            if (m_board->entityWon(x, y, m_currPlayer->GetPlayerColor())) {
                restartRound();
                system("pause");
                continue;
            }
            ///Tiebreaker - update it
            if (m_board->isBoardFilled() || m_currHand.empty()) {
                //The other player has one more move left!
                if (m_currPlayerColor == 'R')
                    m_currPlayerColor = 'B';
                else
                    m_currPlayerColor = 'R';
                m_currPlayer = m_currPlayerColor=='R' ? m_p1 : m_p2;
                m_currHand = m_currPlayer->GetHandCards();

                system("cls");
                m_board->printBoard();
                playerTurn(m_currPlayerColor);

                ///menu
                printMenu();
                std::cin >> options;
                switch (options)
                {
                case 1: {
                    m_currPlayer->printHandCards();
                    uint16_t placeOption;
                    printOptionsForCards();
                    std::cin >> placeOption;

                    switch (placeOption)
                    {
                    case 1:
                    {
                        m_wasPlaced = placeEterCard(x, y);
                        break;
                    }
                    case 2:
                    {
                        m_wasPlaced = placeIllusionCard(x, y);
                        break;
                    }
                    case 3:
                    {
                        m_wasPlaced = placeMinionCard(x, y);
                        break;
                    }
                    default:
                        break;
                    }

                    if (m_wasPlaced)
                    {
                        m_currPlayer->SetLastMinionCardPlayed(&m_board->getCardOnPos(x, y));
                        if (m_currPlayer->GetPlayerColor() == 'R')
                            Player::updateCover(x, y, m_p2->getCovered(), m_board->getMatrix());
                        else
                            Player::updateCover(x, y, m_p1->getCovered(), m_board->getMatrix());

                        std::cout << "Succesfull move!\n";
                    }
                    system("pause");
                    break;
                }
                case 2: {
                    m_currPlayer->printHandCards();
                    system("pause");
                    break;
                }
                case 3: {
                    checkCoveredCards(m_currPlayer->getCovered());
                    system("pause");
                    break;
                }
                case 4: {
                    size_t x, y;
                    std::cout << "Check stack on position: ";
                    std::cin >> x >> y;
                    if (x < 0 || x >= m_board->getRowCount() || y < 0 || y >= m_board->getColCount())
                    {
                        std::cout << "\nThat is not a valid position!\n";
                        system("pause");
                        break;
                    }
                    checkStack(m_board->getMatrix()[x][y]);
                    system("pause");
                    break;
                }
                case 5:
                {
                    checkElementalCardFunction(*m_board, m_p1, m_p2, m_currPlayer, m_currHand, m_removedCardsHand, m_wasPlaced, m_wasElementalCardUsed);
                    system("pause");
                    break;
                }
                case 6: {
                    TestIsolatedSpacesFunc(*m_board);
                    system("pause");
                    break;
                }
                case 7: {
                    helpOption();
                    system("pause");
                    break;
                }
                case 8:
                    m_wasPlaced = useExplosionCard();
                    system("pause");
                    break;
                case 9:

                    system("pause");
                    break;
                default:
                    break;
                }

                if (m_board->entityWon(x, y, m_currPlayer->GetPlayerColor())) {
                    if (m_currPlayer->GetPlayerColor() == 'R')
                        m_score.first++;
                    else
                        m_score.second++;
                    m_rounds--;
                    std::cout << "Player1: " << m_score.first << " | Player2: " << m_score.second << "\n";
                    delete m_board;
                    delete m_p1;
                    delete m_p2;
                    if (m_rounds != 0) {
                        m_board = new Board(3);
                        m_p1 = new Player('R');
                        m_p2 = new Player('B');
                    }
                    system("pause");
                }
            }
            if (m_currPlayerColor == 'R')
                m_currPlayerColor = 'B';
            else
                m_currPlayerColor = 'R';
            m_currPlayer = m_currPlayerColor == 'R' ? m_p1 : m_p2;
        }
    }
}

void GameDemo::playerTurn(char color)
{
    if (color=='R')
        std::cout << "Player 1(Red's) Turn\n";
    else
        std::cout << "Player 2(Blue's) Turn:\n";
}

void GameDemo::setStructuresForPlayer(Player*& player)
{
    m_currHand = player->GetHandCards();
    m_removedCardsHand = player->GetRemovedCards();
    m_eterCardUsage = player->GetEterCardUsage();
    m_illusionUsage = player->GetIllusionUsage();
}

bool GameDemo::placeEterCard(size_t& x, size_t& y)
{
    if (m_currPlayer->GetEterCardUsage())
    {
        std::cout << "You have already used your eter card\n";
        return false;
    }
    uint16_t value;
    std::cout << "Choose the position: ";
    std::cin >> x >> y;
    MinionCard cardToPlace(1, m_currPlayer->GetPlayerColor(), true);

    if (m_currHand.find(cardToPlace) == m_currHand.end()) {
        std::cout << "\nYou don't own any cards of that type!\n";
        system("pause");
        return false;
    }

    if (m_board->setPos(x, y, cardToPlace, *m_currPlayer) == 1) {
        std::cout << "\nYou can't place that card there!\n";
        system("pause");
        return false;
    }
    m_currPlayer->SetEterCardUsage(true);
    m_currPlayer->UpdateCard(cardToPlace, -1);
    return true;
}

bool GameDemo::placeIllusionCard(size_t& x, size_t& y)
{
    if (m_currPlayer->GetIllusionUsage())
    {
        std::cout << "You have already used your illusion\n";
        return false;
    }
    int val;
    std::cout << "\nChoose a card and the position: ";
    std::cin >> val >> x >> y;
    MinionCard cardToPlace(val, m_currPlayer->GetPlayerColor(), false);

    if (m_currHand.find(cardToPlace) == m_currHand.end()) {
        std::cout << "\nYou don't own any cards of that type!\n";
        system("pause");
        return false;
    }

    cardToPlace.SetIsIllusionCard(true);

    if (m_board->setPos(x, y, cardToPlace, *m_currPlayer) == 1) {
        std::cout << "\nYou can't place that card there!\n";
        system("pause");
        return false;
    }

    cardToPlace.SetIsIllusionCard(false);
    m_currPlayer->UpdateCard(cardToPlace, -1);
    m_currPlayer->SetIllusionUsage(true);
    m_currPlayer->SetIllusionCard(&m_board->getCardOnPos(x, y));
    return true;
}

bool GameDemo::placeMinionCard(size_t& x, size_t& y)
{
    int val;
    std::cout << "\nChoose a card and the position: ";
    std::cin >> val >> x >> y;
    MinionCard cardToPlace(val, m_currPlayer->GetPlayerColor(), false);

    if (m_currHand.find(cardToPlace) == m_currHand.end()) {
        std::cout << "\nYou don't own any cards of that type!\n";
        system("pause");
        return false;
    }

    if (m_board->setPos(x, y, cardToPlace, *m_currPlayer) == 1) {
        std::cout << "\nYou can't place that card there!\n";
        system("pause");
        return false;
    }
    m_currPlayer->UpdateCard(cardToPlace, -1);
    return true;
}

bool GameDemo::useExplosionCard()
{
    if (m_board->getLineCount() == 2)
    {
        ExplosionCard explCard(m_board->getMaxSize());

        printExplosionOptions();
        uint16_t explosionOption;
        bool getOut = false;
        std::cin >> explosionOption;
        do
        {
            switch (explosionOption)
            {
            case 0:
                getOut = true;
                return false;
            case 1:
            {
                Board copyBoard(3);
                Board::cloneMatrix(*m_board, copyBoard);
                Player copyPl1 = *m_p1;
                Player copyPl2 = *m_p2;
                m_board->applyExplosionOnBoard(explCard, *m_p1, *m_p2);
                if (isolatedSpaces(*m_board))
                {
                    Board::cloneMatrix(copyBoard, *m_board);
                    *m_p1 = copyPl1;
                    *m_p2 = copyPl2;
                    std::cout << "Can't have isolated stacks/cards..\n";
                }
                else
                    getOut = true;
                break;
            }
            case 2:
                explCard.RotateToRight(m_board->getMaxSize());
                explCard.showExpl(m_board->getMaxSize());
                std::cin >> explosionOption;
                break;
            default:
                break;
            }
        } while (getOut == false);

    }
    else
    {
        std::cout << "you cannot place a explosion card right now\n";
        return false;
    }
    return true;
}

void GameDemo::restartRound()
{
    if (m_currPlayer->GetPlayerColor() == 'R')
        m_score.first++;
    else
        m_score.second++;
    m_rounds--;
    std::cout << "Player1: " << m_score.first << " | Player2: " << m_score.second << "\n";
    delete m_board;
    delete m_p1;
    delete m_p2;
    if (m_rounds != 0) {
        m_board = new Board(3);
        m_p1 = new Player('R');
        m_p2 = new Player('B');
    }

}

void GameDemo::checkCoveredCards(const coveredSet& coveredCardSet) 
{

    if (coveredCardSet.size() == 0) 
    {
        std::cout << "You have no covered cards.\n";
        return;
    }
    std::cout << "Cards on position {x, y, pos_in_stack}:\n";
    for (auto& i : coveredCardSet) 
        std::cout << "{" << std::get<0>(i) << ", " << std::get<1>(i) << ": " << std::get<2>(i) << "}\n";
    
}

void GameDemo::checkStack(const cardStack& stackToCheck)
{
    std::cout << "Bottom: (";
    for (auto& i : stackToCheck) {
        std::cout << i << ", ";
    }
    std::cout << ")";
}

void GameDemo::checkElementalCardFunction(Board& b, Player*& p1, Player*& p2, Player* currPlayer, hand& currHand, hand& removedCardsHand, bool& wasUsed, bool& wasCardUsed) {
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
        if (funcControlledExplosion(b, *p1, *p2) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
            std::cout << "Failed to use Controlled Explosion\n";
        break;
    }
    case 2: {
        if (currPlayer->GetPlayerColor() == 'R')
        {
            if (funcDestruction(b, *p2) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
                std::cout << "Failed to use Destruction\n";
        }
        else
        {
            if (funcDestruction(b, *p1) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
                std::cout << "Failed to use Destruction\n";
        }
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

            if (funcFlame(b, illusionX, illusionY, x, y, cardToPlace, *currPlayer) == 0)
            {
                wasUsed = true;
            }
            else
            {
                std::cout << "Failed to use Flame\n";
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

            if (funcFlame(b, illusionX, illusionY, x, y, cardToPlace, *currPlayer) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
            {
                std::cout << "Failed to use Flame\n";
                system("pause");
                break;
            }

            cardToPlace.SetIsIllusionCard(false);
            currPlayer->UpdateCard(cardToPlace, -1);
            currPlayer->SetIllusionUsage(true);
            currPlayer->SetIllusionCard(&b.getCardOnPos(x, y));
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

            if (funcFlame(b, illusionX, illusionY, x, y, cardToPlace, *currPlayer) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
            {
                std::cout << "Failed to use Flame\n";
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
            currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
            if (currPlayer->GetPlayerColor() == 'R')
                Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
            else
                Player::updateCover(x, y, p1->getCovered(), b.getMatrix());

            std::cout << "Succesfull move!\n";
        }

        break;
    }
    case 4: {
        uint16_t value;
        std::cout << "Type a value for the card you want to return\n";
        std::cin >> value;
        if (funcFire(b, *p1, *p2, value) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "Failed to use Fire\n";
        }
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

        if (funcAsh(b, *currPlayer, card, x, y) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "Failed to use Ash\n";
            break;
        }

        currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
        if (currPlayer->GetPlayerColor() == 'R')
            Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
        else
            Player::updateCover(x, y, p1->getCovered(), b.getMatrix());

        std::cout << "Succesfull move!\n";
        break;
    }
    case 6: {
        funcSpark(b, *currPlayer);
        break;
    }
    case 7: {
        std::cout << "Type the coodonates of your opponent's card: ";
        uint16_t x, y;
        std::cin >> x >> y;
        if (currPlayer->GetPlayerColor() == 'R')
            funcSquall(b, *p2, x, y);
        else
            funcSquall(b, *p1, x, y);
        break;
    }
    case 8: {
        funcGale(b, *p1, *p2);
        break;
    }
    case 9: {
        std::string type;
        std::cout << "\nMove Row(R) or Column(C): ";
        std::cin >> type;
        uint16_t lineCnt;
        std::cout << "\nWhich line: ";
        std::cin >> lineCnt;
        std::string dir;
        std::cout << "\nWhich direction (left(L)/right(R) for Row, up(U)/down(D) for Column): ";
        std::cin >> dir;
        int condition;
        if (condition = CheckHurricaneInput(b, lineCnt, type, dir) != NO_ERRORS) {
            funcHurricane(b, p1->GetHandCards(), p2->GetHandCards(), lineCnt, type, dir);
        }
        else {
            ErrorMesageHuricane(condition);
        }
        break;
    }
    }
}


