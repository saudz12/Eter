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

	template<typename T>
	T generateRandomMageCard();
public:
	MageCard(MageCardType Type,bool activeFace);
	MageCard();

	CardType GetCardType() const;
	MageCardType GetMageType() const;
	bool GetIsActiveFace() const;

	void SetActionCard(ActionCard);

	void SetCardType(CardType type);
	void SetMageType(MageCardType mage);
	void SetIsActiveFace(bool isActiveFace);
};

template<typename T>
inline T MageCard::generateRandomMageCard()
{
	constexpr int first = static_cast<int>(T::FireMage1);
	constexpr int last = static_cast<int>(T::WaterMage2);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(first, last);

	return static_cast<T>(dist(gen));
}
