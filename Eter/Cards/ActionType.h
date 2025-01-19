#pragma once
#include <cstdint>
#include "Card.h"

enum class CARD_API ActionCard : uint16_t {
	ControlledExplosion=0,
	Destruction,
	Flame,
	Fire,
	Ash,
	Spark,
	Squall,
	Gale,
	Hurricane,
	Gust,
	Mirage,
	Storm,
	Tide,
	Mist,
	Wave,
	Whirlpool,
	Blizzard,
	Waterfall,
	Support,
	Earthquake,
	Crumble,
	Border,
	Avalanche,
	Rock,

	Default,

	FireMage1,
	FireMage2,
	EarthMage1,
	EarthMage2,
	AirMage1,
	AirMage2,
	WaterMage1,
	WaterMage2
};

ActionCard CARD_API GetElementalCard(int16_t _val);
ActionCard CARD_API GetMageCard(int16_t _val);
