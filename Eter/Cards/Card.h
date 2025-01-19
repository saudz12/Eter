#pragma once

#ifdef CARDS_EXPORTS
	#define CARD_API __declspec(dllexport)
#else
	#define CARD_API __declspec(dllimport)
#endif

#include <cstdint>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

enum class CARD_API CardType : uint16_t { MinionCard, ExplosionCard, HoleCard, MageCard, ElementalCard, BlizzardCard};

enum class CARD_API Colours : int16_t {
	RED,
	BLUE,
	INVALID_COL
};

class CARD_API Card
{
protected:
	CardType m_cardType;
public:
	Card(const CardType type);
	virtual CardType GetCardType() const=0;
	virtual void SetCardType(CardType type)=0;
};

