#pragma once

#include "qtCompletePlayer.h"


qtCompletePlayer::qtCompletePlayer(char color) :
	m_player{color}
{
	generatePathsForMinionCards();
    loadCards();
}

std::vector<QString>& qtCompletePlayer::GetPathCards()
{
    return m_pathCards;
}

std::deque<QPixmap>& qtCompletePlayer::GetPixmapCards()
{
    return m_pixmapCards;
}

void qtCompletePlayer::SetPathCards(std::vector<QString>& pathCards)
{
    m_pathCards = pathCards;
}

void qtCompletePlayer::SetPixmapCards(std::deque<QPixmap>& pixmapCards)
{
    m_pixmapCards = pixmapCards;
}

void qtCompletePlayer::loadCards()
{
    const hand& currPlayerHandCard=m_player.GetHandCards();

    for (auto& currCard : currPlayerHandCard)
    {
        auto& [currMinionCard, remainingCards] = currCard;
        int cardValue = currMinionCard.GetValue();
        int auxRemainingCards = remainingCards;
        while (auxRemainingCards != 0)
        {
            m_pixmapCards.emplace_back(m_pathCards[cardValue]);
            auxRemainingCards--;
        }
    }
}

void qtCompletePlayer::generatePathsForMinionCards()
{
    QString basePath = QDir::currentPath() + "/textures/";
    if (m_player.GetPlayerColor() == 'R')
        basePath += "red_";
    else
        basePath += "blue_";
    for (size_t i = 0; i < 5; i++)
    {
        m_pathCards.emplace_back(basePath + QString::number(i) + ".jpg");
    }

}



