#pragma once
#include <cstdint>
#include <iostream>


enum class CommonErrors : int16_t {
	_NO_ERRORS,
	_OUTSIDE_BOUNDS,
	_ETER_PROPERTY_VIOLATION,
	_ILLUSION_PROPERTY_VIOLATION,
	_HOLE_PROPERTY_VIOLATION,
	_NEEDS_EMPTY_SPACE,
	_INVALID_LINE_TYPE,
	_INVALID_DIRECTION,
	_INCOMPLETE_LINE_STRUCTURE,
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

	_ADJACENT_OUTSIDE_BOUNDS,
	_ADJACENT_SPACES_EMPTY

};

void ErrorMesageHuricane(CommonErrors _message);
void ErrorMessageWhirlpool(CommonErrors _message);
void ErrorMessageFlame(CommonErrors _message);
void ErrorMessageFire(CommonErrors _message);
void ErrorMessageAsh(CommonErrors _message);
void ErrorMessageSpark(CommonErrors _message);
void ErrorMessageSquall(CommonErrors _message);
void ErrorMessageGust(CommonErrors _message);
void ErrorMessageMirage(CommonErrors _message);
void ErrorMessagestorm(CommonErrors _message);
void ErrorMessageTide(CommonErrors _message);
void ErrorMessageMist(CommonErrors _message);
void ErrorMessageWave(CommonErrors _message);

void ErrorMessageFireMage1(CommonErrors _message);
void ErrorMessageEarthMage1(CommonErrors _message);
void ErrorMessageEarthMage2(CommonErrors _message);
