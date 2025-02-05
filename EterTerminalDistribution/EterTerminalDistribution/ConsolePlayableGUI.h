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
	std::vector<int16_t> GetInputMage(ActionCard _action);
	std::vector<int16_t> GetInputElemental(ActionCard _action);
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

	void Loop();
};

