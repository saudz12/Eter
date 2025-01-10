#include "Player.h"

Player::Player(Colours playerColor)
	:	m_playerColor{ playerColor }, m_illusionUsage{ false }, m_eterCardUsage{ false }/*, m_remainingCounter{}, m_remainingCards{5}*/
		
{
	/*if (training)
		generateTrainingModeHand();
	else*/
		generateHand();

	//new
}

Player::Player(Colours _playerColor, bool _training)
	:	m_playerColor{ _playerColor },
		m_illusionUsage{ false },
		m_eterCardUsage{ false },
		m_illusionCard{ nullptr },
		m_lastMinionCardPlayed{ nullptr },
		m_remainingCards{5}
{
	GenerateHand(_training);
}

Player::Player()
	: m_playerColor{ Colours::RED }, m_illusionUsage{ false }, m_eterCardUsage{ false }
{
	generateTrainingModeHand();
}

Player::Player(Colours playerColor, GameOptions elementalDuelOption, GameOptions mageDuelOption):
	m_playerColor{ playerColor }, m_illusionUsage{ false }, m_eterCardUsage{ false }/*, m_remainingCounter{}, m_remainingCards{5}*/
{
	generateHand();

	if (elementalDuelOption == GameOptions::EnabledElemental) 
		m_elementalCard = ElementalCard();
	else 
		m_elementalCard = std::nullopt;   

	if (mageDuelOption == GameOptions::EnabledMage)
		m_mageCard = MageCard();
	else
		m_mageCard = std::nullopt;
}
Colours Player::GetPlayerColor() const
{
	return m_playerColor;
}

bool Player::GetIllusionUsage() const
{
	return m_illusionUsage;
}

bool Player::GetEterCardUsage() const
{
	return m_eterCardUsage;
}

const Hand& Player::GetHandCards() const
{
	return m_handCards;
}

const CardCounter& Player::GetRemaningCounter()
{
	return m_remainingCounter;
}

Hand& Player::GetRemovedCards()
{
	return m_removedCards;
}

void Player::SetEterCardUsage(bool eterCardUsage)
{
	m_eterCardUsage = eterCardUsage;
}

void Player::SetPlayerColor(Colours playerColor)
{
	m_playerColor = playerColor;
}

void Player::SetIllusionUsage(bool illusionUsage)
{
	m_illusionUsage = illusionUsage;
}

void Player::SetHandCards(const Hand& handCards)
{
	m_handCards = handCards;
}

//1 if unsucessfull, 0 updates was completed
int Player::UpdateCard(const MinionCard& card, int cnt)
{
	//bounds
	if (cnt != 1 && cnt != -1)
		return 1;
	//change if found
	if (m_handCards.find(card) == m_handCards.end())
		return 1;
	m_handCards[card] += cnt;
	if (m_handCards[card] == 0)
		m_handCards.erase(card);
	return 0;
}

void Player::updateCover(uint16_t x, uint16_t y, CoveredSet& coveredCardSet, ResizeableMatrix& board)
{
	if (board[x][y].size() == 1)
		return;

	int pos = board[x][y].size() - 2;
	MinionCard& lastPlaced = board[x][y].back();
	MinionCard& coveredCard = board[x][y][pos];
	if (lastPlaced.GetColor() != coveredCard.GetColor())
		coveredCardSet.emplace(x, y, pos);
}

void Player::applyTansformToCovered(Player& p1, Player& p2, CardStack& stack, uint16_t oldX, uint16_t oldY, uint16_t newX, uint16_t newY)
{
	auto& p1Covered = p1.getCovered();
	auto& p2Covered = p2.getCovered();

	CoveredSet p1Moved;
	CoveredSet p2Moved;

	for (int i = 0; i < stack.size() - 1; i++) {
		position toFind{ oldX, oldY, i };
		auto currCardColor = stack[i].GetColor();
		if (currCardColor == Colours::RED) {
			p1Moved.insert({ newX, newY, i });
			p1Covered.erase(p1Covered.find(toFind));
		}
		else {
			p2Moved.insert({newX, newY, i});
			p2Covered.erase(p2Covered.find(toFind));
		}
	}
	for (auto& newPosition : p1Moved) {
		p1Covered.insert(newPosition);
	}
	for (auto& newPosition : p2Moved) {
		p2Covered.insert(newPosition);
	}
}

