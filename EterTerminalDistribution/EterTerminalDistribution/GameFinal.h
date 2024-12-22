#pragma once
#include "Board.h"
#include "InputChecking.h"

class GameFinal{
private:
	std::shared_ptr<Player> m_player1;
	std::shared_ptr<Player> m_player2;
	std::unique_ptr<Board> m_board;

	//weak pointer(and change to shared) to current player? - usefull in some places
	CoveredSet m_activeCoveredSet;
	Hand m_activePlayingHand;
	Hand m_activeRemovedHand;
	Player m_activePlayer;

	Score m_gameScore;
	Colours m_activeColor;

	GameOptions m_enabledEter;
	GameOptions m_enabledIllusion;
	GameOptions m_enabledMage;
	GameOptions m_enabledElemental;
	GameOptions m_enabledTimed;
	GameOptions m_enabledTournament;

	bool m_wasPlaced;
	bool m_powerUsed;
	bool m_tieBraker;
	
	void AdvanceAction();
	void EndTurn();
	//void resetRound(int16_t maxBoardSize, GameOptions enabledEter, GameOptions enabledIllusion, GameOptions enabledMage, GameOptions enabledElemental, GameOptions enabledTimed);
	void ResetRound();

public:
	GameFinal();
	GameFinal(	int16_t _maxBoardSize,	
				GameOptions _enabledEter,		GameOptions _enabledIllusion,
				GameOptions _enabledMage,		GameOptions _enabledElemental,
				GameOptions _enabledTournament,	GameOptions _enabledTimed);
	
	
};