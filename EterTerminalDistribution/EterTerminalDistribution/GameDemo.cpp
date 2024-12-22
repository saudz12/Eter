#include "GameDemo.h"

GameDemo::GameDemo(uint16_t size,uint16_t numberOfRounds)
{
    m_board = new Board(size);
    m_p1 = new Player(Colours::RED);
    m_p2 = new Player(Colours::BLUE);
    m_currPlayer = nullptr;
    m_currPlayerColor = Colours::RED;
    m_wasPlaced = false;
    m_wasElementalCardUsed = false;
    m_rounds = numberOfRounds;
    m_blizzardCardRound = Colours::INVALID_COL;
    m_score = { 0,0 };
}

void GameDemo::runDemo()
{
    bool elementalCardUsedTester = false;
    while (m_rounds) {
        //get current player data
        system("cls");
        m_board->printBoard(false);
        m_wasPlaced = false;
        m_currPlayer = m_currPlayerColor== Colours::RED ? m_p1 : m_p2;
        showPlayerTurn(m_currPlayerColor);
        if (m_currPlayer->GetPlayerColor() == Colours::RED)
            setStructuresForPlayer(m_p1);
        else
            setStructuresForPlayer(m_p2);
        ///menu
        uint16_t options;

        printMenu();
        std::cin >> options;
        int16_t x, y;
        switch (options)
        {
        case 1: {
            m_currPlayer->printHandCards();
            printHand(m_currPlayer->GetHandCards());
            uint16_t placeOption;
            printOptionsForCards(placeOption);
   
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
                if (m_currPlayer->GetPlayerColor() == Colours::RED)
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
            int16_t x, y;
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
            helpMenuOption();
            system("pause");
            break;
        }
        case 8:
        {
            m_wasPlaced = useExplosionCard();
            system("pause");
            break;
        }
        case 9:
        {
            system("pause");
            break;
        }
        default:
            break;
        }

        if (m_wasPlaced) {
            m_wasPlaced = false;

            if (m_blizzardCardRound == m_currPlayer->GetPlayerColor())
            {
                m_blizzardCardRound = Colours::INVALID_COL;
                ResizeableMatrix& matrix = m_board->getMatrix();

                for (size_t row = 0; row < matrix.size(); row++)
                {
                    for (size_t col = 0; col < matrix[row].size(); col++)
                        if (!matrix[row][col].empty() && matrix[row][col].back().GetCardType() == CardType::BlizzardCard)
                            matrix[row][col].pop_back();
                }
            }
            //check win condition
            /*if (elementalCardUsedTester == true) { ///big error  - elemental cards need different check ;-;
                elementalCardUsedTester = false;
                continue;
            }*/
            if (m_board->checkWin() != Colours::INVALID_COL) {
                restartRound();
                system("pause");
                continue;
                ///Tiebreaker - update it
                if (m_board->isBoardFilled() || m_currHand.empty()) {
                    //The other player has one more move left!
                    if (m_currPlayerColor == Colours::RED)
                        m_currPlayerColor = Colours::BLUE;
                    else
                        m_currPlayerColor = Colours::RED;
                    m_currPlayer = m_currPlayerColor == Colours::RED ? m_p1 : m_p2;
                    m_currHand = m_currPlayer->GetHandCards();

                    system("cls");
                    m_board->printBoard(false);
                    showPlayerTurn(m_currPlayerColor);

                    ///menu
                    printMenu();
                    std::cin >> options;
                    switch (options)
                    {
                    case 1: {
                        m_currPlayer->printHandCards();
                        uint16_t placeOption;
                        printOptionsForCards(placeOption);

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
                            if (m_currPlayer->GetPlayerColor() == Colours::RED)
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
                        int16_t x, y;
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
                        helpMenuOption();
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

                    if (m_board->checkWin() != Colours::INVALID_COL) {
                        if (m_currPlayer->GetPlayerColor() == Colours::RED)
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
                            m_p1 = new Player(Colours::RED);
                            m_p2 = new Player(Colours::BLUE);
                        }
                        system("pause");
                    }
                }
            }
            
            if (m_currPlayerColor == Colours::RED)
                m_currPlayerColor = Colours::BLUE;
            else
                m_currPlayerColor = Colours::RED;
            m_currPlayer = m_currPlayerColor == Colours::RED ? m_p1 : m_p2;
        }
    }
}

void GameDemo::showPlayerTurn(Colours color)
{
    if (color== Colours::RED)
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

bool GameDemo::placeEterCard(int16_t& x, int16_t& y)
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

bool GameDemo::placeIllusionCard(int16_t& x, int16_t& y)
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

bool GameDemo::placeMinionCard(int16_t& x, int16_t& y)
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

        printOptionsForExplostion();
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
    if (m_currPlayer->GetPlayerColor() == Colours::RED)
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
        m_p1 = new Player(Colours::RED);
        m_p2 = new Player(Colours::BLUE);
    }

}

