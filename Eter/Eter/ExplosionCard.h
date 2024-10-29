#pragma once
#include "Card.h"
#include <vector>
#include "ReturnOrRemoveType.h"

typedef std::vector<std::vector<ReturnOrRemoveCard>> explMatrix;

class ExplosionCard : public Card
{
private:
	explMatrix m_explosionMatrix;
public:
	ExplosionCard(const explMatrix& explosionMatrix);

	explMatrix GetExplosionMatrix() const;

	void SetCardType(CardType type) override;
	void SetExplosionMatrix(const explMatrix& Matrix);
	
	CardType GetCardType() const override;
		
	void RotateToRight();
};

