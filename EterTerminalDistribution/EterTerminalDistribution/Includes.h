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
#include <memory>

constexpr auto ID_ROW = "R";
constexpr auto ID_COLUMN = "C";
constexpr auto DIR_LEFT = "L";
constexpr auto DIR_RIGHT = "R";
constexpr auto DIR_UP = "U";
constexpr auto DIR_DOWN = "D";

enum class Colours : int16_t {
	RED,
	BLUE,
	INVALID_COL
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
	TYPE_COLUMN,
	TYPE_ROW,
	TYPE_INVALID_LINE
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

Directions GetDirection(char d);

std::ostream& operator<<(std::ostream& os, const Colours& col);