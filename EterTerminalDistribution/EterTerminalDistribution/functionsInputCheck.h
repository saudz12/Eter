#pragma once

#include "ExplosionCard.h"
#include "MoveLaterToGameClass.h"

using handCard = std::unordered_map<MinionCard, uint16_t>;


uint16_t checkFuncFlame(Board&, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard&, Player&);

uint16_t checkFuncFire(Board&, uint16_t);

uint16_t checkFuncAsh(Board&,const MinionCard&, uint16_t, uint16_t);

uint16_t checkFuncSpark(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

uint16_t checkFuncSquall(Board&, uint16_t, uint16_t);

uint16_t checkFuncHurricane(Board&, hand&, hand&);

uint16_t checkFuncGust(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

uint16_t checkFuncMirage(Board&, uint16_t, uint16_t, const MinionCard&);

uint16_t checkFuncStorm(Board&, uint16_t, uint16_t);

uint16_t checkFuncTide(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

uint16_t checkFuncMist(Board&, Player&, uint16_t, uint16_t, MinionCard&);

uint16_t checkFuncWave(Board&, uint16_t, uint16_t, MinionCard);

uint16_t checkFuncWhirlpool(Board&, uint16_t, uint16_t);

uint16_t checkFuncBlizzard(line&);

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