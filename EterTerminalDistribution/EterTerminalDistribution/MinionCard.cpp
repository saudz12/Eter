#include "MinionCard.h"

MinionCard::MinionCard(uint16_t value, char color) 
    : Card{ CardType::MinionCard }, m_value{ value }, m_color{ color }, m_isEterCard{ false }, m_isIllusionCard{ false }
{
}

uint16_t MinionCard::GetValue() const
{
    return m_value;
}

char MinionCard::GetColor() const
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

void MinionCard::SetColor(char color)
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

bool MinionCard::operator>(const MinionCard& card)
{
    return (m_value>card.m_value)?true : false;
}

std::ostream& operator<<(std::ostream& out, const MinionCard& card)
{
    out << card.m_value << ":" <<card.m_color<<" ";
    return out;
}
