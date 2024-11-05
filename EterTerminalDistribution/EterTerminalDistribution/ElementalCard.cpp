#include "ElementalCard.h"

ElementalCard::ElementalCard() : Card(CardType::ElementalCard), m_elementType{ActionCard::Default}
{
}

ElementalCard::ElementalCard(ActionCard action) : Card(CardType::ElementalCard), m_elementType{action}
{
}

CardType ElementalCard::GetCardType() const
{
	return m_cardType;
}

ActionCard ElementalCard::GetActionCard() const
{
	return m_elementType;
}

void ElementalCard::SetCardType(CardType type)
{
	m_cardType = type;
}

void ElementalCard::SetActionCard(ActionCard action)
{
	m_elementType = action;
}
