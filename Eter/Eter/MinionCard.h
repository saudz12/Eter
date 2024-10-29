#pragma once
#include "Card.h"
#include <string>
#include <cstdint>
#include <string_view>

class MinionCard : public Card
{
private:
	uint16_t m_value;
	std::string m_cardColor;
	bool m_isEterCard;
	bool m_isIllusionCard;
public:
	MinionCard(uint16_t value, std::string_view cardColor);
	//getters
	uint16_t GetValue() const;
	std::string GetCardColor() const;
	bool GetIsEterCard() const;
	bool GetIsIllusionCard() const;
	CardType GetCardType() const override;

	//setters
	void SetValue(uint16_t value);
	void SetColor(std::string color);
	void SetIsEterCard(bool isEterCard);
	void SetIsIllusionCard(bool isIllusionCard);
	void SetCardType(CardType type) override;
	
};

