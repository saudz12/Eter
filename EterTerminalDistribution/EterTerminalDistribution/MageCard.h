#pragma once
#include "Card.h"
#include "ActionType.h"
#include <cstdint>
using MageType = std::pair<ActionCard, ActionCard>;

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

	void SetActionCard(ActionCard, uint16_t);
	void SetActionCard(ActionCard, ActionCard);

	void SetCardType(CardType type);
	void SetMageType(MageType mage);
	void SetIsActiveFace(bool isActiveFace);
};

