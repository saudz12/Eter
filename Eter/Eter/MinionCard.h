#pragma once
#include "Card.h"

#include "qdebug.h"

using position = std::tuple< uint16_t, uint16_t, uint16_t>;

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
	//char m_color;
	Colours m_color;
	bool m_isEterCard;
	bool m_isIllusionCard;
	bool m_marker;
	//char m_belongsTo;
	Colours m_belongsTo;
	bool m_isHole;
public:
	static MinionCard&& CreateHoleCard();
	static MinionCard&& CreateEterCard(Colours _colour);
	MinionCard(MinionCard&& other) noexcept;
	MinionCard(uint16_t value, Colours colour, bool isEter, bool isHole = false);
	MinionCard();
	MinionCard(const MinionCard& other);

	//overload functions
	friend std::ostream& operator<<(std::ostream &out,const MinionCard &card);
	friend QDebug operator<<(QDebug debug, const MinionCard& card);
	bool operator>(const MinionCard& card);
	bool operator==(const MinionCard& card) const;
	MinionCard& operator=(const MinionCard& card);

	//getters
	uint16_t GetValue() const;

	Colours GetColor() const;
	bool GetIsEterCard() const;
	bool GetIsIllusionCard() const;
	bool GetMarker() const;
	CardType GetCardType() const override;

	bool CheckIsHole() const;

	//setters
	void SetValue(uint16_t value);

	void SetColor(Colours color);
	void SetIsEterCard(bool isEterCard);
	void SetIsIllusionCard(bool isIllusionCard);
	void SetCardType(CardType type) override;
	void SetMarker(bool isMarked);

	void SetBelongsTo(Colours belongsTo);
	void SetIsHole(bool isHole);
};

namespace std
{
	template<>
	struct hash <MinionCard>
	{
		size_t operator()(const MinionCard& card) const
		{
			return std::hash<uint16_t>()(card.GetValue());
		}
	};
}



