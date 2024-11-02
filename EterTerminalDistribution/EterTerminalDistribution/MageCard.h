#pragma once
#include "MageType.h"
#include "Card.h"

class MageCard : public Card
{
private:
	MageType m_mageType;
	bool m_isActiveFace;
public:
	MageCard(MageType Type,bool activeFace);
	
	CardType GetCardType() const;
	MageType GetMageType() const;
	bool GetIsActiveFace() const;

	void SetCardType(CardType type);
	void SetMageType(MageType mage);
	void SetIsActiveFace(bool isActiveFace);
};

