#pragma once

/// <summary>
/// Add here input cheking for each function that requires input from the user.
/// Error handling by returning integers --OR ENUMS SO WE KNOW EXACTLY WHAT WE RETURN!!!
/// </summary>
#include "functionsElementalCards.h"
#include "ErrorPrints.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction);

const int CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference);

int16_t checkFuncFlame(Board&, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const MinionCard&, Player&);

int16_t checkFuncFire(Board&, int16_t);

int16_t checkFuncAsh(Board&, const MinionCard&, int16_t, int16_t);

int16_t checkFuncSpark(Board&, int16_t, int16_t, int16_t, int16_t);

int16_t checkFuncSquall(Board&, int16_t, int16_t);

int16_t checkFuncGust(Board&, int16_t, int16_t, int16_t, int16_t);

int16_t checkFuncMirage(Board&, int16_t, int16_t, const MinionCard&);

int16_t checkFuncStorm(Board&, int16_t, int16_t);

int16_t checkFuncTide(Board&, int16_t, int16_t, int16_t, int16_t);

int16_t checkFuncMist(Board&, Player&, int16_t, int16_t, MinionCard&);

int16_t checkFuncWave(Board&, int16_t, int16_t, MinionCard);

int16_t checkFuncBlizzard(Line&);

int16_t checkFuncWaterfall(Board&, int16_t);

int16_t checkFuncSupport(Board&, int16_t, int16_t);

int16_t checkFuncEarthquake(Board&);

int16_t checkFuncCrumble(Board&, int16_t, int16_t);

int16_t checkFuncBorder(Board&, int16_t, int16_t);

int16_t checkFuncAvalanche(Board&, int16_t, int16_t, int16_t, int16_t, char);

int16_t checkFuncRock(Board&, int16_t, int16_t, MinionCard&);

int16_t checkFuncFireMage1(Board&, Player&);

int16_t checkFuncFireMage2(Board&, Player&);

int16_t checkFuncEarthMage1(Board&, Player&, int16_t, int16_t);

int16_t checkFuncEarthMage2(Board&);

int16_t checkFuncAirMage1(Board&, Player& pl);

int16_t checkFuncAirMage2(Board&, int16_t, int16_t);

int16_t checkFuncWaterMage1(Board&, Player&);

int16_t checkFuncWaterMage2(Board& board, char color, Player& pl);