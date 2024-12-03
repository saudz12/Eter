#pragma once

#include "qlabel.h"
#include "qboxlayout.h"
#include "qwidget.h"
#include "qstring.h"
#include "qdir.h"

#include <vector>

#include "Player.h"

class qtCompletePlayer
{
private:
	///declarations
	std::vector<QString> m_pathCards;
	std::deque<QPixmap> m_pixmapCards;
	Player m_player;

	///functions
	void generatePathsForMinionCards();
	void loadCards();
public:
	qtCompletePlayer(char color);

	///getters
	std::vector<QString>& GetPathCards();
	std::deque<QPixmap>& GetPixmapCards();

	///setters
	void SetPathCards(std::vector<QString>& pathCards);
	void SetPixmapCards(std::deque<QPixmap>& pixmapCards);
};

