#include "MinionCard.h"

MinionCard::MinionCard(uint16_t value, std::string_view color) : Card {CardType::MinionCard}
{
    m_value = value;
    m_color = color;
    m_isEterCard = false;
    m_isIllusionCard = false;
}

bool MinionCard::operator==(const MinionCard& card) const
{
    if (m_value != card.GetValue())
        return false;
    if (m_color != card.GetColor())
        return false;
    if (m_isEterCard != card.GetIsEterCard())
        return false;
    if (m_isIllusionCard != card.GetIsIllusionCard())
        return false;
    return true;
}

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

std::ostream& operator<<(std::ostream& os, const MinionCard& card)
{
    os << card.GetValue() << " " << card.GetColor();
    return os;
}
