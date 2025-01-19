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

	m_board = std::make_unique<Board>(m_board->getMaxSize());
	m_player1 = std::make_unique<Player>(Colours::RED, false);
	m_player2 = std::make_unique<Player>(Colours::BLUE, false);

	m_activePlayer = std::shared_ptr<Player>(m_player1);

	m_activeColor = Colours::RED;

	m_activeCoveredSet = m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();

	std::random_device rd;
	std::uniform_int_distribution<int16_t> elementalrange(1, 24);



	m_elemental1 = std::move(PowerUsage{ false, GetMageCard(elementalrange(rd)) });
	m_elemental2 = std::move(PowerUsage{ false, GetMageCard(elementalrange(rd)) });
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
	m_player1 = std::make_shared<Player>(Colours::RED, true);
	m_player2 = std::make_shared<Player>(Colours::BLUE, true);
	m_activeCoveredSet =  m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
}

GameFinal::GameFinal(std::string path)
{

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
	m_player1			{ std::make_shared<Player>(Colours::RED, _enabledEter != GameOptions::EnabledEter) },
	m_player2			{ std::make_shared<Player>(Colours::BLUE, _enabledEter != GameOptions::EnabledEter) },
	m_activePlayer		{ std::shared_ptr<Player>(m_player1)}
{
	m_activeCoveredSet = m_player1->getCovered();
	m_activePlayingHand = m_player1->GetHandCards();
	m_activeRemovedHand = m_player1->GetRemovedCards();
	std::random_device rd;
	std::uniform_int_distribution<int16_t> magerange(1, 8);
	m_redMage = std::move(PowerUsage{false, GetMageCard(magerange(rd))});
	m_blueMage = std::move(PowerUsage{ false, GetMageCard(magerange(rd))});
	std::uniform_int_distribution<int16_t> elementalrange(1, 24);
	m_elemental1 = std::move(PowerUsage{ false, GetElementalCard(elementalrange(rd))});
	m_elemental2 = std::move(PowerUsage{ false, GetElementalCard(elementalrange(rd))});

	//REMOVE THIS LATER: !!
	m_redMage.second = ActionCard::WaterMage2;
	m_blueMage.second = ActionCard::WaterMage2;
}

ActionCard GameFinal::GetCurrentPlayerMage()
{
	switch (m_activeColor)
	{
	case Colours::RED:
		return m_redMage.second;
	case Colours::BLUE:
		return m_blueMage.second;
	default:
		return ActionCard::Default;
	}
}

CommonErrors GameFinal::CheckInput(ActionCard _action, std::vector<int16_t> _inputData)
{
	switch (_action)
	{
	case ActionCard::FireMage1: 
	{
		int16_t x = _inputData[0];
		int16_t y = _inputData[1];
		return checkFuncFireMage1(*m_board, *m_activePlayer, x, y, m_board->GetStackSize(x, y) - 1);
	}
	case ActionCard::FireMage2: 
	{
		int16_t line = _inputData[0];
		LineType type = GetLineType(char(_inputData[1]));
		return checkFuncFireMage2(*m_board, *m_activePlayer, line, type);
	}
	case ActionCard::EarthMage1:
	{
		int16_t x = _inputData[0];
		int16_t y = _inputData[1];
		int16_t val = _inputData[2];
		return checkFuncEarthMage1(*m_board, *m_activePlayer, x, y, val);
	}
	case ActionCard::EarthMage2:
	{
		int16_t x = _inputData[0];
		int16_t y = _inputData[1];
		return checkFuncEarthMage2(*m_board, x, y);
	}
	case ActionCard::AirMage1:
	{
		int16_t xS = _inputData[0];
		int16_t yS = _inputData[1];
		int16_t xD = _inputData[2];
		int16_t yD = _inputData[3];
		return checkFuncAirMage1(*m_board, m_activeColor, xS, yS, xD, yD);
	}
	case ActionCard::AirMage2:
	{
		int16_t x = _inputData[0];
		int16_t y = _inputData[1];
		return checkFuncAirMage2(*m_board, x, y, m_activeColor);
	}
	case ActionCard::WaterMage1:
	{
		int16_t xS = _inputData[0];
		int16_t yS = _inputData[1];
		int16_t xD = _inputData[2];
		int16_t yD = _inputData[3];
		return checkFuncWaterMage1(*m_board, m_activeColor, xS, yS, xD, yD);
	}
	case ActionCard::WaterMage2:
	{
		MarginType margin = GetMargin(char(_inputData[0]));
		return checkFuncWaterMage2(*m_board, margin);
	}
	case  ActionCard::Gust:
	{
		int16_t x1 = _inputData[0];
		int16_t y1 = _inputData[1];
		int16_t x2 = _inputData[2];
		int16_t y2 = _inputData[3];
		return checkFuncGust(*m_board, x1, y1, x2, y2);
	}
	case ActionCard::Mirage:
	{
		int16_t x = _inputData[0];
		int16_t y = _inputData[1];
		return checkFuncMirage(*m_board, x, y);
	}
	case ActionCard::Waterfall:
		return CommonErrors::_NO_ERRORS;
	case ActionCard::Mist:
		return CommonErrors::_NO_ERRORS;
	case ActionCard::Support:
		return checkFuncSupport(*m_board, _inputData[0], _inputData[1]);
	default:
	{
		return CommonErrors::_INVALID_CARD_TYPE;
	}
	}

	return CommonErrors::_INVALID_CARD_TYPE;
}

Colours GameFinal::GetActiveColour()
{
	return m_activeColor;
}

bool GameFinal::CanPlayMage()
{
	if(m_activeColor == Colours::RED)
		return !m_redMage.first;
	return !m_blueMage.first;
}

bool GameFinal::PlaceCard(int16_t _x, int16_t _y, int16_t _val)
{
	if (m_board->isBoardEmpty()) {
		if (!m_activePlayer->HasCardOfValue(_val)) {
			return false;
		}
		m_board->PlaceCard(m_activePlayer->PlayCard(_val), 0, 0);
		return true;
	}

	if (m_board->CheckPos(_x, _y) == BoardErrors::_OUTSIDE_BOUND)
		return false;

	if (!m_activePlayer->HasCardOfValue(_val)) {
		return false;
	}

	BoardErrors tryPlace = m_board->CanPlace(_x, _y, _val);
	if (tryPlace != BoardErrors::_NO_ERRORS && tryPlace != BoardErrors::ILLUSION_PROPERTY)
		return false;

	m_board->PlaceCard(m_activePlayer->PlayCard(_val), _x, _y);
	m_activePlayer->UpdateCard(_val, CardAction::REMOVE);
	return true;
}

void GameFinal::PlayElemental(PowerSelect select, std::vector<int16_t> positions)
{
	/*if (m_powerUsed) return;
	m_powerUsed = true;*/
	ActionCard toSearch = ActionCard::Default;
	if (select == PowerSelect::First && m_elemental1.first == false)
	{
		m_elemental1.first = true;
		toSearch = m_elemental1.second;
	}
	else if (select == PowerSelect::Second && m_elemental2.first == false)
	{
		m_elemental2.first = true;
		toSearch = m_elemental2.second;
	}

	switch (toSearch)
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
	default:
		break;
	}
}

