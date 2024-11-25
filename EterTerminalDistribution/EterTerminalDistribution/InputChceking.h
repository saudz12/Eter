#pragma once

/// <summary>
/// Add here input cheking for each function that requires input from the user.
/// Error handling by returning integers
/// </summary>

//Shared
constexpr uint16_t NO_ERRORS = 0;
constexpr uint16_t OUTSIDE_BOUNDS = -1;
constexpr uint16_t ETER_PROPERTY_VIOALTION = -2;
constexpr uint16_t EMPTY_SPACE = -3;

//Hurricane span
constexpr uint16_t INVALID_LINE_TYPE = 1;
constexpr uint16_t INVALID_LINE_STRUCTURE = 2;
constexpr uint16_t INVALID_DIRECTION = 3;

//Whirlpool
constexpr uint16_t ADJACENT_OUTSIDE_BOUNDS = 1;
constexpr uint16_t ADJACENT_SPACES_EMPTY = 1;

#include "functionsElementalCards.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction);

const int CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype);