#include "ConsolePlayableGUI.h"

GameView::LaunchOptions GameView::GetMode(int16_t _m)
{
    switch (_m)
    {
    case 1:
        return LaunchOptions::TRAINING;
    case 2:
        return LaunchOptions::ELEMENTAL;
    case 3:
        return LaunchOptions::MAGE_DUEL;
    case 4:
        return LaunchOptions::TOURNAMENT;
    case 5:
        return LaunchOptions::TIMED;
    default:
        return LaunchOptions::INVALID_GAME_MODE;
    }
}

void GameView::LaunchMenu()
{
	/*int cnt = 0;
    
    int c = 0;
    
    auto func = [&cnt](int _o) -> std::string {
        if (cnt == _o)
            return "> ";
        else
            return "";
        };

    while (c != 13)
        //if (_kbhit() != 0)
    {
        std::cout << func(0) << "1. Training\n";
        std::cout << func(1) << "2. Elemental\n";
        std::cout << func(2) << "3. Mage duel\n";
        std::cout << func(3) << "4. Tournament\n";
        std::cout << func(4) << "5. Timed\n";

        c = _getch();
        
        //std::cout << c;
        switch (c)
        {
        case GameView::LEAVE:
            exit(0);
        case GameView::SELECT:
            return;
        case GameView::DOWN:
            cnt++;
            cnt %= 5;
            break;
        case GameView::UP:
            cnt--;
            if (cnt < 0)
                cnt = 4;
            break;
        default:
            break;
        }

        system("cls");
        
        m_activeMode = GetMode(c);
    }*/

    uint16_t option;

    while (true)
    {
        PrintGameOptions();

        std::cin >> option;

        switch (option)
        {
        case 0:
            exit(0);
        case 1:
            m_activeMode = GetMode(1);
            return;
        case 2:
            m_activeMode = GetMode(2);
            return;
        case 3:
            m_activeMode = GetMode(3);
            return;
        case 4:
            m_activeMode = GetMode(4);
            return;
        case 5:
            m_activeMode = GetMode(5);
            return;
        default:
            std::cout << "Invalid option..";
            system("cls");
            break;
        }
    }
}

void GameView::GetPlayingFormat()
{
    int16_t size = 4;

    switch (m_activeMode)
    {
    case LaunchOptions::TRAINING:
        size = 3;
        Eter = GameOptions::DisabledEter;
        Illusion = GameOptions::DisabledIllusion;
        break;
    case LaunchOptions::ELEMENTAL:
        Elemental = GameOptions::EnabledElemental;
        break;
    case LaunchOptions::MAGE_DUEL:
        Mage = GameOptions::EnabledMage;
        break;
    case LaunchOptions::TOURNAMENT:
        //pick random
        Elemental = GameOptions::EnabledElemental;
        Mage = GameOptions::EnabledMage;
        Tournament = GameOptions::EnabledTournament;

        break;
    case LaunchOptions::TIMED:
        //pick random?
        Timed = GameOptions::EnabledTimed;
        break;
    case LaunchOptions::INVALID_GAME_MODE:
        size = 0;
        break;
    default:
        break;
    }
    //return std::make_shared<GameFinal>(new GameFinal{size, Eter, Illusion, Mage, Elemental, Tournament, Timed}); //nu merge??
    //m_game = GameFinal{ std::move(GameFinal{ size, Eter, Illusion, Mage, Elemental, Tournament, Timed }) };
    m_game = std::make_unique<GameFinal>(size, Eter, Illusion, Mage, Elemental, Tournament, Timed);
}

