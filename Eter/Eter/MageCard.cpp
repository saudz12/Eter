#include "MageCard.h"

MageCard::MageCard(MageType type,bool activeFace) : Card(CardType::MageCard)
{
	m_mageType = type;
	m_isActiveFace = activeFace;
}

CardType MageCard::GetCardType() const
{
	return m_cardType;
}

MageType MageCard::GetMageType() const
{
	return m_mageType;
}

bool MageCard::GetIsActiveFace() const
{
	return m_isActiveFace;
}

void MageCard::SetCardType(CardType type)
{
	m_cardType = type;
}

void MageCard::SetMageType(MageType mage)
{
	m_mageType = mage;
}

void MageCard::SetIsActiveFace(bool isActiveFace)
{
	m_isActiveFace = isActiveFace;
}
