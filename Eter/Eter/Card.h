#pragma once
#include "CardType.h"

class Card
{
protected:
	CardType m_cardType;
public:
	virtual CardType GetCardType() const;
	virtual void SetCardType(CardType type);
	Card(const CardType type);
};