void Player::ReturnStackToHand(Hand& h1, Hand& h2, CardStack& stack)
{
	Hand& currHand = h1;
	for (auto& card : stack) {
		if (card.GetColor() == Colours::RED)
			currHand = h1;
		else
			currHand = h2;

		if (currHand.find(card) != currHand.end())
			currHand[card]++;
		else
			currHand.insert({ card, 1 });
	}
}

void Player::generateTrainingModeHand()
{
	m_handCards.clear();

	//creating minion cards with their value and color
	MinionCard combatCard1(1, m_playerColor, false);
	MinionCard combatCard2(2, m_playerColor, false);
	MinionCard combatCard3(3, m_playerColor, false);
	MinionCard combatCard4(4, m_playerColor, false);

	m_handCards.emplace(combatCard1, 2);
	m_handCards.emplace(combatCard2, 2);
	m_handCards.emplace(combatCard3, 2);
	m_handCards.emplace(combatCard4, 1);
}

void Player::generateHand()
{
	m_handCards.clear();

	m_handCards.emplace(MinionCard{ 1, m_playerColor, false }, 2);
	m_handCards.emplace(MinionCard{ 2, m_playerColor, false }, 3);
	m_handCards.emplace(MinionCard{ 3, m_playerColor, false }, 3);
	m_handCards.emplace(MinionCard{ 4, m_playerColor, false }, 1);
	m_handCards.emplace(MinionCard{ 1, m_playerColor, true }, 1); //eter card has the value 1 
}

void Player::GenerateHand(bool training)
{
	int offset = int16_t(!training);

	m_remainingCounter.emplace(0, offset);
	m_remainingCounter.emplace(1, 2);
	m_remainingCounter.emplace(2, 2 + offset);
	m_remainingCounter.emplace(3, 2 + offset);
	m_remainingCounter.emplace(4, 1);

	m_remainingCards[0].resize(offset);
	m_remainingCards[1].resize(2);
	m_remainingCards[2].resize(2 + offset);
	m_remainingCards[3].resize(2 + offset);
	m_remainingCards[4].resize(1);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < m_remainingCards[i].size(); j++)
		{
			m_remainingCards[i][j] = std::move(MinionCard((i == 0) ? 1 : i, m_playerColor, i == 0));
			continue;
		}
	}
}

MinionCard* Player::GetLastMinionCardPlayed() const
{
	return m_lastMinionCardPlayed;
}

MinionCard* Player::GetIllusionCard() const
{
	return m_illusionCard;
}

CoveredSet& Player::getCovered()
{
	return this->m_coveredCardSet;
}

bool Player::CheckCoveredPopulation()
{
	return m_coveredCardSet.empty();
}

bool Player::CheckCoveredProperty(int16_t _x, int16_t _y, int16_t _pos)
{
	return m_coveredCardSet.find({ _x, _y, _pos }) != m_coveredCardSet.end();
}

MinionCard&& Player::PlayCard(int16_t _val) 
{
	m_lastPlayedCard.push_back(&m_remainingCards[_val].back());

	UpdateCard(_val, CardAction::REMOVE);

	return std::move(m_remainingCards[_val].back());
}

MinionCard&& Player::ReplayCard(int16_t _val)
{
	m_lastPlayedCard.push_back(&m_removed_Cards[_val].back());

	MinionCard toMove = std::move(m_removed_Cards[_val].back());

	UpdateCard(_val, CardAction::FORGET);

	return std::move(toMove);
}

void Player::ReturnCard(MinionCard&& _toMove)
{
	//weak_ptr shinanigans pt last placed sau altceva - tinem pointeri normali dar trebuie sa schimbam 
	UpdateCard(_toMove.GetValue(), CardAction::RETURN);

	m_remainingCards[_toMove.GetValue()].push_back(_toMove);
}

