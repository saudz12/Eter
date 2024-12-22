#pragma once
#include "Card.h"
#include "ActionType.h"

using ElementalCardType= std::pair<ActionCard, void*>;

class ElementalCard : public Card
{
private:
	ElementalCardType m_elementType;

	template<typename T>
	T generateRandomElementalCard();
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

template<typename T>
inline T ElementalCard::generateRandomElementalCard()
{
	constexpr int first = static_cast<int>(T::ControlledExplosion);
	constexpr int last = static_cast<int>(T::Rock);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(first, last);

	return static_cast<T>(dist(gen));
}