void GameDemo::checkCoveredCards(const CoveredSet& coveredCardSet) 
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

void GameDemo::checkStack(const CardStack& stackToCheck)
{
    std::cout << "Bottom: (";
    for (auto& i : stackToCheck) {
        std::cout << i << ", ";
    }
    std::cout << ")";
}

void GameDemo::checkElementalCardFunction(Board& b, Player*& p1, Player*& p2, Player* currPlayer, Hand& currHand, Hand& removedCardsHand, bool& wasUsed, bool& wasCardUsed) {
    std::cout << "\nELEMENTAL CARDS:\n";
    std::cout << "1. Controlled Explosion\n2. Destruction\n3. Flame\n4. Fire\n5. Ash\n6. Spark\n7. Squall\n8. Gale\n";
    std::cout << "9. Hurricane\n10. Gust\n11. Mirage\n12. Storm\n13. Tide\n14. Mist\n15. Wave\n16. Whirlpool\n";
    std::cout << "17. Blizzard\n18. Waterfall\n19. Support\n20. Earthquake\n21. Crumble\n22. Border\n23. Avalanche\n24. Rock\n";
    std::cout << "25. Go back\n";
    uint16_t card;
    std::cin >> card;
    switch (card)
    {
    //controlled explosion
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
    //destruction
    case 2: {
        if (currPlayer->GetPlayerColor() == Colours::RED)
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
    //flame
    case 3: {
        int16_t illusionX, illusionY, x, y, val;
        std::cout << "Type the coordonates of the illusion card you want to reveal\n";
        std::cin >> illusionX >> illusionY;

        currPlayer->printHandCards();
        uint16_t placeOption;
        std::cout << "Options:\n1. Place eter card\n2. Play a minion card as an illusion\n3. Play a minion card\n";
        std::cin >> placeOption;

        int condition;

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
                wasCardUsed = true;
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
            if (currPlayer->GetPlayerColor() == Colours::RED)
                Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
            else
                Player::updateCover(x, y, p1->getCovered(), b.getMatrix());

            std::cout << "Succesfull move!\n";
        }

        break;
    }
    //fire
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
    //ash
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
            currPlayer->returnMinionCardToHand(card);
            std::cout << "Failed to use Ash\n";
            break;
        }

        currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
        if (currPlayer->GetPlayerColor() == Colours::RED)
            Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
        else
            Player::updateCover(x, y, p1->getCovered(), b.getMatrix());

        std::cout << "Succesfull move!\n";
        break;
    }
    //spark
    case 6: {
        if (funcSpark(b, *currPlayer) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
            std::cout << "Failed to use Spark\n";
        break;
    }
    //squall
    case 7: {
        std::cout << "Type the coodonates of your opponent's card: ";
        uint16_t x, y;
        std::cin >> x >> y;
        if (currPlayer->GetPlayerColor() == Colours::RED)
        {
            if (funcSquall(b, *p2, x, y) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
                std::cout << "Failed to use Squall\n";
        }
        else
        {
            if (funcSquall(b, *p1, x, y) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
                std::cout << "Failed to use Squall\n";
        }
        break;
    }
    //gale
    case 8: {
        if (funcGale(b, *p1, *p2) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
            std::cout << "Failed to use Gale\n";
        break;
    }
    //hurricane
    case 9: {
        char type;
        std::cout << "\nMove Row(R-r) or Column(C-c): ";
        std::cin >> type;
        uint16_t lineCnt;
        std::cout << "\nWhich line: ";
        std::cin >> lineCnt;
        char dir;
        std::cout << "\nWhich direction (left(L-l)/right(R-r) for Row, up(U-u)/down(D-d) for Column): ";
        std::cin >> dir;
        CommonErrors condition = CheckHurricaneInput(b, lineCnt, GetLineType(toupper(type)), GetDirection(toupper(dir)));
        if (condition == CommonErrors::_NO_ERRORS) {
            funcHurricane(b, p1->GetHandCards(), p2->GetHandCards(), lineCnt, GetLineType(toupper(type)), GetDirection(toupper(dir)));
            wasUsed = true;
            wasCardUsed = true;
        }
        else {
            ErrorMesageHuricane(condition);
        }
        break;
    }
    //gust
    case 10: {
        uint16_t x1, y1, x2, y2;
        std::cout << "\nChoose a card you want to move: ";
        std::cin >> x1 >> y1;
        std::cout << "\nChoose a neighboring card of a lower value you want to cover: ";
        std::cin >> x2 >> y2;

        if (b.getCardOnPos(x1, y1).GetColor() == Colours::RED)
        {
            if (funcGust(b, *p1, x1, y1, x2, y2) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
                std::cout << "Failed to use Gust\n";
        }
        else if (b.getCardOnPos(x1, y1).GetColor() == Colours::BLUE)
        {
            if (funcGust(b, *p2, x1, y1, x2, y2) == 0)
            {
                wasUsed = true;
                wasCardUsed = true;
            }
            else
                std::cout << "Failed to use Gust\n";
        }
        break;
    }
    //mirage
    case 11: {
        uint16_t x, y;
        std::cout << "\nType the position of your illusion: ";
        std::cin >> x >> y;
        m_currPlayer->printHandCards();
        std::cout << "\nChoose a card: ";
        uint16_t val;
        std::cin >> val;
        MinionCard toPlace(val, currPlayer->GetPlayerColor(), false);

        if (funcMirage(b, *currPlayer, x, y, toPlace) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
            currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
            currPlayer->SetIllusionCard(nullptr);
            currPlayer->UpdateCard(toPlace, -1);
            if (m_currPlayer->GetPlayerColor() == Colours::RED)
                Player::updateCover(x, y, m_p2->getCovered(), m_board->getMatrix());
            else
                Player::updateCover(x, y, m_p1->getCovered(), m_board->getMatrix());
        }
        else
            std::cout << "Failed to use Mirage\n";
        break;
    }
    //storm
    case 12: {
        uint16_t x, y;
        std::cout << "\nChoose a position from which you want to remove the stack of cards: ";
        std::cin >> x >> y;

        if (funcStorm(b, *p1, *p2, x, y) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "Failed to use Storm\n";
        }

        break;
    }
    //tide
    case 13: {
        uint16_t x1, y1, x2, y2;
        std::cout << "\nChoose the positions for the spaces you want to switch: ";
        std::cin >> x1 >> y1 >> x2 >> y2;

        if (funcTide(b, x1, y1, x2, y2) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Tide";
        }

        break;
    }
    //mist
    case 14: {
        currPlayer->printHandCards();

        int16_t val, x, y;
        std::cout << "\nChoose a card you want to place as an illusion and the position: ";
        std::cin >> val >> x >> y;
        MinionCard card(val, currPlayer->GetPlayerColor(), false);

        if (currHand.find(card) == currHand.end()) {
            std::cout << "\nYou don't own any cards of that type!\n";
            system("pause");
            break;
        }

        m_currPlayer->UpdateCard(card, -1);
        if (funcMist(b, *currPlayer, x, y, card) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            m_currPlayer->UpdateCard(card, 1);
            std::cout << "Failed to use Mist\n";
            break;
        }

        currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
        if (currPlayer->GetPlayerColor() == Colours::RED)
            Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
        else
            Player::updateCover(x, y, p1->getCovered(), b.getMatrix());
        break;
    }
    //wave
    case 15: {
        uint16_t x, y;
        std::cout << "\nChoose a stack of cards which you want to move to a nearby empty space: ";
        std::cin >> x >> y;

        currPlayer->printHandCards();
        int16_t val;
        std::cout << "\nChoose a card you want to place into the now empty space: ";
        std::cin >> val;

        MinionCard card(val, currPlayer->GetPlayerColor(), false);

        if (currHand.find(card) == currHand.end()) {
            std::cout << "\nYou don't own any cards of that type!\n";
            system("pause");
            break;
        }

        if (funcWave(b, *currPlayer, x, y, card) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Wave\n";
            break;
        }

        m_currPlayer->UpdateCard(card, -1);
        currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
        if (currPlayer->GetPlayerColor() == Colours::RED)
            Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
        else
            Player::updateCover(x, y, p1->getCovered(), b.getMatrix());
        break;
    }
    //whirlpool
    case 16: {
        std::cout << "\nChoose an empty space you want to whirlpool\n";
        int16_t x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (CheckWhirlpool(b, x1, y1, x2, y2, Preference::FIRST) == CommonErrors::_NO_ERRORS)
        {
            //funcWhirlpool();
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Whirlpool\n";
            break;
        }

        break;
    }
    //blizzard
    case 17: {
        std::cout << "\nChoose if you want to affect a row or a column (R/C)\n";
        char type;
        std::cin >> type;
        std::cout << "\nChoose an index\n";
        uint16_t index;
        std::cin >> index;

        if (funcBlizzard(b, index, type) == 0)
        {
            if (m_currPlayerColor == Colours::RED)
                m_blizzardCardRound = Colours::BLUE;
            else
                m_blizzardCardRound = Colours::RED;
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Blizzard\n";
            break;
        }

        break;
    }
    //waterfall
    case 18: {
        uint16_t x, y;
        std::cout << "\nChoose a card for which column you want to collapse to the bottom, which your chosen card on top: ";
        std::cin >> x >> y;

        if (funcWaterfall(b, x, y) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Waterfall";
        }

        break;
    }
    //support
    case 19: {
        uint16_t x, y;
        std::cout << "\n Choose a card which you want to increased its value by 1, cannot be used on a value 4 card: ";
        std::cin >> x >> y;

        if (funcSupport(b, x, y) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Support";
        }

        break;
    }
    //earthquake
    case 20: {
        if (funcEarthquake(b, *p1, *p2) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Earthquake";
        }

        break;
    }
    //crumble
    case 21: {
        uint16_t x, y;
        std::cout << "\nChoose a card which you want to lower its value by 1, cannot be used on a value 1 card: ";
        std::cin >> x >> y;

        if (funcCrumble(b, x, y) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Crumble\n";
        }

        break;
    }   
    //border
    case 22: {
        int16_t x, y;
        std::cout << "\nChoose the coordonates for where to place the border\n";
        std::cin >> x >> y;

        if (funcBorder(b, x, y) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Border\n";
        }

        break;
    }
    //Avalanche
    case 23: {
        int16_t x1, y1, x2, y2;
        char dir;
        std::cout << "\nChoose 2 neighboring cards, if they are vertical choose to move them up or down (U/D), ";
        std::cout << "if they are horizontal choose to move them left or right (L/R): ";
        std::cin >> x1 >> y1 >> x2 >> y2 >> dir;

        if (checkFuncAvalanche(b, x1, x2, y1, y2, GetDirection(dir)) == CommonErrors::_NO_ERRORS) {
            funcAvalanche(b, x1, y1, x2, y2, GetDirection(dir));

            wasUsed = true;
            wasCardUsed = true;
        }

        break;
    }
    //Rock
    case 24: {
        uint16_t x, y;
        std::cout << "\nChoose an illusion card you want to cover with one of your cards: ";
        std::cin >> x >> y;

        currPlayer->printHandCards();
        std::cout << "\nChoose a card you want to  play: ";
        uint16_t val;
        std::cin >> val;

        MinionCard card(val, currPlayer->GetPlayerColor(), false);

        if (currHand.find(card) == currHand.end()) {
            std::cout << "\nYou don't own any cards of that type!\n";
            system("pause");
            break;
        }

        if (funcRock(b, x, y, card) == 0)
        {
            wasUsed = true;
            wasCardUsed = true;
        }
        else
        {
            std::cout << "\nFailed to use Rock\n";
            break;
        }

        m_currPlayer->UpdateCard(card, -1);
        currPlayer->SetLastMinionCardPlayed(&b.getCardOnPos(x, y));
        if (currPlayer->GetPlayerColor() == Colours::RED)
            Player::updateCover(x, y, p2->getCovered(), b.getMatrix());
        else
            Player::updateCover(x, y, p1->getCovered(), b.getMatrix());
        break;
    }
    //go back
    case 25: {
        break;
    }
    }
}


void GameDemo::advanceTurn()
{
    m_currPlayerColor = (m_currPlayerColor == Colours::RED) ? Colours::BLUE : Colours::RED;

    m_wasPlaced = false;
    m_currPlayer = (m_currPlayerColor == Colours::RED()) ? m_p1 : m_p2;
}



