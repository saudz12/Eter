#include "ConsolePlayableGUI.h"

GameView::LaunchOptions GameView::GetMode(int16_t _m)
{
    switch (_m)
    {
    case 0:
        return LaunchOptions::TRAINING;
    case 1:
        return LaunchOptions::ELEMENTAL;
    case 2:
        return LaunchOptions::MAGE_DUEL;
    case 3:
        return LaunchOptions::TOURNAMENT;
    case 4:
        return LaunchOptions::TIMED;
    default:
        return LaunchOptions::INVALID_GAME_MODE;
    }
}

//void GameView::LaunchMenu()
//{
//	/*int cnt = 0;
//    
//    int c = 0;
//    
//    auto func = [&cnt](int _o) -> std::string {
//        if (cnt == _o)
//            return "> ";
//        else
//            return "";
//        };
//
//    while (c != 13)
//        //if (_kbhit() != 0)
//    {
//        
//        << func(0) << "1. Training\n";
//        qDebug() << func(1) << "2. Elemental\n";
//        qDebug() << func(2) << "3. Mage duel\n";
//        qDebug() << func(3) << "4. Tournament\n";
//        qDebug() << func(4) << "5. Timed\n";
//
//        c = _getch();
//        
//        //qDebug() << c;
//        switch (c)
//        {
//        case GameView::LEAVE:
//            exit(0);
//        case GameView::SELECT:
//            return;
//        case GameView::DOWN:
//            cnt++;
//            cnt %= 5;
//            break;
//        case GameView::UP:
//            cnt--;
//            if (cnt < 0)
//                cnt = 4;
//            break;
//        default:
//            break;
//        }
//
//        system("cls");
//        
//        m_activeMode = GetMode(c);
//    }*/
//
//    uint16_t option;
//
//    while (true)
//    {
//        PrintGameOptions();
//
//        std::cin >> option;
//
//        switch (option)
//        {
//        case 0:
//            exit(0);
//        case 1:
//            ;
//            return;
//        case 2:
//            return;
//        case 3:
//            return;
//        case 4:
//            return;
//        case 5:
//            return;
//        default:
//            qDebug() << "Invalid option..";
//            system("cls");
//            break;
//        }
//    }
//}

void GameView::GetLaunchMode()
{
    m_activeMode = LaunchOptions::TRAINING;
    if (Mage == GameOptions::EnabledMage)
        m_activeMode = LaunchOptions::MAGE_DUEL;
    else if (Elemental == GameOptions::EnabledElemental)
        m_activeMode = LaunchOptions::ELEMENTAL;
    else if (Tournament == GameOptions::EnabledTournament)
        m_activeMode = LaunchOptions::TOURNAMENT;
    else if (Timed == GameOptions::EnabledTimed)
        m_activeMode = LaunchOptions::TIMED;
}

void GameView::GetPlayingFormat()
{
    boardSize = 4;

    switch (m_activeMode)
    {
    case LaunchOptions::TRAINING:
        boardSize = 3;
        Eter = GameOptions::DisabledEter;
        Illusion = GameOptions::EnabledIllusion;
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
        break;
    case LaunchOptions::TIMED:
        //pick random?
        Timed = GameOptions::EnabledTimed;
        break;
    case LaunchOptions::INVALID_GAME_MODE:
        boardSize = 0;
        break;
    default:
        break;
    }
    //return std::make_shared<GameFinal>(new GameFinal{size, Eter, Illusion, Mage, Elemental, Tournament, Timed}); //nu merge??
    //m_game = GameFinal{ std::move(GameFinal{ size, Eter, Illusion, Mage, Elemental, Tournament, Timed }) };
    m_game = std::make_unique<GameFinal>(boardSize, Eter, Illusion, Mage, Elemental, Tournament, Timed);
}

void GameView::PrintGameOptions()
{
    qDebug() << "Chose a game mode to play: " << '\n' << '\n';
    qDebug() << "0. Exit" << '\n';
    qDebug() << "1. Standard" << '\n';
    qDebug() << "2. Elemental" << '\n';
    qDebug() << "3. Mage Duel" << '\n';
    qDebug() << "4. Tournament" << '\n';
    qDebug() << "5. Timed" << '\n';
}

void GameView::PrintPlayerOptions()
{
    qDebug() << "Chose an action: " << '\n' << '\n';
    qDebug() << "0. Exit" << '\n';
    qDebug() << "1. Place a card from hand" << '\n';
    qDebug() << "2. Use a special power" << '\n';
}

GameView::GameView() :
    Illusion    { GameOptions::EnabledIllusion },
    Mage        { GameOptions::EnabledMage },
    Elemental   { GameOptions::DisabledElemental },
    Tournament  { GameOptions::DisabledTournament },
    Timed       { GameOptions::DisabledTimed },
    Eter        { GameOptions::EnabledEter }
{
    //m_game = std::make_unique<test>(newteste);
    //LaunchMenu();
    GetLaunchMode();
    GetPlayingFormat();
}

GameView::GameView(GameOptions illusion,
    GameOptions mage, GameOptions elemental, GameOptions tournament, GameOptions timed, GameOptions eter) : 
    Illusion{illusion},
    Elemental{elemental},
    Mage{mage},
    Tournament{tournament},
    Timed{timed},
    Eter{eter}
{
    GetLaunchMode();
    GetPlayingFormat();
}

bool GameView::CheckWin()
{
    return m_game->CheckWin();
}

void GameView::Loop()
{
    int16_t x, y, val;
    while (true)
    {
        m_game->PrintBoard();
        
        qDebug() << "Where(x, y) and Card: " << '\n';
        std::cin >> x >> y >> val;
    }
}

bool GameView::PlaceCard(const int16_t x, const uint16_t y, const uint16_t val)
{
    if (m_game->PlaceCard(x, y, val))
    {
        m_game->PrintBoard();
        return true;
    }
    else
    {
        return false;
    }
}

IllusionErrors GameView::PlaceIllusion(const int16_t x, const uint16_t y, const uint16_t val)
{
    if (m_game->PlaceIllusion(x, y, val)==IllusionErrors::_NO_ERRORS)
    {
        m_game->PrintBoard();
        return IllusionErrors::_NO_ERRORS;
    }
    else 
    {
        return m_game->PlaceIllusion(x, y, val);
    }
}

void GameView::EndTurn()
{
    m_game->EndTurn();
}

ExplosionCard GameView::GenerateNewExplosionCard()
{
    return m_game->generateNewExplosionCard();
}

bool GameView::tryToApplyExplosionOnBoard(ExplosionCard& card)
{
    return m_game->tryToApplyExplosionOnBoard(card);
}

std::vector<MarginType> GameView::applyExplosionOnBoard(const ExplosionCard& card) const
{
    return m_game->applyExplosionOnBoard(card);
}
