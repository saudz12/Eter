#pragma once

/// <summary>
/// Add here input cheking for each function that requires input from the user.
/// Error handling by returning integers
/// </summary>
#include "functionsElementalCards.h"
#include "ErrorPrints.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction);

const int CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference);

int16_t checkFuncFlame(Board&, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard&, Player&);

int16_t checkFuncFire(Board&, uint16_t);

int16_t checkFuncAsh(Board&, const MinionCard&, uint16_t, uint16_t);

int16_t checkFuncSpark(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

int16_t checkFuncSquall(Board&, uint16_t, uint16_t);

int16_t checkFuncGust(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

int16_t checkFuncMirage(Board&, uint16_t, uint16_t, const MinionCard&);

int16_t checkFuncStorm(Board&, uint16_t, uint16_t);

int16_t checkFuncTide(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

uint16_t checkFuncMist(Board&, Player&, uint16_t, uint16_t, MinionCard&);

int16_t checkFuncWave(Board&, uint16_t, uint16_t, MinionCard);

uint16_t checkFuncBlizzard(Line&);

uint16_t checkFuncWaterfall(Board&, uint16_t);

uint16_t checkFuncSupport(Board&, uint16_t, uint16_t);

uint16_t checkFuncEarthquake(Board&);

uint16_t checkFuncCrumble(Board&, uint16_t, uint16_t);

uint16_t checkFuncBorder(Board&, uint16_t, uint16_t);

uint16_t checkFuncAvalanche(Board&, uint16_t, uint16_t, uint16_t, uint16_t, char);

uint16_t checkFuncRock(Board&, uint16_t, uint16_t, MinionCard&);

uint16_t checkFuncFireMage1(Board&, Player&);

uint16_t checkFuncFireMage2(Board&, Player&);

uint16_t checkFuncEarthMage1(Board&, Player&, uint16_t, uint16_t);

uint16_t checkFuncEarthMage2(Board&);

uint16_t checkFuncAirMage1(Board&, Player& pl);

uint16_t checkFuncAirMage2(Board&, uint16_t, uint16_t);

uint16_t checkFuncWaterMage1(Board&, Player&);

uint16_t checkFuncWaterMage2(Board& board, char color, Player& pl);