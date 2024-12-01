#pragma once

#include "Player.h"
#include "Board.h"
class Game : Player,Board
{
	private:
		Board m_boardGame;
		Player m_Player1, m_Player2; // we don't have a constructor without params in Player class, resorted to this
		// uint8_t gameType; //could we use this instead of 5 bools?
		bool m_timed,
			 m_tournament,
			 m_training,
		  	 m_wizardDuel,
			 m_elementalBattle;
		uint8_t m_elapsedGames, 
				m_player1Wins, 
				m_player2Wins;
	public:
		// constructors/destructors
		Game();
		//Game(const Game &game);
		//~Game();

		//getters
		//Board getBoardGame();
		Player getPlayer1();
		Player getPlayer2();

		//setters
		void setBoardGame(Board board);


		//methods
		void timedGame();
		void tournamentGame();
		void trainingGame();
		void wizardDuelGame();
		void elementalBattleGame();


};

