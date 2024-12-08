#include "GameFinal.h"

void GameFinal::GenerateElementalCards()
{
	//ToDo
}

void GameFinal::GenerateMageCards()
{
	//ToDo
}

void GameFinal::PlayRound()
{
	while (true) {
		system("cls");
		int16_t option;
		PrintStandardMenu(option, m_enabledElemental, m_powerUsed, m_enabledMage, true); //needs player

		switch (option)
		{
		case 1:
			int16_t val, x, y;
			std::cin >> val >> x >> y;

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
		}
		if (m_tieBraker) {
			switch (m_board->checkWin())
			{
			case Colours::INVALID_COL:
			{

			}
			case Colours::RED:
			{
				m_gameScore.first++;
			}
			case Colours::BLUE:
			{
				m_gameScore.second++;
			}
			//ResetRound();
			return;
			}
		}
		if (m_board->isBoardFilled() || m_activePlayingHand->size() == 0) {
			m_tieBraker = true;
			AdvanceAction();
		}
		if (m_wasPlaced ) {

		}
	}
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

GameFinal::GameFinal(int16_t nrOfRounds, int16_t maxBoardSize,	GameOptions enabledEter =	GameOptions::DisabledEter,	GameOptions enabledIllusion =	GameOptions::DisabledIllusion,
																GameOptions enabledMage =	GameOptions::DisabledMage,	GameOptions enabledElemental =	GameOptions::DisabledElemental,
																GameOptions enabledTimed =	GameOptions::DisabledTimed,	GameOptions enabledTournament =	GameOptions::DisabledTournament)
	:
	m_rounds{ nrOfRounds },
	m_enabledEter{ enabledEter },
	m_enabledIllusion{ enabledIllusion },
	m_enabledElemental{ enabledElemental },
	m_enabledMage{ enabledMage },
	m_enabledTimed{ enabledTimed },
	m_enabledTournament{ enabledTournament },
	m_activeColor{ Colours::RED },
	m_wasPlaced{ false },
	m_powerUsed{ false },
	m_tieBraker{ false },
	m_board{ std::make_unique<Board>(maxBoardSize) },
	m_player1{ std::make_shared<Player>(Colours::RED) },
	m_player2{ std::make_shared<Player>(Colours::BLUE) },
	m_activeCoveredSet{ &m_player1->getCovered() },
	m_activePlayingHand{ &m_player1->GetHandCards() },
	m_activeRemovedHand{ &m_player1->GetRemovedCards() }
{
	GenerateElementalCards();
	GenerateMageCards();
}

void GameFinal::GameLoop()
{
	for (int i = 0; i < m_rounds; i++) {
		PlayRound();
		if (m_enabledTournament == GameOptions::EnabledElemental) {
			//get random atributes. For now default.
			//resetRound(m_board->getMaxSize(), m_enabledEter, m_enabledIllusion, m_enabledMage, m_enabledElemental, m_enabledElemental);
			ResetRound();
		}
		else {
			ResetRound();
		}
	}
}
