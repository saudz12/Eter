#pragma once
#include "MinionCard.h"
//#include "ExplosionCard.h"
//#include "MageCard.h"
//#include "ElementalCard.h"

#include <map>

class Player
{
private:
	bool m_playerColor;
	bool m_usedIllusion;
	//bool m_usedPower;
	//bool m_usedMage;
	int m_handSize;
	std::map<MinionCard, int> m_handCards;
	//ElementalCard m_elementalCard;
	//MageCard m_mageCard;
public:
	//getters
	bool GetPlayerColor() const;
	bool GetUsedIllusion() const;
	bool GetHandSize() const;
	std::map<MinionCard, int> GetHandCards() const;
};

