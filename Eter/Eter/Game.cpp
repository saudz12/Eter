#include "Game.h"
#include "Game.h"

Game::Game() {
	m_elapsedGames = 0;
	m_player1Wins = 0;
	m_player2Wins = 0;

	m_timed = 0;
	m_tournament = 0;
	m_training = 0;
	m_wizardDuel = 0;
	m_elementalBattle = 0;
	m_Player1 = getPlayer1();
	m_Player2 = getPlayer2();
	m_boardGame = getBoardGame();
}

Board Game::getBoardGame()
{
	return Board();
}

Player Game::getPlayer1()
{
	return Player{ "R" };
}

Player Game::getPlayer2()
{
	return Player{ "B" };
}

void Game::setBoardGame(Board board)
{
	m_boardGame = board;
}

void Game::timedGame()
{
}

void Game::tournamentGame()
{
}

void Game::trainingGame()
{
}

void Game::wizardDuelGame()
{
}

void Game::elementalBattleGame()
{
}
