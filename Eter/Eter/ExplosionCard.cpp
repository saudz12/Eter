#include "ExplosionCard.h"

std::pair<uint16_t, uint16_t> ExplosionCard::GeneratePositionInMatrix(uint16_t size)
{
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(0, size-1); 
	uint16_t i, j;
	do
	{
		i = distr(gen);
		j = distr(gen);
	} while (m_explosionMap.find({i,j})!=m_explosionMap.end());
	return { i,j };
}

ReturnRemoveOrHoleCard ExplosionCard::GenerateEffect()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(1, 100);
	//1-49 return 
	//50-98 remove
	//99-100 hole
	uint16_t chanceForCard = distr(gen);
	if (chanceForCard >= 1 && chanceForCard <= 49)
		return ReturnRemoveOrHoleCard::ReturnCard;
	else if (chanceForCard >= 50 && chanceForCard <= 98)
		return ReturnRemoveOrHoleCard::RemoveCard;
	return ReturnRemoveOrHoleCard::HoleCard;
}

ExplosionCard::ExplosionCard(const explMap& Matrix) : Card{CardType::ExplosionCard}
{
	this->m_explosionMap = Matrix;
}

ExplosionCard::ExplosionCard(uint16_t size):Card{ CardType::ExplosionCard }
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr;
	if (size == 3)
		distr = std::uniform_int_distribution(2, 4);
	else if (size == 4)
		distr = std::uniform_int_distribution(3, 6);
	uint16_t numberOfEffects = distr(gen);
	for (int16_t i = 0; i < numberOfEffects; ++i)
	{
		std::pair<uint16_t, uint16_t> pos = GeneratePositionInMatrix(size);
		ReturnRemoveOrHoleCard effect = GenerateEffect();
		m_explosionMap[pos] = effect;
	}	
	showExpl(size);
}

const explMap& ExplosionCard::GetExplosionMap() const
{
	return this->m_explosionMap;
}

CardType ExplosionCard::GetCardType() const
{
	return m_cardType;
}

void ExplosionCard::SetExplosionMap(const explMap& Map)
{
	this->m_explosionMap = Map;
}

void ExplosionCard::SetCardType(CardType type)
{
	m_cardType = type;
}

void ExplosionCard::RotateToRight(uint16_t size)
{
	std::unordered_map<std::pair<uint16_t, uint16_t>, ReturnRemoveOrHoleCard,PairHash> newMap;
	for (const auto& effect : m_explosionMap)
	{
		uint16_t i, j;
		i = effect.first.second;
		j = size - 1 - effect.first.first;
		newMap[{i, j}] = effect.second;
	}
	m_explosionMap = newMap;
}

void ExplosionCard::showExpl(int16_t size)
{
	qDebug() << "The explosion:\n";
	for (int16_t i = 0; i < size; ++i)
	{
		for (int16_t j = 0; j < size; ++j)
		{
			if (m_explosionMap.find({ i,j }) != m_explosionMap.end())
			{
				switch (m_explosionMap[{i,j}])
				{
				case ReturnRemoveOrHoleCard::ReturnCard:
					qDebug() << "Ret ";
					break;
				case ReturnRemoveOrHoleCard::RemoveCard:
					qDebug() << "Rem ";
					break;
				case ReturnRemoveOrHoleCard::HoleCard:
					qDebug() << "Hol ";
					break;
				default:
					break;
				}
			}
			else
				qDebug() << "--- ";
		}
		qDebug() << '\n';
	}
}

