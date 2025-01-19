#pragma once
#include <iostream>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <tuple>
#include <string>
#include <cstdint>
#include <deque>
#include <stack>
#include <vector>
#include <memory>
#include <random>
#include <ranges>
#include <algorithm>
#include <optional>
#include "json.hpp"
#include <fstream>
#include "../Cards/MinionCard.h"
#include "../Cards//ActionType.h"


using json = nlohmann::json;

constexpr auto ID_ROW = "R";
constexpr auto ID_COLUMN = "C";
constexpr auto DIR_LEFT = "L";
constexpr auto DIR_RIGHT = "R";
constexpr auto DIR_UP = "U";
constexpr auto DIR_DOWN = "D";

enum class GameOptions : int16_t
{
	EnabledEter,
	DisabledEter,
	EnabledIllusion,
	DisabledIllusion,
	EnabledMage,
	DisabledMage,
	EnabledElemental,
	DisabledElemental,
	EnabledTimed,
	DisabledTimed,
	EnabledTournament,
	DisabledTournament
};

Colours GetColour(char c);
char GetColour(Colours c);

enum class ColorActions : int16_t {
	_RED_ADD,
	_BLUE_ADD,
	_RED_ADD_BLUE_DEC,
	_BLUE_ADD_RED_DEC,
	_RED_DEC,
	_BLUE_DEC,
	_ZERO
};

enum class LineType : int16_t {
	TYPE_ROW,
	TYPE_COLUMN,
	_INVALID_LINE_TYPE
};

LineType GetLineType(char t);

enum class Directions : int16_t
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	INVALID_DIR
};

static enum class CommonErrors : int16_t {
	_NO_ERRORS,
	_OUTSIDE_BOUND,
	_ETER_PROPERTY_VIOLATION,
	_ILLUSION_PROPERTY_VIOLATION,
	_HOLE_PROPERTY_VIOLATION,
	_NEEDS_EMPTY_SPACE,
	_INVALID_LINE_TYPE,
	_INVALID_DIRECTION,
	_INCOMPLETE_LINE_STRUCTURE,
	_LINE_DOES_NOT_CONTAIN_COLOR,
	_IDENTICAL_COORDINATES,

	_EMPTY_STACK,
	_POPULATED_STACK,
	_STACK_HEIGHT_TOO_SMALL,
	_NEGATIVE_CARD_VALUE,

	_INVALID_CARD_TYPE,
	_INVALID_CARD_VALUE,
	_NOT_ENEMY_CARD,
	_NOT_ACTIVE_CARD,
	_NOT_ILLUSION,
	_NO_CARDS_OF_VALUE,

	_NO_COVERED_CARDS,
	_MAX_BOARD_SIZE,

	_ADJACENT_OUTSIDE_BOUNDS,
	_ADJACENT_SPACES_EMPTY,
	_NOT_ADJACENT

};

Directions GetDirection(char d);

std::ostream& operator<<(std::ostream& os, const Colours& col);
std::ostream& operator<<(std::ostream& out, const MinionCard& card);