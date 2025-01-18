#pragma once
#include "Board.h"
#include "InputChecking.h"

using PowerUsage = std::pair<bool, ActionCard>;

enum class PowerSelect : int16_t {
	First,
	Second,
};

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

	bool m_wasPlaced;
	bool m_powerUsed;
	bool m_tieBraker;

	PowerUsage m_redMage;
	PowerUsage m_blueMage;
	PowerUsage m_elemental1;
	PowerUsage m_elemental2;

public:
	GameFinal();
	GameFinal(	int16_t _maxBoardSize,	
				GameOptions _enabledEter,		GameOptions _enabledIllusion,
				GameOptions _enabledMage,		GameOptions _enabledElemental,
				GameOptions _enabledTournament,	GameOptions _enabledTimed);

	ActionCard GetCurrentPlayerMage();
	CommonErrors CheckInput(ActionCard _action, std::vector<int16_t> _inputData);
	Colours GetActiveColour();

#pragma region turn_logic
	void AdvanceAction();
	void EndTurn();
	void ResetRound();
#pragma endregion

#pragma region action_logic
	bool PlaceCard(int16_t _x, int16_t _y, int16_t _val);
	void PlayElemental(PowerSelect select, std::vector<int16_t> positions);
	void PlayMage(std::vector<int16_t> inputData);
	Colours CheckWinner(); //cheking everything
	bool CheckWin(int16_t _x, int16_t _y); //singlechecking
#pragma endregion

#pragma region print_api
	void PrintBoard(bool _debug = false);
	void PrintActiveHand();
#pragma endregion
};