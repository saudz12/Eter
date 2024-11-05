#pragma once
#include "Card.h"
#include "ActionType.h"
#include "unordered_map"
class ElementalCard : public Card
{
private:
	ActionCard m_elementType;
public:
	//constructors
	ElementalCard();
	ElementalCard(ActionCard);

	//getters
	CardType GetCardType() const ;
	ActionCard GetActionCard() const;

	//setters
	void SetCardType(CardType);
	void SetActionCard(ActionCard);
};