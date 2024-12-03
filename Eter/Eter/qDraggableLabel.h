#pragma once

#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

class qDraggableLabel : public QLabel
{
	Q_OBJECT
private:
	QPixmap m_cardPixmap;
public:
	qDraggableLabel(QPixmap cardPixmap, const int CARD_WIDTH, const int CARD_HEIGHT, QWidget* parent = nullptr);
private:
	void mousePressEvent(QMouseEvent* event) override;
};

