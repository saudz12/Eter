#pragma once
#include "Card.h"
#include <string>
#include <cstdint>
#include <string_view>
#include <iostream>

class MinionCard : public Card
{
private:
	uint16_t m_value;
	std::string m_color;
	bool m_isEterCard;
	bool m_isIllusionCard;
public:
	MinionCard(uint16_t value, std::string_view color);

	bool operator==(const MinionCard& card) const;
	friend std::ostream& operator<<(std::ostream& os, const MinionCard& card);

	//getters
	uint16_t GetValue() const;
	std::string GetColor() const;
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

namespace std
{
	template<>
	struct hash <MinionCard>
	{
		size_t operator()(const MinionCard& card) const
		{
			size_t h1 = std::hash<uint16_t>()(card.GetValue());
			size_t h2 = std::hash<std::string>()(card.GetColor());
			size_t h3 = std::hash<bool>()(card.GetIsEterCard());

			return h1 ^ (h2 < 1) ^ (h3 < 2);
		}
	};
}

