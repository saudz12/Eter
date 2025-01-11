#include "qDraggableLabel.h"

qDraggableLabel::qDraggableLabel(QPixmap& cardPixmap, const int CARD_WIDTH,const int CARD_HEIGHT,bool isDraggable)
    : m_cardPixmap{ cardPixmap },m_isDraggable{isDraggable}
{
    setPixmap(m_cardPixmap);
    setAlignment(Qt::AlignCenter);
    setFixedSize(CARD_WIDTH,CARD_HEIGHT);
}

void qDraggableLabel::setParent(QWidget* parent)
{
    setParent(parent);
}

void qDraggableLabel::setColor(Colours color)
{
    m_color = color;
}

void qDraggableLabel::mousePressEvent(QMouseEvent* event)
{
    if (m_isDraggable && event->button() == Qt::LeftButton) {
        QMimeData* mimeData = new QMimeData;
        QByteArray pixmapData;
        QDataStream stream(&pixmapData, QIODevice::WriteOnly);
        mimeData->setText("minion");
        mimeData->setProperty("value", m_value);

        if (m_color == Colours::RED)
            mimeData->setProperty("color", QString("R"));
        else if (m_color == Colours::BLUE)
            mimeData->setProperty("color", QString("B"));

        stream << m_cardPixmap;
        mimeData->setData("application/x-card-pixmap", pixmapData);
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(m_cardPixmap);
        drag->setHotSpot(event->pos());
        // Start the drag
        drag->exec();
    }
    //QLabel::mousePressEvent(event);
}
