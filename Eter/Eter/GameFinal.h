#pragma once
#include <cstdint>
#include <fstream>

#include "Board.h"
#include "InputChecking.h"
#include "json.hpp"


using PowerUsage = std::tuple<bool, ActionCard, uint16_t>;
using json = nlohmann::json;

enum class PowerSelect : int16_t {
	First,
	Second,
};

class GameFinal {
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
	bool m_canPlayExplosion;
	bool m_wasExplosionPlayed;

	PowerUsage m_redMage;
	PowerUsage m_blueMage;
	PowerUsage m_elemental1;
	PowerUsage m_elemental2;

	void FindPower(ActionCard identif);

public:
	GameFinal();
	GameFinal(int16_t _maxBoardSize,
		GameOptions _enabledEter, GameOptions _enabledIllusion,
		GameOptions _enabledMage, GameOptions _enabledElemental,
		GameOptions _enabledTournament, GameOptions _enabledTimed);

#pragma region turn_logic
	void AdvanceAction();
	void EndTurn();
	void ResetRound();
#pragma endregion

#pragma region action_logic
	bool PlaceCard(int16_t _x, int16_t _y, int16_t _val);
	void PlayElemental(PowerSelect select);
	void PlayMage();
	bool CheckWin(); //cheking everything
	bool CheckWin(int16_t _x, int16_t _y); //singlechecking
	IllusionErrors PlaceIllusion(int16_t _x, int16_t _y, int16_t _val);
#pragma endregion

#pragma region print_api
	void PrintBoard(bool _debug = false);
	void PrintActiveHand();
#pragma endregion
	ExplosionCard generateNewExplosionCard();

	std::shared_ptr<Player> getPlayer1() const;
	std::shared_ptr<Player> getPlayer2() const;
	int16_t getFirstElementalCardId() const;
	int16_t getSecondElementalCardId() const;
	Board& GetBoard() { return *m_board; }
	bool GetCanPlayExplosion() const { return m_canPlayExplosion; }
	
	bool tryToApplyExplosionOnBoard(ExplosionCard& card);
	std::vector<MarginType> applyExplosionOnBoard(const ExplosionCard& card);

	void SaveCurrentToJson();
	template <typename T1, typename T2>
	json serializePairAsObject(const std::pair<T1, T2>& pair);

	template <typename Tuple, std::size_t... Indices>
    void serializeTupleHelper(const Tuple& tuple, json& j, std::index_sequence<Indices...>);

	template <typename... Args>
	json serializeTupleAsObject(const std::tuple<Args...>& tuple);

	void LoadFromJson();

	template <typename T1, typename T2>
	std::pair<T1, T2> deserializePair(const json& j);

	template <typename... Args>
	std::tuple<Args...> deserializeTuple(const json& j);

	template <typename... Args, std::size_t... Indices>
	std::tuple<Args...> deserializeTupleHelper(const json& j, std::index_sequence<Indices...>);
};

template <typename T1, typename T2>
inline json GameFinal::serializePairAsObject(const std::pair<T1, T2>& pair) {
	return { {"first", pair.first}, {"second", pair.second} };
}

template <typename Tuple, std::size_t... Indices>
inline void GameFinal::serializeTupleHelper(const Tuple& tuple, json& j, std::index_sequence<Indices...>) {
	((j["element" + std::to_string(Indices)] = std::get<Indices>(tuple)), ...);
}

template <typename... Args>
inline json GameFinal::serializeTupleAsObject(const std::tuple<Args...>& tuple) {
	json j;
	serializeTupleHelper(tuple, j, std::index_sequence_for<Args...>{});
	return j;
}

template <typename T1, typename T2>
inline std::pair<T1, T2> GameFinal::deserializePair(const json& j) {
	return { j.at("first").get<T1>(), j.at("second").get<T2>() };
}

template <typename... Args>
inline std::tuple<Args...> GameFinal::deserializeTuple(const json& j) {
	return deserializeTupleHelper<Args...>(j, std::index_sequence_for<Args...>{});
}

template <typename... Args, std::size_t... Indices>
inline std::tuple<Args...> GameFinal::deserializeTupleHelper(const json& j, std::index_sequence<Indices...>) {
	return std::make_tuple(j.at("element" + std::to_string(Indices)).get<Args>()...);
}