std::vector<int16_t> GameView::GetInput(ActionCard _action)
{
    std::vector<int16_t> inputData{};

    switch (_action)
    {
    case ActionCard::FireMage1: {
        int16_t x, y;
        std::cout << "Pos x and y on the board fot the card: " << std::endl;
        std::cin >> x >> y;
        inputData.push_back(x);
        inputData.push_back(y);
        
        break;
    }
    case ActionCard::FireMage2:
    {
        int16_t line;
        char type;
        std::cout << "Line l and line type ('c' for Column, 'r' for Row - type sensitvie) on the board: " << std::endl;
        std::cin >> line >> type;
        inputData.push_back(line);
        inputData.push_back(int16_t(type));
        
        break;
    }
    case ActionCard::EarthMage1:
    {
        int16_t x, y, val;
        std::cout << "Pos x and y on the board: " << std::endl;
        std::cin >> x >> y;
        std::cout << "Val of card from hand: " << std::endl;
        std::cin >> val;
        inputData.push_back(x);
        inputData.push_back(y);
        inputData.push_back(val);

        break; 
    }
    case ActionCard::EarthMage2:
    {
        int16_t x, y;
        std::cout << "Pos x and y on the board for the hole: " << std::endl;
        std::cin >> x >> y;
        inputData.push_back(x);
        inputData.push_back(y);

        break;
    }
    case ActionCard::AirMage1:
    {
        int16_t xS, yS, xD, yD;
        std::cout << "Pos x and y on the board for origin: " << std::endl;
        std::cin >> xS >> yS;
        std::cout << "Pos x and y on the board for destination: " << std::endl;
        std::cin >> xD >> yD;
        inputData.push_back(xS);
        inputData.push_back(yS);
        inputData.push_back(xD);
        inputData.push_back(yD);

        break;
    }
    case ActionCard::AirMage2:
    {
        int16_t x, y;
        std::cout << "Pos x and y on the board for card: " << std::endl;
        std::cin >> x >> y;
        inputData.push_back(x);
        inputData.push_back(y);

        break;
    }
    case ActionCard::WaterMage1:
    {
        int16_t xS, yS, xD, yD;
        std::cout << "Pos x and y on the board for origin: " << std::endl;
        std::cin >> xS >> yS;
        std::cout << "Pos x and y on the board for destination: " << std::endl;
        std::cin >> xD >> yD;
        inputData.push_back(xS);
        inputData.push_back(yS);
        inputData.push_back(xD);
        inputData.push_back(yD);

        break;
    }
    case ActionCard::WaterMage2:
    {
        char m;
        std::cout << "Select margin: 't' fot TOP, 'b' for BOTTOM, 'l' for LEFT, 'r' for RIGHT: " << std::endl;
        std::cin >> m;
        inputData.push_back(int16_t(m));

        break;
    }
    default:
        return std::vector<int16_t>{};
    }

    if (m_game->CheckInput(m_game->GetCurrentPlayerMage(), inputData) == CommonErrors::_NO_ERRORS) {
        return inputData;
    }

    return std::vector<int16_t>{};
}

void GameView::PrintGameOptions()
{
    std::cout << "Chose a game mode to play: " << std::endl << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Standard" << std::endl;
    std::cout << "2. Elemental" << std::endl;
    std::cout << "3. Mage Duel" << std::endl;
    std::cout << "4. Tournament" << std::endl;
    std::cout << "5. Timed" << std::endl;
}

void GameView::PrintPlayerOptions()
{
    if (m_game->GetActiveColour() == Colours::RED)
        std::cout << "Red's ";
    else
        std::cout << "Blue's ";
    std::cout << "Turn.\n\nChose an action: " << std::endl << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Place a card from hand" << std::endl;
    std::cout << "2. Use a special power" << std::endl;
}

GameView::GameView() :
    Illusion    { GameOptions::EnabledIllusion },
    Mage        { GameOptions::DisabledMage },
    Elemental   { GameOptions::DisabledElemental },
    Tournament  { GameOptions::DisabledTournament },
    Timed       { GameOptions::DisabledTimed },
    Eter        { GameOptions::EnabledEter }
{
    //m_game = std::make_unique<test>(newteste);
    LaunchMenu();
    GetPlayingFormat();
}

void GameView::Loop()
{
    int16_t x, y, val;

    bool goNext = false;

    while (true)
    {
        goNext = false;
        m_game->PrintBoard();
        
        int option;
        std::cout << std::endl;
        PrintPlayerOptions();
        std::cin >> option;
        std::vector<int16_t> inputData{};
        
        switch (option)
        {
        case 1:
            m_game->PrintActiveHand();
            std::cout << "Where(x, y) and Card: " << std::endl;
            std::cin >> x >> y >> val;
                if (m_game->PlaceCard(x, y, val)) {
                goNext = true;
            }
            break;
        case 2:
            if (m_activeMode == LaunchOptions::MAGE_DUEL) {
                //get input
                //check input --> break if broken
                //play card
                
                inputData = GetInput(m_game->GetCurrentPlayerMage());
                if (!inputData.empty())
                {
                    goNext = true;
                    m_game->PlayMage(inputData);
                }
                else
                    std::cout << "Wrong input :/" << std::endl;
            }
            else if (m_activeMode == LaunchOptions::ELEMENTAL) {
                //choose card
                //get input
                //check input --> break if broken
                //play card
            }
            break;
        default:
            break;
        }

        if (goNext) {
            m_game->EndTurn();
            Colours winner;
            if ((winner = m_game->CheckWinner()) != Colours::INVALID_COL) {
                if (winner == Colours::RED)
                    std::cout << "RED WON!@!@!!@@!" << std::endl;
                else
                    std::cout << "BLUEWONONOWNON" << std::endl;
                m_game->ResetRound();
            }
        }
            
    }

}
