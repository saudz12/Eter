#pragma once

#include "qtCompletePlayer.h"


qtCompletePlayer::qtCompletePlayer(Colours color,int width,int heigth,bool isDraggable) :
	m_player{color},m_CARD_WIDTH{width},m_CARD_HEIGTH{heigth},m_isDraggable{isDraggable}
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

std::deque<QPointer<qDraggableLabel>>& qtCompletePlayer::GetLabelsCards()
{
    return m_labelsCards;
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
    const Hand& currPlayerHandCard = m_player.GetHandCards();
    int i = 0;
    for (auto& currCard : currPlayerHandCard)
    {
        auto& [currMinionCard, remainingCards] = currCard;
        int cardValue = currMinionCard.GetValue();
        int auxRemainingCards = remainingCards;
        m_pixmapCards.emplace_back(m_pathCards[cardValue]);
        while (auxRemainingCards != 0)
        {
            QPixmap resizedCard=
                m_pixmapCards[i].scaled(m_CARD_WIDTH, m_CARD_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            QPointer<qDraggableLabel> currDragLabel = new 
                qDraggableLabel(resizedCard, m_CARD_WIDTH, m_CARD_HEIGTH,m_isDraggable);

            currDragLabel->setColor(m_player.GetPlayerColor());
            currDragLabel->setValue(cardValue);
            m_labelsCards.emplace_back(currDragLabel);
            auxRemainingCards--;
        }
        i++;
    }
}

void qtCompletePlayer::generatePathsForMinionCards()
{
    QString basePath = QDir::currentPath() + "/textures/";
    if (m_player.GetPlayerColor() == Colours::RED)
        basePath += "red_";
    else
        basePath += "blue_";
    for (size_t i = 0; i < 5; i++)
    {
        m_pathCards.emplace_back(basePath + QString::number(i) + ".jpg");
        qDebug() << basePath + QString::number(i) + ".jpg";
    }
}



