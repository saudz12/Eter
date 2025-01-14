#pragma once

#include "qlabel.h"
#include "qboxlayout.h"
#include "qwidget.h"
#include "qstring.h"
#include "qdir.h"
#include "qpointer.h"

#include <vector>
#include <memory>

#include "Player.h"
#include "qDraggableLabel.h"

class qtCompletePlayer
{
private:
	///declarations
	std::vector<QString> m_pathCards;
	std::deque<QPixmap> m_pixmapCards;
	std::deque<QPointer<qDraggableLabel>> m_labelsCards;
	std::shared_ptr<Player> m_player;
	bool m_isDraggable;
	const int m_CARD_WIDTH, m_CARD_HEIGTH;
	///functions
	void generatePathsForMinionCards();
	void loadCards();
public:
	qtCompletePlayer(std::shared_ptr<Player>,int width,int heigth,bool m_isDraggable);

	///getters
	std::vector<QString>& GetPathCards();
	std::deque<QPixmap>& GetPixmapCards();
	std::deque<QPointer<qDraggableLabel>>& GetLabelsCards();
	///setters
	void SetPathCards(std::vector<QString>& pathCards);
	void SetPixmapCards(std::deque<QPixmap>& pixmapCards);
};

