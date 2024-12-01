#pragma once
#include <cstdint>
#include <iostream>

//Shared
constexpr int16_t NO_ERRORS = 0;
constexpr int16_t OUTSIDE_BOUNDS = -1;
constexpr int16_t ETER_PROPERTY_VIOALTION = -2;
constexpr int16_t EMPTY_SPACE = -3;
constexpr int16_t INVALID_LINE_TYPE = -4;
constexpr int16_t INVALID_DIRECTION = -5;

//Hurricane span
constexpr int16_t INVALID_LINE_STRUCTURE = 2;

//Whirlpool
constexpr int16_t ADJACENT_OUTSIDE_BOUNDS = 1;
constexpr int16_t ADJACENT_SPACES_EMPTY = 2;

void ErrorMesageHuricane(int message);
void ErrorMessageWhirlpool(int message);


