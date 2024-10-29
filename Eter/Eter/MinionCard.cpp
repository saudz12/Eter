#include "MinionCard.h"

uint16_t MinionCard::GetValue() const
{
    return m_value;
}

std::string MinionCard::GetColor() const
{
    return m_color;
}

bool MinionCard::GetIsEterCard() const
{
    return m_isEterCard;
}

bool MinionCard::GetIsIllusionCard() const
{
    return m_isIllusionCard;
}

CardType MinionCard::GetCardType() const
{
    return m_cardType;
}

void MinionCard::SetValue(uint16_t value) 
{
    m_value = value;
}

void MinionCard::SetColor(std::string color)
{
    m_color = color;
}

void MinionCard::SetIsEterCard(bool isEterCard)
{
    m_isEterCard = isEterCard;
}

void MinionCard::SetIsIllusionCard(bool isIllusionCard)
{
    m_isIllusionCard = isIllusionCard;
}

void MinionCard::SetCardType(CardType type)
{
    m_cardType = type;
}
