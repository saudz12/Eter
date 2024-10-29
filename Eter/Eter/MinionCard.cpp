#include "MinionCard.h"

MinionCard::MinionCard(uint16_t value, std::string_view cardColor) : Card {CardType::MinionCard}
{
    m_value = value;
    m_cardColor = cardColor;
    m_isEterCard = false;
    m_isIllusionCard = false;
}

uint16_t MinionCard::GetValue() const
{
    return m_value;
}

std::string MinionCard::GetCardColor() const
{
    return m_cardColor;
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

void MinionCard::SetColor(std::string cardColor)
{
    m_cardColor = cardColor;
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
