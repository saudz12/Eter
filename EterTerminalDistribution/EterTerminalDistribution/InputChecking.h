#pragma once

/// <summary>
/// Add here input cheking for each function that requires input from the user.
/// Error handling by returning integers --OR ENUMS SO WE KNOW EXACTLY WHAT WE RETURN!!!
/// </summary>
#include "functionsElementalCards.h"
#include "functionsMageCards.h"
#include "ErrorPrints.h"

CommonErrors CheckHurricaneInput(Board& _board, uint16_t _lineCnt, LineType _type, Directions _direction);

CommonErrors CheckWhirlpool(Board& _board, uint16_t _x1, uint16_t _y1, uint16_t _x2, uint16_t _y2, Preference _preference);

CommonErrors checkFuncFlame(Board& _board, int16_t _xi, int16_t _yi, Player& _player, int16_t _val, int16_t _xp, int16_t _yp);

CommonErrors checkFuncFire(Board&, int16_t);

CommonErrors checkFuncAsh(Board&, const MinionCard&, int16_t, int16_t);

CommonErrors checkFuncSpark(Board&, int16_t, int16_t, int16_t, int16_t);

CommonErrors checkFuncSquall(Board&, int16_t, int16_t, Player&);

CommonErrors checkFuncGust(Board&, int16_t, int16_t, int16_t, int16_t);

CommonErrors checkFuncMirage(Board&, int16_t, int16_t);

CommonErrors checkFuncStorm(Board&, int16_t, int16_t);

CommonErrors checkFuncTide(Board&, int16_t, int16_t, int16_t, int16_t);

CommonErrors checkFuncMist(Board&, Player&, int16_t, int16_t, MinionCard&);

CommonErrors checkFuncWave(Board&, int16_t, int16_t, MinionCard);

CommonErrors checkFuncBlizzard();

CommonErrors checkFuncWaterfall(Board&, int16_t);

CommonErrors checkFuncSupport(Board&, int16_t, int16_t);

CommonErrors checkFuncEarthquake(Board&);

CommonErrors checkFuncCrumble(Board&, int16_t, int16_t);

CommonErrors checkFuncBorder(Board&, int16_t, int16_t);

CommonErrors checkFuncAvalanche(Board& _board, int16_t _x1, int16_t _y1, int16_t _x2, int16_t _y2, Directions _direction);

CommonErrors checkFuncRock(Board&, int16_t, int16_t, MinionCard&);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CommonErrors checkFuncFireMage1(Board& _board, Player& _player, int16_t _x, int16_t _y, int16_t _pos);

CommonErrors checkFuncFireMage2(Board& _board, Player& _player, int16_t _line, LineType _type);

CommonErrors checkFuncEarthMage1(Board& _board, Player& _user, int16_t _x, int16_t _y, int16_t _val);

CommonErrors checkFuncEarthMage2(Board& _board, int16_t _x, int16_t _y);

CommonErrors checkFuncAirMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);

CommonErrors checkFuncAirMage2(Board& _board, int16_t _x, int16_t _y, Colours _color);

CommonErrors checkFuncWaterMage1(Board& _board, Colours _color, int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);

CommonErrors checkFuncWaterMage2(Board& _board, MarginType _margin);