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

//Flame
constexpr int16_t FAILED_FLAME_CARD_PLACEMENT = 1;

//Fire/Ash
constexpr int16_t INVALID_CARD_VALUE = 1;

//Squall
constexpr int16_t FAILED_ON_ILLUSION = 3;

//Gust
constexpr int16_t IDENTICAL_COORDINATES = 1;
constexpr int16_t VALUE_TOO_GREAT = 2;

//Mirage
constexpr int16_t NOT_ILLUSION = 1;

//Storm
constexpr int16_t INSUFFICIENT_STACK_HEIGHT = 1;

//Mist
constexpr int16_t FAILED_MIST_CARD_PLACEMENT = 1;

enum class CommonErrors : int16_t {
	NO_ERRORS,
	OUTSIDE_BOUNDS,
	ETER_PROPERTY_VIOALTION,
	EMPTY_SPACE,
	INVALID_LINE_TYPE,
	INVALID_DIRECTION,
};

enum class HurricangeErrors : int16_t {
	INVALID_LINE_STRUCTURE
};

enum class WhirlpoolErrors : int16_t {
	ADJACENT_OUTSIDE_BOUNDS,
	ADJACENT_SPACES_EMPTY
};

void ErrorMesageHuricane(int message);
void ErrorMessageWhirlpool(int message);
void ErrorMessageFlame(int message);
void ErrorMessageFire(int message);
void ErrorMessageAsh(int message);
void ErrorMessageSpark(int message);
void ErrorMessageSquall(int message);
void ErrorMessageGust(int message);
void ErrorMessageMirage(int message);
void ErrorMessagestorm(int message);
void ErrorMessageTide(int message);
void ErrorMessageMist(int message);
void ErrorMessageWave(int message);