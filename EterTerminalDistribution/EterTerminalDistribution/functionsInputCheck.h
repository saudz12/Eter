#pragma once


#include "ExplosionCard.h"
#include "MoveLaterToGameClass.h"

using handCard = std::unordered_map<MinionCard, uint16_t>;





int checkFuncFlame(Board&, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const MinionCard&, Player&);

int checkFuncFire(Board&, uint16_t);

int checkFuncAsh(Board&,const MinionCard&, uint16_t, uint16_t);

int checkFuncSpark(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

int checkFuncSquall(Board&, uint16_t, uint16_t);


int checkFuncHurricane(Board&, hand&, hand&);

int checkFuncGust(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

int checkFuncMirage(Board&, uint16_t, uint16_t, const MinionCard&);

int checkFuncStorm(Board&, uint16_t, uint16_t);

int checkFuncTide(Board&, uint16_t, uint16_t, uint16_t, uint16_t);

int checkFuncMist(Board&, Player&, uint16_t, uint16_t, MinionCard&);

int checkFuncWave(Board&, uint16_t, uint16_t, MinionCard);

int checkFuncWhirlpool(Board&, uint16_t, uint16_t);

int checkFuncBlizzard(line&);

int checkFuncWaterfall(Board&, uint16_t);

int checkFuncSupport(Board&, uint16_t, uint16_t);

int checkFuncEarthquake(Board&);

int checkFuncCrumble(Board&, uint16_t, uint16_t);

int checkFuncBorder(Board&, uint16_t, uint16_t);

int checkFuncAvalanche(Board&, uint16_t, uint16_t, uint16_t, uint16_t, char);

int checkFuncRock(Board&, uint16_t, uint16_t, MinionCard&);

int checkFuncFireMage1(Board&, Player&);

int checkFuncFireMage2(Board&, Player&);

int checkFuncEarthMage1(Board&, Player&, uint16_t, uint16_t);

int checkFuncEarthMage2(Board&);

int checkFuncAirMage1(Board&, Player& pl);

int checkFuncAirMage2(Board&, uint16_t, uint16_t);

int checkFuncWaterMage1(Board&, Player&);

int checkFuncWaterMage2(Board& board, char color, Player& pl);