#pragma once

#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <qpointer.h>

class qDraggableLabel : public QLabel
{
	Q_OBJECT
private:
	QPixmap m_cardPixmap;
	int m_value;
	char m_color;
public:
	qDraggableLabel(QPixmap& cardPixmap, const int CARD_WIDTH, const int CARD_HEIGHT);
	void setParent(QWidget* widget);
	void setValue(int value) { m_value = value; setProperty("value", m_value); }
	void setColor(char color) { m_color = color; setProperty("color", QString(color)); }
private:
	void mousePressEvent(QMouseEvent* event) override;
};

