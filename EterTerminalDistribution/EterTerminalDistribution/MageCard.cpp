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

void MageCard::SetActionCard(ActionCard card, uint16_t whichCard)
{
	switch (whichCard)
	{
		case 1:
			m_mageType = { ActionCard::FireMage1,ActionCard::FireMage2 };
			break;
		case 2:
			m_mageType = { ActionCard::EarthMage1,ActionCard::EarthMage2 };
			break;
		case 3:
			m_mageType = { ActionCard::AirMage1,ActionCard::AirMage2 };
			break;
		case 4: 
			m_mageType= { ActionCard::WaterMage1,ActionCard::WaterMage2 };
			break;
		default:
			break;
	}
}

void MageCard::SetActionCard(ActionCard actionCard1, ActionCard actionCard2)
{
	m_mageType = {actionCard1,actionCard2};
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
