#pragma once
#include "Card.h"

class MinionCard : public Card
{
private:
	uint16_t m_value;
	char m_color;
	bool m_isEterCard;
	bool m_isIllusionCard;
public:
	MinionCard(uint16_t value, char color);

	//overload functions
	friend std::ostream& operator<<(std::ostream &out,const MinionCard &card);
	bool operator>(const MinionCard& card);
	bool operator==(const MinionCard& card) const;
	
	//getters
	uint16_t GetValue() const;
	char GetColor() const;
	bool GetIsEterCard() const;
	bool GetIsIllusionCard() const;
	CardType GetCardType() const override;

	//setters
	void SetValue(uint16_t value);
	void SetColor(char color);
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
			/*size_t h1 = std::hash<uint16_t>()(card.GetValue());
			size_t h2 = std::hash<char>()(card.GetColor());
			size_t h3 = std::hash<bool>()(card.GetIsEterCard());

			return h1 ^ (h2 < 1) ^ (h3 < 2);*/

			return std::hash<uint16_t>()(card.GetValue());
		}
	};
}



