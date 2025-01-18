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

	std::random_device rd;
	std::uniform_int_distribution<int16_t> elementalrange(1, 24);

	int16_t firstCardNumber{ elementalrange(rd) };
	int16_t secondCardNumber{ elementalrange(rd) };

	while (firstCardNumber == secondCardNumber)
		secondCardNumber = elementalrange(rd);

	m_elemental1 = std::move(PowerUsage{ false, GetElementalCard(firstCardNumber), firstCardNumber });
	m_elemental2 = std::move(PowerUsage{ false, GetElementalCard(secondCardNumber), secondCardNumber });
}

void GameFinal::FindPower(ActionCard identif)
{
	switch (identif)
	{
	case ActionCard::ControlledExplosion:
		break;
	case ActionCard::Destruction:
		break;
	case ActionCard::Flame:
		break;
	case ActionCard::Fire:
		break;
	case ActionCard::Ash:
		break;
	case ActionCard::Spark:
		break;
	case ActionCard::Squall:
		break;
	case ActionCard::Gale:
		break;
	case ActionCard::Hurricane:
		break;
	case ActionCard::Gust:
		break;
	case ActionCard::Mirage:
		break;
	case ActionCard::Storm:
		break;
	case ActionCard::Tide:
		break;
	case ActionCard::Mist:
		break;
	case ActionCard::Wave:
		break;
	case ActionCard::Whirlpool:
		break;
	case ActionCard::Blizzard:
		break;
	case ActionCard::Waterfall:
		break;
	case ActionCard::Support:
		break;
	case ActionCard::Earthquake:
		break;
	case ActionCard::Crumble:
		break;
	case ActionCard::Border:
		break;
	case ActionCard::Avalanche:
		break;
	case ActionCard::Rock:
		break;
	case ActionCard::Default:
		break;
	case ActionCard::FireMage1:
		break;
	case ActionCard::FireMage2:
		break;
	case ActionCard::EarthMage1:
		break;
	case ActionCard::EarthMage2:
		break;
	case ActionCard::AirMage1:
		break;
	case ActionCard::AirMage2:
		break;
	case ActionCard::WaterMage1:
		break;
	case ActionCard::WaterMage2:
		break;
	default:
		break;
	}
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
	m_winnerStatus{ Colours::INVALID_COL },
	m_wasPlaced{ false },
	m_powerUsed{ false },
	m_tieBraker{ false },
	m_wasExplosionPlayed{false}
{
	m_board = std::make_unique<Board>(3);
	m_player1 = std::make_shared<Player>(Colours::RED, m_enabledElemental, m_enabledMage);
	m_player2 = std::make_shared<Player>(Colours::BLUE, m_enabledElemental, m_enabledMage);
	m_activeCoveredSet = m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
}

GameFinal::GameFinal(int16_t _maxBoardSize,
	GameOptions _enabledEter, GameOptions _enabledIllusion,
	GameOptions _enabledMage, GameOptions _enabledElemental,
	GameOptions _enabledTournament, GameOptions _enabledTimed) :
	m_enabledEter{ _enabledEter },
	m_enabledIllusion{ _enabledIllusion },
	m_enabledElemental{ _enabledElemental },
	m_enabledMage{ _enabledMage },
	m_enabledTournament{ _enabledTournament },
	m_enabledTimed{ _enabledTimed },
	m_activeColor{ Colours::RED },
	m_winnerStatus{ Colours::INVALID_COL },
	m_wasPlaced{ false },
	m_powerUsed{ false },
	m_tieBraker{ false },
	m_board{ std::make_unique<Board>(_maxBoardSize) },
	m_player1{ std::make_shared<Player>(Colours::RED, _maxBoardSize==3?true:false) },
	m_player2{ std::make_shared<Player>(Colours::BLUE, _maxBoardSize == 3 ? true : false) },
	m_activePlayer{ std::shared_ptr<Player>(m_player1) },
	m_canPlayExplosion{false},
	m_wasExplosionPlayed{false}
{
	m_activeCoveredSet = m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
	std::random_device rd;
	std::uniform_int_distribution<int16_t> magerange(1, 8);

	int16_t firstMageCard{ magerange(rd) };
	int16_t secondMageCard{ magerange(rd) };

	while (firstMageCard == secondMageCard)
		secondMageCard = magerange(rd);

	m_redMage = std::move(PowerUsage{ false, GetMageCard(magerange(rd)), firstMageCard });
	m_blueMage = std::move(PowerUsage{ false, GetMageCard(magerange(rd)), secondMageCard });

	std::uniform_int_distribution<int16_t> elementalrange(1, 24);

	int16_t firstCardNumber{ elementalrange(rd) };
	int16_t secondCardNumber{ elementalrange(rd) };

	while (firstCardNumber == secondCardNumber)
		secondCardNumber = elementalrange(rd);

	m_elemental1 = std::move(PowerUsage{ false, GetElementalCard(firstCardNumber), firstCardNumber });
	m_elemental2 = std::move(PowerUsage{ false, GetElementalCard(secondCardNumber), secondCardNumber });
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
	
	bool canCoverIllusion = m_board->CanCoverIllusion(_x, _y, _val);
	if (canCoverIllusion)
	{
		if (m_board->getCardOnPos(_x, _y).GetValue() < _val)
		{
			m_board->RemoveTop(_x, _y);
			m_board->PlaceCard(m_activePlayer->PlayCard(_val), _x, _y);
			m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
		}
		else
		{
			m_board->RevealIllusion(_x, _y);
			m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
		}
		return true;
	}

	m_board->PlaceCard(m_activePlayer->PlayCard(_val), _x, _y);
	m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
	if (m_board->getRowCount() == m_board->getMaxSize() && m_board->getColCount() == m_board->getMaxSize() && !m_canPlayExplosion)
	{
		m_canPlayExplosion = true;
		m_wasExplosionPlayed = true;
	}
	PrintBoard();
	return true;
}
void GameFinal::PlayElemental(PowerSelect select)
{
	if (m_powerUsed) return;
	m_powerUsed = true;
	if (select == PowerSelect::First && std::get<0>(m_elemental1) == false)
	{
		std::get<0>(m_elemental1) = true;
		FindPower(std::get<1>(m_elemental1));
	}
	else if (select == PowerSelect::Second && std::get<0>(m_elemental2) == false)
	{
		std::get<0>(m_elemental2) = true;
		FindPower(std::get<1>(m_elemental2));
	}
}

void GameFinal::PlayMage()
{
	if (m_powerUsed) return;
	m_powerUsed = true;
	if (m_activeColor == Colours::RED && std::get<0>(m_redMage) == false) {
		std::get<0>(m_redMage) = true;
		FindPower(std::get<1>(m_redMage));
	}
	else if (m_activeColor == Colours::BLUE && std::get<0>(m_blueMage) == false)
	{
		std::get<0>(m_blueMage) = true;
		FindPower(std::get<1>(m_blueMage));
	}

}

bool GameFinal::CheckWin()
{
	return (m_winnerStatus = m_board->checkWin()) != Colours::INVALID_COL;
}

IllusionErrors GameFinal::PlaceIllusion(int16_t _x, int16_t _y, int16_t _val)
{
	if (m_activePlayer->GetIllusionUsage() == true)
		return IllusionErrors::_ILLUSION_ALREADY_USED;

	if (m_board->isBoardEmpty()) {
		m_board->PlaceIllusion(m_activePlayer->PlayCard(_val), 0, 0);
		m_activePlayer->SetIllusionUsage(true);
		m_activePlayer->PlayCard(0);
		m_activePlayer->UpdateCard(0, CardAction::REMOVE);
		m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
		return IllusionErrors::_NO_ERRORS;
	}

	if (!m_board->isEmptySpace(_x, _y)) {
		return IllusionErrors::_INVALID_SPACE;//invalid space
	}

	m_board->PlaceIllusion(m_activePlayer->PlayCard(_val), _x, _y);
	m_activePlayer->SetIllusionUsage(true);
	m_activePlayer->PlayCard(0);
	m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
	m_activePlayer->UpdateCard(0, CardAction::REMOVE);
	if (m_board->getRowCount() == m_board->getMaxSize() && m_board->getColCount() && !m_canPlayExplosion)
	{
		m_canPlayExplosion = true;
		m_wasExplosionPlayed = true;
	}
	return IllusionErrors::_NO_ERRORS;
}

void GameFinal::PrintBoard(bool _debug)
{
	m_board->printBoard(_debug);
}

void GameFinal::PrintActiveHand()
{
	auto& seekHand = m_activePlayer->GetRemaningCounter();
	std::for_each(seekHand.begin(), seekHand.end(), [&seekHand](const auto& key) {std::cout << key.first << ": " << key.second << "copies left\n"; });
}

ExplosionCard GameFinal::generateNewExplosionCard()
{
	return ExplosionCard(m_board->getMaxSize());
}

std::shared_ptr<Player> GameFinal::getPlayer1() const {
	return m_player1;
}

std::shared_ptr<Player> GameFinal::getPlayer2() const {
	return m_player2;
}

int16_t GameFinal::getFirstElementalCardId() const
{
	return std::get<2>(m_elemental1);
}

int16_t GameFinal::getSecondElementalCardId() const
{
	return std::get<2>(m_elemental2);
}

bool GameFinal::tryToApplyExplosionOnBoard(ExplosionCard& card)
{
	return m_board->tryApplyExplosionOnBoard(card,*m_player1,*m_player2);
}

void GameFinal::applyExplosionOnBoard(const ExplosionCard& card)
{
	m_board->applyExplosionOnBoard(card,*m_player1,*m_player2,false);
}

