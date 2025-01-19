#pragma once
#include "Card.h"

class HoleCard : public Card
{
public :
	HoleCard();
	CardType GetCardType() const override;
	void SetCardType(CardType type) override;
};