void Player::KillCard(MinionCard&& _toMove)
{
	/*for (int i = 0; i < m_lastPlayedCard.size(); i++)
		if (m_lastPlayedCard[i].GetValue() == _toMove.GetValue())
		{
			m_lastPlayedCard.erase(m_lastPlayedCard.begin() + i);
			break;
		}*/

	UpdateCard(_toMove.GetValue(), CardAction::REMEMBER);

	m_removed_Cards[_toMove.GetValue()].push_back(_toMove);
}

void Player::UpdateCard(int16_t _val, CardAction _action)
{
	switch (_action)
	{
	case CardAction::RETURN:
		m_remainingCounter[_val]++;
		break;
	case CardAction::REMOVE:
		m_remainingCounter[_val]--;
		m_remainingCards[_val].pop_back();
		break;
	case CardAction::REMEMBER:
		m_removedCounter[_val]++;
		break;
	case CardAction::FORGET:
		m_removedCounter[_val]--;
		m_removed_Cards[_val].pop_back();
	default:
		break;
	}
}

void Player::CoverCard(MinionCard& _card)
{
	m_coveredCards.push_back(&_card);
}

void Player::UncoverCard(MinionCard& _card)
{
	/*for (int i = 0; i < m_coveredCards.size(); i++)
		if (&m_coveredCards[i] == &_card) {
			m_coveredCards.erase(m_coveredCards.begin() + i);
			break;
		}*/

}

bool Player::HasCardOfValue(uint16_t value)
{
	return m_remainingCounter[value] > 0;
}

void Player::SetIllusionCard(MinionCard* illusionCard)
{
	m_illusionCard = illusionCard;
}

void Player::SetLastMinionCardPlayed(MinionCard* cardPlayed)
{
	m_lastMinionCardPlayed = cardPlayed;
}

bool Player::placeMinionCardFromHand(MinionCard& card)
{
	if (m_handCards.at(card) != 0)
	{
		card.SetBelongsTo(m_playerColor);
		m_handCards[card]--;
		m_lastMinionCardPlayed = &card;
		return true;
	}
	else
	{
		return false;
	}
}

void Player::returnMinionCardToHand(const MinionCard& card)
{
	if (m_handCards.find(card) != m_handCards.end())
		m_handCards[card]++;
	else
		m_handCards.emplace(card, 1);
}

void Player::returnLastMinionCardToHand()
{
	m_handCards[(*m_lastMinionCardPlayed)]++;
}

void Player::addToRemovedCards(const MinionCard& card)
{
	if (m_removedCards.find(card) != m_removedCards.end())
		m_removedCards[card]++;
	else
		m_removedCards.emplace(card, 1);
}

bool Player::placeMinionCardFromRemovedCard(const MinionCard& card)
{
	bool placed = false;
	if (m_removedCards.find(card) != m_removedCards.end())
	{
		if (m_removedCards[card] != 0)
		{
			m_removedCards[card]--;
			placed = true;
		}
	}
	return placed;
}

bool Player::printCoveredCards(ResizeableMatrix& matrix)
{
	if (m_coveredCardSet.size() == 0) {
		std::cout << "You have no covered cards..\n";
		return false;
	}
	int i = 0;
	std::cout << "Covered cards:\n";
	for (auto& card :m_coveredCardSet) {
		auto [x, y, posInStack] = card;

		std::cout << ++i << ". " <<"position:"<< posInStack << "," 
			<<"color"<<matrix[x][y][posInStack].GetColor()<<","
			<<"value"<< matrix[x][y][posInStack].GetValue() << "\n";
	}
	return true;
}

void Player::printHandCards()
{
	std::cout << "\nYour Hand:\n";
	for (auto& i : m_handCards) 
	{
		if (i.first.GetIsEterCard() && m_eterCardUsage == false)
			std::cout << "Eter Card: " << i.second << " Left\n";
		else 
			std::cout << "Minion Card " << i.first.GetValue() << ": " << i.second << " Left\n";
	}
}

std::ostream& operator<<(std::ostream& os, const position& posTuple)
{
	os << "{" << std::get<0>(posTuple) << ", " << std::get<0>(posTuple) << ": " << std::get<0>(posTuple) << "}";

	return os;
}
