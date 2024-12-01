#include "MinionCard.h"

MinionCard::MinionCard(uint16_t value, char color, bool isEter) 
    : Card{ CardType::MinionCard }, 
    m_value{ value }, 
    m_color{ color }, 
    m_isEterCard{ isEter }, 
    m_isIllusionCard{ false }, 
    m_marker{ false }, 
    //m_belongsTo(color), 
    m_isHole{false}
{
}

MinionCard::MinionCard(uint16_t value, Colours color, bool isEter)
    : Card{ CardType::MinionCard },
    m_value{ value },
    m_color{ color },
    m_isEterCard{ isEter },
    m_isIllusionCard{ false },
    m_marker{ false },
    m_belongsTo(color), 
    m_isHole{ false }
{
}

uint16_t MinionCard::GetValue() const
{
    return m_value;
}

//char MinionCard::GetColor() const
//{
//    return m_color;
//}

Colours MinionCard::GetColor() const
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

bool MinionCard::GetMarker() const
{
    return m_marker;
}

CardType MinionCard::GetCardType() const
{
    return m_cardType;
}

//char MinionCard::GetBelongsTo() const
//{
//    return m_belongsTo;
//}

Colours MinionCard::GetBelongsTo() const
{
    return m_belongsTo;
}

bool MinionCard::GetIsHole() const
{
    return m_isHole;
}

void MinionCard::SetValue(uint16_t value) 
{
    m_value = value;
}

//void MinionCard::SetColor(char color)
//{
//    m_color = color;
//}

void MinionCard::SetColor(Colours color)
{
    m_color = color;
}

void MinionCard::SetIsEterCard(bool isEterCard)
{
    m_isEterCard = isEterCard;
}

void MinionCard::SetIsIllusionCard(bool isIllusionCard)
{
    if (!m_isEterCard)
        m_isIllusionCard = isIllusionCard;
}

void MinionCard::SetCardType(CardType type)
{
    m_cardType = type;
}

void MinionCard::SetMarker(bool isMarked)
{
    m_marker = isMarked;
}

//void MinionCard::SetBelongsTo(char belongsTo)
//{
//    m_belongsTo = belongsTo;
//}

void MinionCard::SetBelongsTo(Colours belongsTo)
{
    m_belongsTo = belongsTo;
}

void MinionCard::SetIsHole(bool isHole)
{
    m_isHole = isHole;
}

bool MinionCard::operator>(const MinionCard& card)
{
    return (m_value>card.m_value)?true : false;
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

MinionCard& MinionCard::operator=(const MinionCard& card)
{
    m_value = card.m_value;
    m_color = card.m_color;
    m_isEterCard = card.m_isEterCard;
    m_isIllusionCard = card.m_isIllusionCard;
    m_marker = card.m_marker;
    return *this;
}

//std::ostream& operator<<(std::ostream& out, const MinionCard& card)
//{
//    if (card.GetCardType() == CardType::HoleCard)
//        out << " H ";
//    else if (card.GetIsEterCard())
//        out << "E:" << card.GetColor();
//    else if (card.GetIsIllusionCard())
//        out << "I:" << card.GetColor();
//    else
//        out << card.GetValue() << ":" << card.GetColor();
//    return out;
//}

std::ostream& operator<<(std::ostream& out, const MinionCard& card)
{
    if (card.GetCardType() == CardType::HoleCard)
        out << " H ";
    else if (card.GetIsEterCard())
        out << "E:" << card.GetColor();
    else if (card.GetIsIllusionCard())
        out << "I:" << card.GetColor();
    else
        out << card.GetValue() << ":" << card.GetColor();
    return out;
}
