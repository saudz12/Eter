#pragma once
#include "GameFinal.h"
#include <conio.h>

static enum class LaunchOptions : int16_t
{
	TRAINING,
	ELEMENTAL,
	MAGE_DUEL,
	TOURNAMENT,
	TIMED,
	INVALID_GAME_MODE
};

static LaunchOptions GetMode(int _m);

class GameView {
	std::shared_ptr<GameFinal> m_game;
	LaunchOptions m_activeMode;

	void LaunchMenu();
	std::shared_ptr<GameFinal>&& GetPlayingFormat();

	static const int UP{ 72 };
	static const int DOWN{ 80 };
	static const int LEFT{ 75 };
	static const int RIGHT{ 77 };
	static const int LEAVE{ 27 };
	static const int SELECT{ 13 };

public:

	GameView();

	void Loop();
};

