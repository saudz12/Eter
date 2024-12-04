#pragma once
#include "Includes.h"

enum class CardType : uint16_t { MinionCard, ExplosionCard, HoleCard, MageCard, ElementalCard };

class Card
{
protected:
	CardType m_cardType;
public:
	Card(const CardType type);
	virtual CardType GetCardType() const=0;
	virtual void SetCardType(CardType type)=0;
};

