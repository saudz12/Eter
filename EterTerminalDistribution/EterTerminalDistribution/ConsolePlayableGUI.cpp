#include "ConsolePlayableGUI.h"

void GameView::LaunchMenu()
{
	int cnt = 0;
    
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
    }
}

std::shared_ptr<GameFinal>&& GameView::GetPlayingFormat()
{
    int16_t size = 4;
    GameOptions Eter {GameOptions::EnabledEter};
    GameOptions Illusion {GameOptions::EnabledIllusion};
    GameOptions Mage {GameOptions::EnabledMage};
    GameOptions Elemental {GameOptions::DisabledElemental};
    GameOptions Tournament {GameOptions::DisabledTournament};
    GameOptions Timed {GameOptions::DisabledTimed};

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
    return std::make_shared<GameFinal>(GameFinal());
}

GameView::GameView::GameView()
    : m_activeMode{LaunchOptions::TRAINING}
{
	LaunchMenu();
    
    m_game = GetPlayingFormat();
}

void GameView::Loop()
{
}

LaunchOptions GetMode(int _m)
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
