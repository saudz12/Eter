#include "ElementalCard.h"
#include "functionsElementalCards.h"
#include "Board.h"
#include "funcAssociationsToCard.h"

ElementalCard::ElementalCard() :
	Card(CardType::ElementalCard)
{
	auto & [cardType,asssociatedFunction] = m_elementType;
	cardType= generateRandomElementalCard<ActionCard>();
	asssociatedFunction = (void*)associateCardWithFunc(cardType);
}

ElementalCard::ElementalCard(ElementalCardType& ECardType) : 
	Card(CardType::ElementalCard), 
	m_elementType{ECardType.first,nullptr}
{
	m_elementType.first = ECardType.first;
	m_elementType.second=(void*)associateCardWithFunc(ECardType.first);
}

ActionCard ElementalCard::GetActionCard() const
{
	return m_elementType.first;
}

CardType ElementalCard::GetCardType() const
{
	return m_cardType;
}

ElementalCardType ElementalCard::GetElementalCardType() const
{
	return m_elementType;
}

void ElementalCard::SetActionCard(ActionCard AcCard)
{
	m_elementType.first = AcCard;
}

void ElementalCard::SetCardType(CardType type)
{
	m_cardType = type;
}

void ElementalCard::SetElementalCardType(ElementalCardType ECardType)
{
	m_elementType = ECardType;
}


