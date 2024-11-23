#pragma once
#include "Card.h"

using position = std::tuple< uint16_t, uint16_t, uint16_t>;
constexpr auto COL_RED = 'R';
constexpr auto COL_BLUE = 'B';

struct hashPosition {
	size_t operator()(const position& toHash) const {
		int x = std::get<0>(toHash);
		int y = std::get<1>(toHash);
		int pos = std::get<2>(toHash);

		return std::hash<int>()(x) ^ std::hash<int>()(y) ^ std::hash<int>()(pos);
	}
};

class MinionCard : public Card
{
private:
	uint16_t m_value;
	char m_color;
	bool m_isEterCard;
	bool m_isIllusionCard;
	bool m_marker;
	char m_belongsTo;
	bool m_isHole;
public:
	MinionCard(uint16_t value, char color, bool isEter);
	MinionCard() = default;
	
	//overload functions
	friend std::ostream& operator<<(std::ostream &out,const MinionCard &card);
	bool operator>(const MinionCard& card);
	bool operator==(const MinionCard& card) const;
	MinionCard& operator=(const MinionCard& card);
	
	//getters
	uint16_t GetValue() const;
	char GetColor() const;
	bool GetIsEterCard() const;
	bool GetIsIllusionCard() const;
	bool GetMarker() const;
	CardType GetCardType() const override;
	char GetBelongsTo() const;
	bool GetIsHole() const;

	//setters
	void SetValue(uint16_t value);
	void SetColor(char color);
	void SetIsEterCard(bool isEterCard);
	void SetIsIllusionCard(bool isIllusionCard);
	void SetCardType(CardType type) override;
	void SetMarker(bool isMarked);
	void SetBelongsTo(char belongsTo);
	void SetIsHole(bool isHole);
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