void GameFinal::PlayMage(std::vector<int16_t> inputData)
{
	/*if (m_powerUsed) return;
	m_powerUsed = true;*/
	ActionCard toSearch = ActionCard::Default;
	if (m_activeColor == Colours::RED && m_redMage.first == false) {
		m_redMage.first = true;
		toSearch = m_redMage.second;
	}
	else if (m_activeColor == Colours::BLUE && m_blueMage.first == false)
	{
		m_blueMage.first = true;
		toSearch = m_blueMage.second;
	}
	switch (toSearch)
	{
	case ActionCard::FireMage1:
		funcFireMage1(*m_board, *m_activePlayer, inputData[0], inputData[1], inputData[2]);
		break;
	case ActionCard::FireMage2:
		funcFireMage2(*m_board, *m_activePlayer, inputData[0], GetLineType(char(inputData[1])));
		break;
	case ActionCard::EarthMage1:
		funcEarthMage1(*m_board, *m_activePlayer, m_activeColor == Colours::RED ? *m_player2 : *m_player1, inputData[0], inputData[1], inputData[2]);
		break;
	case ActionCard::EarthMage2:
		funcEarthMage2(*m_board, inputData[0], inputData[1]);
		break;
	case ActionCard::AirMage1:
		funcAirMage1(*m_board, inputData[0], inputData[1], inputData[2], inputData[3]);
		break;
	case ActionCard::AirMage2:
		funcAirMage2(*m_board, m_activeColor, inputData[0], inputData[1]);
		break;
	case ActionCard::WaterMage1:
		funcAirMage1(*m_board, inputData[0], inputData[1], inputData[2], inputData[3]);
		break;
	case ActionCard::WaterMage2:
		funcWaterMage2(*m_board, GetMargin(char(inputData[0])));
		break;
	default:
		break;
	}

}


Colours GameFinal::CheckWinner()
{
	m_winnerStatus = m_board->checkWin();

	return m_winnerStatus;
}

void GameFinal::PrintBoard(bool _debug)
{
	m_board->printBoard(_debug);
}

void GameFinal::PrintActiveHand()
{
	auto& seekHand = m_activePlayer->GetRemaningCounter();
	std::for_each(seekHand.begin(), seekHand.end(), [&seekHand](const auto& key) {std::cout << key.first << ": " << key.second << " copies left\n"; });
}

template <typename T1, typename T2>
json GameFinal::serializePairAsObject(const std::pair<T1, T2>& pair) {
	return { {"first", pair.first}, {"second", pair.second} };
}

void GameFinal::SaveCurrentToJson()
{
	json jsonObject;

	//board
	
	jsonObject["matrix"] = m_board->SerialiseMatrix();

	//players
	
	jsonObject["player1"] = m_player1->SerialisePlayer();
	jsonObject["player2"] = m_player2->SerialisePlayer();

	//game
	jsonObject["score"] = serializePairAsObject(m_gameScore);
	jsonObject["active_color"] = m_activeColor;
	jsonObject["winner_status"] = m_winnerStatus;

	jsonObject["enavbled_eter"] = m_enabledEter;
	jsonObject["enavbled_illusion"] = m_enabledIllusion;
	jsonObject["enavbled_mage"] = m_enabledMage;
	jsonObject["enavbled_elemental"] = m_enabledElemental;
	jsonObject["enavbled_timed"] = m_enabledTimed;
	jsonObject["enavbled_tournament"] = m_enabledTournament;

	jsonObject["was_placed"] = m_wasPlaced;
	jsonObject["power_used"] = m_powerUsed;
	jsonObject["tie_braker"] = m_tieBraker;

	jsonObject["red_mage"] = serializePairAsObject(m_redMage);
	jsonObject["blue_mage"] = serializePairAsObject(m_blueMage);
	jsonObject["elemental_1"] = serializePairAsObject(m_elemental1);
	jsonObject["elemental_2"] = serializePairAsObject(m_elemental2);

	std::ofstream outFile("savefile.json");
	if (outFile.is_open()) {
		outFile << jsonObject.dump(4); // Pretty-print with 4 spaces
		outFile.close();
		std::cout << "JSON object written to 'savefile.json'." << std::endl;
	}
	else {
		std::cerr << "Failed to open file for writing!" << std::endl;
	}
}
