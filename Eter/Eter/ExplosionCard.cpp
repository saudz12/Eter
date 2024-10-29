#include "ExplosionCard.h"
#include "Card.h"

ExplosionCard::ExplosionCard(const explMatrix& Matrix) : Card{CardType::ExplosionCard}
{
	this->m_explosionMatrix = Matrix;
}

explMatrix ExplosionCard::GetExplosionMatrix() const
{
	return this->m_explosionMatrix;
}

CardType ExplosionCard::GetCardType() const
{
	return m_cardType;
}

void ExplosionCard::SetExplosionMatrix(const explMatrix& Matrix)
{
	this->m_explosionMatrix = Matrix;
}

void ExplosionCard::SetCardType(CardType type)
{
	m_cardType = type;
}

void ExplosionCard::RotateToRight()
{
	explMatrix auxMatrix{ this->m_explosionMatrix };
	for (int i = 0; i < m_explosionMatrix.size(); ++i)
	{
		for (int j = 0; j < m_explosionMatrix[i].size(); ++j)
		{
			this->m_explosionMatrix[j][this->m_explosionMatrix.size() - i - 1] = auxMatrix[i][j];
		}
	}
}

