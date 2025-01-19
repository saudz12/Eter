#pragma once
#include "Includes.h"
#include "ReturnOrRemoveType.h"

struct PairHash {
	std::size_t operator()(const std::pair<uint16_t, uint16_t>& p) const {
		// Combine the hash of both elements
		std::size_t hash1 = std::hash<uint16_t>()(p.first);
		std::size_t hash2 = std::hash<uint16_t>()(p.second);
		return hash1 ^ (hash2 << 1); // Combine using XOR and bit-shifting
	}
};

using explMap=std::unordered_map<std::pair<uint16_t,uint16_t>,ReturnRemoveOrHoleCard,PairHash>;

class ExplosionCard : public Card
{
private:
	explMap m_explosionMap;
	std::pair<uint16_t,uint16_t> GeneratePositionInMatrix(uint16_t);
	ReturnRemoveOrHoleCard GenerateEffect();
public:
	ExplosionCard(const explMap& explosionMap);
	ExplosionCard(uint16_t);
	const explMap& GetExplosionMap() const;	

	void SetCardType(CardType type) override;
	void SetExplosionMap(const explMap& Map);

	CardType GetCardType() const override;
		
	void RotateToRight(uint16_t);
	void showExpl(int16_t);
};