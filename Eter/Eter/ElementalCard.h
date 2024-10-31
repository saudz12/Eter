#pragma once
#include "Card.h"

class ElementalCard : public Card
{

public:
	ElementalCard();
	CardType GetCardType() const ;
	void SetCardType(CardType type);
};

