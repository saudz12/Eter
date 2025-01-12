#pragma once
#include "GameFinal.h"
//#include <memory>
//#include <conio.h>


class GameView {
	enum class LaunchOptions : int16_t
	{
		TRAINING,
		ELEMENTAL,
		MAGE_DUEL,
		TOURNAMENT,
		TIMED,
		INVALID_GAME_MODE
	};

	LaunchOptions GetMode(int16_t _m);

	std::unique_ptr<GameFinal> m_game;
	//GameFinal m_game;
	LaunchOptions m_activeMode;
	GameOptions Eter;
	GameOptions Illusion;
	GameOptions Mage;
	GameOptions Elemental;
	GameOptions Tournament;
	GameOptions Timed;

	void LaunchMenu();
	void GetPlayingFormat();

	/*static const int UP{ 72 };
	static const int DOWN{ 80 };
	static const int LEFT{ 75 };
	static const int RIGHT{ 77 };
	static const int LEAVE{ 27 };
	static const int SELECT{ 13 };*/

	void PrintGameOptions();
	void PrintPlayerOptions();

public:

	GameView();
	GameView(GameOptions illusion,
		GameOptions mage,
		GameOptions elemental,
		GameOptions tournament,
		GameOptions timed,
		GameOptions eter);
	void Loop();
	bool PlaceCard(const int16_t x,const uint16_t y,const uint16_t val);

    GameFinal& GetGameFinal()  { return *m_game; }
};

