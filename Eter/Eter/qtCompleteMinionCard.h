#pragma once
#include "qpixmap.h"

#include "Includes.h"

class qtCompleteMinionCard
{
private:
	MinionCard m_minionCard;
	QPixmap m_minionCardImage;
public:
	qtCompleteMinionCard(uint16_t value,Colours color,bool isEter,QPixmap& minionCardImage);
};

