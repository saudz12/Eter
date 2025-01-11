#include "qtCompleteMinionCard.h"

qtCompleteMinionCard::qtCompleteMinionCard(uint16_t value, Colours color, bool isEter, QPixmap& minionCardImage):
	m_minionCard{value,color,isEter},
	m_minionCardImage{minionCardImage}
{
}
