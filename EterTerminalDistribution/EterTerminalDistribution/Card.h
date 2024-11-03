#pragma once
#include "CardType.h"
#include<iostream>
#include <string_view>
class Card
{
protected:
	CardType m_cardType;
public:
	Card(const CardType type);
	virtual CardType GetCardType() const=0;
	virtual void SetCardType(CardType type)=0;
};

