#pragma once
#include "MinionCard.h"
#include "qpixmap.h"

class qtCompleteMinionCard
{
private:
	MinionCard m_minionCard;
	QPixmap m_minionCardImage;
public:
	qtCompleteMinionCard(uint16_t value,char color,bool isEter,QPixmap& minionCardImage);
};

