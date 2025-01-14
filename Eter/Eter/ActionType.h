#pragma once
#include <cstdint>

enum class ActionCard : uint16_t {
	ControlledExplosion = 0,
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

ActionCard GetElementalCard(int16_t _val);
ActionCard GetMageCard(int16_t _val);
