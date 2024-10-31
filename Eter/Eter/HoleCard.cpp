#include "HoleCard.h"

HoleCard::HoleCard() : Card(CardType::HoleCard)
{
}

CardType HoleCard::GetCardType() const
{
    return m_cardType;
}

void HoleCard::SetCardType(CardType type)
{
    m_cardType = type;
}
