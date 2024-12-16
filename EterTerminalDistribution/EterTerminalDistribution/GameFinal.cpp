#include "GameFinal.h"

void GameFinal::GenerateElementalCards()
{
	//ToDo
}

void GameFinal::GenerateMageCards()
{
	//ToDo
}

void GameFinal::AdvanceAction()
{
	switch (m_activeColor)
	{
	case Colours::RED:
		m_activeColor = Colours::BLUE;
		m_activePlayingHand = &m_player2->GetHandCards();
		m_activeRemovedHand = &m_player2->GetRemovedCards();
		break;
	case Colours::BLUE:
		m_activeColor = Colours::RED;
		m_activePlayingHand = &m_player1->GetHandCards();
		m_activeRemovedHand = &m_player1->GetRemovedCards();
		break;
	default:
		break;
	}
	m_wasPlaced = false;
	m_powerUsed = false;
	return;
}

void GameFinal::EndTurn(bool& tieBraker)
{
	if (m_activePlayingHand->size() == 0 || m_board->isBoardFilled()) {
		tieBraker = true;
		AdvanceAction();
	}

	if (m_board->checkWin() == Colours::INVALID_COL) {
		AdvanceAction();
	}
}

void GameFinal::ResetRound()
{
	m_wasPlaced = false;
	m_powerUsed = false;
	m_tieBraker = false;

	m_board = std::make_unique<Board>(m_board->getMaxSize());
	m_player1 = std::make_unique<Player>(Colours::RED);
	m_player2 = std::make_unique<Player>(Colours::BLUE);

	m_activeColor = Colours::RED;

	m_activeCoveredSet = &m_player1->getCovered();
	m_activePlayingHand = &m_player1->GetHandCards();
	m_activeRemovedHand = &m_player1->GetRemovedCards();

	GenerateElementalCards();
}

GameFinal::GameFinal()
	:
	m_enabledEter{ GameOptions::EnabledEter },
	m_enabledIllusion{ GameOptions::EnabledIllusion },
	m_enabledElemental{ GameOptions::EnabledElemental },
	m_enabledMage{ GameOptions::EnabledMage },
	m_enabledTournament{ GameOptions::DisabledTournament },
	m_enabledTimed{ GameOptions::DisabledTimed },
	m_activeColor{ Colours::RED },
	m_wasPlaced{ false },
	m_powerUsed{ false },
	m_tieBraker{ false },
	m_board{ std::make_unique<Board>(3) },
	m_player1{ std::make_shared<Player>(Colours::RED) },
	m_player2{ std::make_shared<Player>(Colours::BLUE) },
	m_activeCoveredSet{ &m_player1->getCovered() },
	m_activePlayingHand{ &m_player1->GetHandCards() },
	m_activeRemovedHand{ &m_player1->GetRemovedCards() }
{
	GenerateElementalCards();
	GenerateMageCards();
}

GameFinal::GameFinal(	int16_t _maxBoardSize,
						GameOptions _enabledEter,		GameOptions _enabledIllusion,
						GameOptions _enabledMage,		GameOptions _enabledElemental,
						GameOptions _enabledTournament, GameOptions _enabledTimed)
	:
	m_enabledEter{ _enabledEter },
	m_enabledIllusion{ _enabledIllusion },
	m_enabledElemental{ _enabledElemental },
	m_enabledMage{ _enabledMage },
	m_enabledTournament{ _enabledTournament },
	m_enabledTimed{ _enabledTimed },
	m_activeColor{ Colours::RED },
	m_wasPlaced{ false },
	m_powerUsed{ false },
	m_tieBraker{ false },
	m_board{ std::make_unique<Board>(_maxBoardSize) },
	m_player1{ std::make_shared<Player>(Colours::RED) },
	m_player2{ std::make_shared<Player>(Colours::BLUE) },
	m_activeCoveredSet{ &m_player1->getCovered() },
	m_activePlayingHand{ &m_player1->GetHandCards() },
	m_activeRemovedHand{ &m_player1->GetRemovedCards() }
{
	GenerateElementalCards();
	GenerateMageCards();
}
