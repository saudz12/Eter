#pragma once
#include "functionsMageCards.h"
#include "functionsElementalCards.h"

inline void* associateCardWithFunc(ActionCard AcCard)
{
	switch (AcCard)
	{
	case ActionCard::ControlledExplosion:
		return (void*)funcControlledExplosion;
		break;
	case ActionCard::Destruction:
		return (void*)funcDestruction;
		break;
	case ActionCard::Flame:
		return (void*)funcFlame;
		break;
	case ActionCard::Fire:
		return (void*)funcFire;
		break;
	case ActionCard::Ash:
		return (void*)funcAsh;
		break;
	case ActionCard::Spark:
		return (void*)funcSpark;
		break;
	case ActionCard::Squall:
		return (void*)funcSquall;
		break;
	case ActionCard::Gale:
		return (void*)funcGale;
		break;
	case ActionCard::Hurricane:
		return (void*)funcHurricane;
		break;
	case ActionCard::Gust:
		return (void*)funcGust;
		break;
	case ActionCard::Mirage:
		return (void*)funcMirage;
		break;
	case ActionCard::Storm:
		return (void*)funcStorm;
		break;
	case ActionCard::Tide:
		return (void*)funcTide;
		break;
	case ActionCard::Mist:
		return (void*)funcMist;
		break;
	case ActionCard::Wave:
		return (void*)funcWave;
		break;
	case ActionCard::Whirlpool:
		return (void*)funcWhirlpool;
		break;
	case ActionCard::Blizzard:
		return (void*)funcBlizzard;
		break;
	case ActionCard::Waterfall:
		return (void*)funcWaterfall;
		break;
	case ActionCard::Support:
		return (void*)funcSupport;
		break;
	case ActionCard::Earthquake:
		return (void*)funcEarthquake;
		break;
	case ActionCard::Crumble:
		return (void*)funcCrumble;
		break;
	case ActionCard::Border:
		return (void*)funcBorder;
		break;
	case ActionCard::Avalanche:
		return (void*)funcAvalanche;
		break;
	case ActionCard::Rock:
		return (void*)funcRock;
		break;
	case ActionCard::Default:
		return (void*)funcDefault;
		break;
	case ActionCard::FireMage1:
		return (void*)funcFireMage1;
		break;
	case ActionCard::FireMage2:
		return (void*)funcFireMage2;
		break;
	case ActionCard::EarthMage1:
		return (void*)funcEarthMage1;
		break;
	case ActionCard::EarthMage2:
		return (void*)funcEarthMage2;
		break;
	case ActionCard::AirMage1:
		return (void*)funcAirMage1;
		break;
	case ActionCard::AirMage2:
		return (void*)funcAirMage2;
		break;
	case ActionCard::WaterMage1:
		return (void*)funcWaterMage1;
		break;
	case ActionCard::WaterMage2:
		return (void*)funcWaterMage2;
		break;
	default:
		break;
	}
}
