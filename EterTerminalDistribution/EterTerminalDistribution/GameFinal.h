#pragma once
#include "Board.h"
#include "InputChecking.h"

enum class Options : int16_t
{
	EnabledEter,
	DisabledEter,
	EnabledIllusion,
	DisabledIllusion,
	EnabledMage,
	DisabledMage,
	EnabledElemental,
	DisabledElemental,
	EnabledTimed,
	DisabledTimed
};

class GameFinal{
private:
	std::unique_ptr<Board> m_board;
	std::unique_ptr<Player> m_player1;
	std::unique_ptr<Player> m_player2;

	Hand& m_activePlayingHand;
	Hand& m_activeRemovedHand;

	Score m_gameScore;
	int16_t m_rounds;
	Colours m_activeColor;

	bool m_wasPlaced;
	bool m_powerUsed;

	Options m_enabledEter;
	Options m_enabledIllusion;
	Options m_enabledMage;
	Options m_enabledElemental;
	Options m_enabledTimed;

	void advanceRound();

public:
	GameFinal(int16_t nrOfRounds, int16_t maxBoardSize, Options enabledEter, Options enabledIllusion, Options enabledMage, Options enabledElemental, Options enabledTimed);

	void generateElementalCards();
	void generateMageCards();

	void gameLoop();
};