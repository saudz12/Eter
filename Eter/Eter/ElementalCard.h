#pragma once
#include "Card.h"
#include "ActionType.h"

using ElementalCardType= std::pair<ActionCard, void*>;

class ElementalCard : public Card
{
private:
	ElementalCardType m_elementType;

public:
	//constructors
	ElementalCard();
	ElementalCard(ElementalCardType&);

	//getters
	ActionCard GetActionCard() const;
	CardType GetCardType() const ;
	ElementalCardType GetElementalCardType() const;

	//setters
	void SetActionCard(ActionCard);
	void SetCardType(CardType);
	void SetElementalCardType(ElementalCardType);
	
};