#pragma once

/// <summary>
/// Add here input cheking for each function that requires input from the user.
/// Error handling by returning integers
/// </summary>

constexpr auto NO_ERRORS = 0;
constexpr auto OUTSIDE_BOUNDS = -1;
constexpr auto INVALID_LINE_TYPE = 1;
constexpr auto INVALID_LINE_STRUCTURE = 2;
constexpr auto INVALID_DIRECTION = 3;
constexpr auto ETER_PROPERTY_VIOALTION = 4;

#include "functionsElementalCards.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction);