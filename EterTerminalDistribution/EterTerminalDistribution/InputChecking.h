#pragma once

/// <summary>
/// Add here input cheking for each function that requires input from the user.
/// Error handling by returning integers --OR ENUMS SO WE KNOW EXACTLY WHAT WE RETURN!!!
/// </summary>
#include "functionsElementalCards.h"
#include "ErrorPrints.h"

CommonErrors CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction);

CommonErrors CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference);

CommonErrors checkFuncFlame(Board&, int16_t x1, int16_t y1, int16_t x2, int16_t y2, const MinionCard&, Player&);

CommonErrors checkFuncFire(Board&, int16_t);

CommonErrors checkFuncAsh(Board&, const MinionCard&, int16_t, int16_t);

CommonErrors checkFuncSpark(Board&, int16_t, int16_t, int16_t, int16_t);

CommonErrors checkFuncSquall(Board&, int16_t, int16_t, Player);

CommonErrors checkFuncGust(Board&, int16_t, int16_t, int16_t, int16_t);

CommonErrors checkFuncMirage(Board&, int16_t, int16_t, const MinionCard&);

CommonErrors checkFuncStorm(Board&, int16_t, int16_t);

CommonErrors checkFuncTide(Board&, int16_t, int16_t, int16_t, int16_t);

CommonErrors checkFuncMist(Board&, Player&, int16_t, int16_t, MinionCard&);

CommonErrors checkFuncWave(Board&, int16_t, int16_t, MinionCard);

CommonErrors checkFuncBlizzard(Line&);

CommonErrors checkFuncWaterfall(Board&, int16_t);

CommonErrors checkFuncSupport(Board&, int16_t, int16_t);

CommonErrors checkFuncEarthquake(Board&);

CommonErrors checkFuncCrumble(Board&, int16_t, int16_t);

CommonErrors checkFuncBorder(Board&, int16_t, int16_t);

CommonErrors checkFuncAvalanche(Board&, int16_t, int16_t, int16_t, int16_t, char);

CommonErrors checkFuncRock(Board&, int16_t, int16_t, MinionCard&);

CommonErrors checkFuncFireMage1(Board& _board, Player& _player, int16_t _x, int16_t _y, int16_t _pos);

CommonErrors checkFuncFireMage2(Board& _board, Player& _player, int16_t _line, char _type);

CommonErrors checkFuncEarthMage1(Board& _board, Player& _user, int16_t _x, int16_t _y, int16_t _val);

CommonErrors checkFuncEarthMage2(Board& _board, int16_t _x, int16_t _y);

CommonErrors checkFuncAirMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);

CommonErrors checkFuncAirMage2(Board&, int16_t, int16_t);

CommonErrors checkFuncWaterMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);

CommonErrors checkFuncWaterMage2(Board& _board, char _margin);