#include "GameFinal.h"


void GameFinal::AdvanceAction()
{
	switch (m_activeColor)
	{
	case Colours::RED:
		m_activeColor = Colours::BLUE;
		m_activePlayer = m_player2;
		m_activePlayingHand = m_player2->GetHandCards();
		m_activeRemovedHand = m_player2->GetRemovedCards();
		break;
	case Colours::BLUE:
		m_activeColor = Colours::RED;
		m_activePlayer = m_player1;
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

void GameFinal::EndTurn()
{
	if (m_activePlayingHand.size() == 0 || m_board->isBoardFilled()) {
		m_tieBraker = true;
		AdvanceAction();
	}
	if (m_board->checkWin() != Colours::INVALID_COL) {
		AdvanceAction();
	}
}

void GameFinal::ResetRound()
{
	m_wasPlaced = false;
	m_powerUsed = false;
	m_tieBraker = false;

	m_board = std::move(std::make_unique<Board>(m_board->getMaxSize()));
	m_player1 = std::move(std::make_unique<Player>(Colours::RED, false));
	m_player2 = std::move(std::make_unique<Player>(Colours::BLUE, false));

	m_activeColor = Colours::RED;

	m_activeCoveredSet = m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();

}

GameFinal::GameFinal()
	:
	m_enabledEter		{ GameOptions::EnabledEter },
	m_enabledIllusion	{ GameOptions::EnabledIllusion },
	m_enabledElemental	{ GameOptions::EnabledElemental },
	m_enabledMage		{ GameOptions::EnabledMage },
	m_enabledTournament	{ GameOptions::DisabledTournament },
	m_enabledTimed		{ GameOptions::DisabledTimed },
	m_activeColor		{ Colours::RED },
	m_winnerStatus		{ Colours::INVALID_COL },
	m_wasPlaced			{ false },
	m_powerUsed			{ false },
	m_tieBraker			{ false }
{
	m_board = std::make_unique<Board>(3);
	m_player1 = std::make_shared<Player>(Colours::RED, m_enabledElemental, m_enabledMage);
	m_player2 = std::make_shared<Player>(Colours::BLUE, m_enabledElemental, m_enabledMage);
	m_activeCoveredSet =  m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
}

GameFinal::GameFinal(	int16_t _maxBoardSize,
						GameOptions _enabledEter,		GameOptions _enabledIllusion,
						GameOptions _enabledMage,		GameOptions _enabledElemental,
						GameOptions _enabledTournament, GameOptions _enabledTimed) :
	m_enabledEter		{ _enabledEter },
	m_enabledIllusion	{ _enabledIllusion },
	m_enabledElemental	{ _enabledElemental },
	m_enabledMage		{ _enabledMage },
	m_enabledTournament	{ _enabledTournament },
	m_enabledTimed		{ _enabledTimed },
	m_activeColor		{ Colours::RED },
	m_winnerStatus		{ Colours::INVALID_COL},
	m_wasPlaced			{ false },
	m_powerUsed			{ false },
	m_tieBraker			{ false },
	m_board				{ std::make_unique<Board>(_maxBoardSize) },
	m_player1			{ std::make_shared<Player>(Colours::RED, false) },
	m_player2			{ std::make_shared<Player>(Colours::BLUE, false) },
	m_activePlayer		{ std::shared_ptr<Player>(m_player1)}
{
	m_activeCoveredSet = m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
}

bool GameFinal::PlaceCard(int16_t _x, int16_t _y, int16_t _val)
{
	if (!m_activePlayer->HasCardOfValue(_val)) {
		return false;
	}
	if (m_board->isBoardEmpty()) {
		m_board->PlaceCard(m_activePlayer->PlayCard(_val), 0, 0);
		m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
		PrintBoard();
		return true;
	}
	BoardErrors tryPlace = m_board->CanPlace(_x, _y, _val);
	if (tryPlace != BoardErrors::_NO_ERRORS && tryPlace != BoardErrors::ILLUSION_PROPERTY)
		return false;

	m_board->PlaceCard(m_activePlayer->PlayCard(_val), _x, _y);
	m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
	PrintBoard();
	return true;
}

void GameFinal::PlayElemental()
{

}

void GameFinal::PlayMage()
{

}

bool GameFinal::CheckWin()
{
	return (m_winnerStatus = m_board->checkWin()) != Colours::INVALID_COL;
}

void GameFinal::PrintBoard(bool _debug)
{
	m_board->printBoard(_debug);
}

void GameFinal::PrintActiveHand()
{
	auto& seekHand = m_activePlayer->GetRemaningCounter();
	std::for_each(seekHand.begin(), seekHand.end(), [&seekHand](const auto& key) {qDebug() << key.first << ": " << key.second << "copies left\n"; });
}
