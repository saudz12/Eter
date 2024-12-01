#pragma once
#include "Card.h"
#include "ActionType.h"
#include <cstdint>

//used for calling the functions
using MageCardType = std::pair<ActionCard,void*>;

class MageCard : public Card
{
private:
	MageCardType m_mageType;
	bool m_isActiveFace;
public:
	MageCard(MageCardType Type,bool activeFace);

	CardType GetCardType() const;
	MageCardType GetMageType() const;
	bool GetIsActiveFace() const;

	void SetActionCard(ActionCard);

	void SetCardType(CardType type);
	void SetMageType(MageCardType mage);
	void SetIsActiveFace(bool isActiveFace);
};

