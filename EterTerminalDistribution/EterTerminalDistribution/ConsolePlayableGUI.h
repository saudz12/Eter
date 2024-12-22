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

	//std::unique_ptr<test> m_game(new test);
	GameFinal m_game;
	LaunchOptions m_activeMode;

	void LaunchMenu();
	void GetPlayingFormat();

	/*static const int UP{ 72 };
	static const int DOWN{ 80 };
	static const int LEFT{ 75 };
	static const int RIGHT{ 77 };
	static const int LEAVE{ 27 };
	static const int SELECT{ 13 };*/

	void PrintGameOptions();

public:

	GameView();

	void Loop();
};

