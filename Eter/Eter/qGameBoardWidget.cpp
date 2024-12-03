#include "qGameBoardWidget.h"

qGameBoardWidget::qGameBoardWidget(QWidget* parent,int board_max_size, int card_width, int card_heigth,int spacing) :
    QWidget{parent},
    CARD_WIDTH{card_width},
    CARD_HEIGTH{card_heigth},
    BOARD_MAX_SIZE{board_max_size}
{
    setAcceptDrops(true); // Enable the widget to accept drops

    QGridLayout* gridLayout = new QGridLayout(this);
    //gridLayout->setSpacing(spacing);

    setLayout(gridLayout);
    setupEmptyBoard();
}

void qGameBoardWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();  // Accept the drag
    }
    else {
        event->ignore();  // Reject if it's not the right type of drag
    }
}

void qGameBoardWidget::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasText())
    {
        // Handle the drop by placing the card at the grid's current position
        QPoint dropPosition = event->position().toPoint();

        // Determine the row and column based on the drop position
        int row = dropPosition.y() / CARD_HEIGTH;
        int col = dropPosition.x() / CARD_WIDTH;

        // Create a new QLabel for the card at the drop position
       
        QLabel* newCardLabel = new QLabel(this);

        // Retrieve the QPixmap from the mime data
        if (event->mimeData()->hasFormat("application/x-card-pixmap")) {
            QByteArray pixmapData = event->mimeData()->data("application/x-card-pixmap");
            QDataStream stream(&pixmapData, QIODevice::ReadOnly);

            QPixmap droppedCardPixmap;
            stream >> droppedCardPixmap;  // Deserialize the pixmap

            newCardLabel->setPixmap(droppedCardPixmap.scaled(CARD_WIDTH, CARD_HEIGTH));
        }

        // Cast the layout to QGridLayout
        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
        if (gridLayout) {
            // Add the card to the grid layout at the appropriate position
            gridLayout->addWidget(newCardLabel, row, col);
        }
        else {
            qWarning() << "The layout is not a QGridLayout!";
        }

        event->acceptProposedAction();  // Accept the drop action
    }
}

void qGameBoardWidget::setBoardPosition(const int x, const int y, const int card_width, const int card_height)
{
    setGeometry(x,y,card_width,card_height);
}

void qGameBoardWidget::addWidgetOnBoard(qDraggableLabel* card, int row, int column)
{
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    gridLayout->addWidget(card, row, column);
}

void qGameBoardWidget::setupEmptyBoard()
{
    // Make sure rows and columns are initialized correctly
    rows = 3;   // Set to the desired number of rows
    columns = 3; // Set to the desired number of columns
    qDebug() << CARD_HEIGTH;
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    this->resize(columns * CARD_WIDTH, rows * CARD_HEIGTH);
    // Set a fixed size for each grid cell (adjust as needed)
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            QLabel* emptySpace = new QLabel(this);
            emptySpace->setStyleSheet("border: 2px solid red; background-color: white;");
            emptySpace->setFixedSize(CARD_WIDTH, CARD_HEIGTH);  // Ensure the QLabel is the right size

            emptySpace->setAlignment(Qt::AlignCenter);

            // Add to grid layout at the specified position
            gridLayout->addWidget(emptySpace, row, col);
        }
    }

    this->show();
}


