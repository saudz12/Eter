#pragma once

#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <qpointer.h>

#include "Includes.h"

class qDraggableLabel : public QLabel
{
	Q_OBJECT
private:
	QPixmap m_cardPixmap;
	int m_value;
	Colours m_color;
	bool m_isDraggable;
public:
	qDraggableLabel(QPixmap& cardPixmap, const int CARD_WIDTH, const int CARD_HEIGHT,bool isDraggable);
	void setParent(QWidget* widget);
	void setValue(int value) { m_value = value; setProperty("value", m_value); }
	void setColor(Colours color);
	void setDraggable(bool isDraggable) { m_isDraggable = isDraggable; }
private:
	void mousePressEvent(QMouseEvent* event) override;
};

