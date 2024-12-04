#include "GameFinal.h"

void GameFinal::advanceAction()
{
	switch (m_activeColor)
	{
	case Colours::RED:
		m_activeColor = Colours::BLUE;
		m_activePlayingHand = m_player2->GetHandCards();
		m_activeRemovedHand = m_player2->GetRemovedCards();
		break;
	case Colours::BLUE:
		m_activeColor = Colours::RED;
		m_activePlayingHand = m_player1->GetHandCards();
		m_activeRemovedHand = m_player1->GetRemovedCards();
		break;
	default:
		break;
	}
	m_wasPlaced = false;
	m_powerUsed = false;
	return;
}

GameFinal::GameFinal(int16_t nrOfRounds, int16_t maxBoardSize, Options enabledEter, Options enabledIllusion, Options enabledMage, Options enabledElemental, Options enabledTimed)
	:
	m_rounds{ nrOfRounds },
	m_enabledEter{ enabledEter },
	m_enabledIllusion{ enabledIllusion },
	m_enabledElemental{ enabledElemental },
	m_enabledMage{ enabledMage },
	m_enabledTimed{ enabledTimed },
	m_activeColor{ Colours::RED },
	m_wasPlaced{ false },
	m_powerUsed{ false },
	m_board{ std::make_unique<Board>(maxBoardSize)},
	m_player1{ std::make_unique<Player>(Colours::RED) },
	m_player2{ std::make_unique<Player>(Colours::BLUE) },
	m_activePlayingHand{ m_player1->GetHandCards() },
	m_activeRemovedHand{ m_player1->GetRemovedCards() },
	m_activeCoveredSet{ m_player1->getCovered()}
{

}

void GameFinal::generateElementalCards()
{
	
}

void GameFinal::generateMageCards()
{	

}

void GameFinal::gameLoop()
{

}

void GameFinal::resetRound(int16_t maxBoardSize, Options enabledEter, Options enabledIllusion, Options enabledMage, Options enabledElemental, Options enabledTimed)
{
	m_enabledEter = enabledEter;
	m_enabledIllusion = enabledIllusion;
	m_enabledMage = enabledMage;
	m_enabledElemental = enabledElemental;
	m_enabledTimed = enabledTimed;
	m_wasPlaced = false;
	m_powerUsed = false;

	m_board = std::make_unique<Board>(maxBoardSize);
	m_player1 = std::make_unique<Player>(Colours::RED);
	m_player2 = std::make_unique<Player>(Colours::BLUE);

	m_activeColor = Colours::RED;
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
	m_activeCoveredSet = m_player1->getCovered();
}
