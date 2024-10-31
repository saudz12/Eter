#include "ElementalCard.h"

ElementalCard::ElementalCard() : Card(CardType::ElementalCard)
{
}

CardType ElementalCard::GetCardType() const
{
	return m_cardType;
}

void ElementalCard::SetCardType(CardType type)
{
	m_cardType = type;
}
