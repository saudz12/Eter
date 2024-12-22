#include "MageCard.h"
#include "funcAssociationsToCard.h"
#include "functionsMageCards.h"

MageCard::MageCard(MageCardType type,bool activeFace) : Card(CardType::MageCard)
{
	m_mageType = type;
	m_isActiveFace = activeFace;
}

MageCard::MageCard() : Card(CardType::MageCard)
{
	auto& [card, associatedFunction] = m_mageType;
	card = generateRandomMageCard<ActionCard>();
	associatedFunction = (void*)associateCardWithFunc(card);
}

CardType MageCard::GetCardType() const
{
	return m_cardType;
}

MageCardType MageCard::GetMageType() const
{
	return m_mageType;
}

bool MageCard::GetIsActiveFace() const
{
	return m_isActiveFace;
}

void MageCard::SetActionCard(ActionCard card)
{
	m_mageType.first = card;
	m_mageType.second = (void*)associateCardWithFunc(m_mageType.first);
}

void MageCard::SetCardType(CardType type)
{
	m_cardType = type;
}

void MageCard::SetMageType(MageCardType mage)
{
	m_mageType = mage;
}

void MageCard::SetIsActiveFace(bool isActiveFace)
{
	m_isActiveFace = isActiveFace;
}
