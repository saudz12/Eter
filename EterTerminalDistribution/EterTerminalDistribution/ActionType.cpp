#include "ActionType.h"

ActionCard GetElementalCard(int16_t _val)
{
	switch (_val)
	{
	case 1:
		return ActionCard::ControlledExplosion;
	case 2:
		return ActionCard::Destruction;
	case 3:
		return ActionCard::Flame;
	case 4:
		return ActionCard::Fire;
	case 5:
		return ActionCard::Ash;
	case 6:
		return ActionCard::Spark;
	case 7:
		return ActionCard::Squall;
	case 8:
		return ActionCard::Gale;
	case 9:
		return ActionCard::Hurricane;
	case 10:
		return ActionCard::Gust;
	case 11:
		return ActionCard::Mirage;
	case 12:
		return ActionCard::Storm;
	case 13:
		return ActionCard::Tide;
	case 14:
		return ActionCard::Mist;
	case 15:
		return ActionCard::Wave;
	case 16:
		return ActionCard::Whirlpool;
	case 17:
		return ActionCard::Blizzard;
	case 18:
		return ActionCard::Waterfall;
	case 19:
		return ActionCard::Support;
	case 20:
		return ActionCard::Earthquake;
	case 21:
		return ActionCard::Crumble;
	case 22:
		return ActionCard::Border;
	case 23:
		return ActionCard::Avalanche;
	case 24:
		return ActionCard::Rock;
	default:
		return ActionCard::Default;
	}
}

ActionCard GetMageCard(int16_t _val)
{
	switch (_val)
	{
	case 1:
		return ActionCard::FireMage1;
	case 2:
		return ActionCard::FireMage2;
	case 3:
		return ActionCard::EarthMage1;
	case 4:
		return ActionCard::EarthMage2;
	case 5:
		return ActionCard::AirMage1;
	case 6:
		return ActionCard::AirMage2;
	case 7:
		return ActionCard::WaterMage1;
	case 8:
		return ActionCard::WaterMage2;
	default:
		return ActionCard::Default;
	}
}
