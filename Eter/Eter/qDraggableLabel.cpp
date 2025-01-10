#include "qDraggableLabel.h"

qDraggableLabel::qDraggableLabel(QPixmap& cardPixmap, const int CARD_WIDTH,const int CARD_HEIGHT)
    : m_cardPixmap{ cardPixmap }
{
    setPixmap(m_cardPixmap);
    setAlignment(Qt::AlignCenter);
    setFixedSize(CARD_WIDTH,CARD_HEIGHT);
}

void qDraggableLabel::setParent(QWidget* parent)
{
    setParent(parent);
}

void qDraggableLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QMimeData* mimeData = new QMimeData;
        QByteArray pixmapData;
        QDataStream stream(&pixmapData, QIODevice::WriteOnly);
        mimeData->setText("minion");
        mimeData->setProperty("value", m_value);
        mimeData->setProperty("color", QString(m_color));
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
