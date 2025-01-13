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
	std::shared_ptr<Player> m_activePlayer;
	//Player m_activePlayer;

	Score m_gameScore;
	Colours m_activeColor;
	Colours m_winnerStatus;

	GameOptions m_enabledEter;
	GameOptions m_enabledIllusion;
	GameOptions m_enabledMage;
	GameOptions m_enabledElemental;
	GameOptions m_enabledTimed;
	GameOptions m_enabledTournament;

	//ExplosionCard m_explosion;

	bool m_wasPlaced;
	bool m_powerUsed;
	bool m_tieBraker;
	bool m_wasExplosionCardPlayed;
public:
	GameFinal();
	GameFinal(	int16_t _maxBoardSize,	
				GameOptions _enabledEter,		GameOptions _enabledIllusion,
				GameOptions _enabledMage,		GameOptions _enabledElemental,
				GameOptions _enabledTournament,	GameOptions _enabledTimed);
	Colours GetActiveColor() { return m_activeColor; }
	const Player& GetRedPlayer() const  { return *m_player1; }
	const Player& GetBluePlayer() const { return *m_player2; }

#pragma region turn_logic
	void AdvanceAction();
	void EndTurn();
	void ResetRound();
#pragma endregion

#pragma region action_logic
	bool PlaceCard(int16_t _x, int16_t _y, int16_t _val);
	void PlayElemental();
	void PlayMage();
	bool CheckWin(); //cheking everything
	bool CheckWin(int16_t _x, int16_t _y); //singlechecking
#pragma endregion

#pragma region print_api
	void PrintBoard(bool _debug = false);
	void PrintActiveHand();
#pragma endregion
};