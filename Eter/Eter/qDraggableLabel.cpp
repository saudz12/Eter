#include "qDraggableLabel.h"

qDraggableLabel::qDraggableLabel(QPixmap cardPixmap, int CARD_WIDTH, int CARD_HEIGHT, QWidget* parent)
    : QLabel(parent), m_cardPixmap(cardPixmap) 
{
    setPixmap(m_cardPixmap);  // Set the card image on the label
    setAlignment(Qt::AlignCenter);
    setFixedSize(CARD_WIDTH,CARD_HEIGHT); // Card size

}

void qDraggableLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QMimeData* mimeData = new QMimeData;
        mimeData->setText("Card");  // You can set other data here as well, like card ID
        QByteArray pixmapData;
        QDataStream stream(&pixmapData, QIODevice::WriteOnly);
        stream << m_cardPixmap;  // Assuming m_cardPixmap contains the image data

        mimeData->setData("application/x-card-pixmap", pixmapData);
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(m_cardPixmap);
        drag->setHotSpot(event->pos());

        // Start the drag
        drag->exec();
    }
    QLabel::mousePressEvent(event);
}
