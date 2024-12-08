#pragma once
#include <cstdint>
#include <iostream>


enum class CommonErrors : int16_t {
	NO_ERRORS,
	OUTSIDE_BOUNDS,
	ETER_PROPERTY_VIOLATION,
	ILLUSION_PROPERTY_VIOLATION,
	NEEDS_EMPTY_SPACE,
	INVALID_LINE_TYPE,
	INVALID_DIRECTION,
	INCOMPLETE_LINE_STRUCTURE,
	IDENTICAL_COORDINATES,

	EMPTY_STACK,
	STACK_HEIGHT_TOO_SMALL,
	NEGATIVE_CARD_VALUE,

	INVALID_CARD_TYPE,
	INVALID_CARD_VALUE,
	NOT_ENEMY_CARD,
	NOT_ACTIVE_CARD,
	NOT_ILLUSION,
	NO_CARDS_OF_VALUE,

	ADJACENT_OUTSIDE_BOUNDS,
	ADJACENT_SPACES_EMPTY

};

void ErrorMesageHuricane(CommonErrors message);
void ErrorMessageWhirlpool(CommonErrors message);
void ErrorMessageFlame(CommonErrors message);
void ErrorMessageFire(CommonErrors message);
void ErrorMessageAsh(CommonErrors message);
void ErrorMessageSpark(CommonErrors message);
void ErrorMessageSquall(CommonErrors message);
void ErrorMessageGust(CommonErrors message);
void ErrorMessageMirage(CommonErrors message);
void ErrorMessagestorm(CommonErrors message);
void ErrorMessageTide(CommonErrors message);
void ErrorMessageMist(CommonErrors message);
void ErrorMessageWave(CommonErrors message);