#include "qGameBoardWidget.h"

qGameBoardWidget::qGameBoardWidget(QWidget* parent,int board_max_size, int card_width, int card_heigth,int spacing) :
    QWidget{parent},
    CARD_WIDTH{card_width},
    CARD_HEIGTH{card_heigth},
    BOARD_MAX_SIZE{board_max_size}
{
    setAcceptDrops(true); // Enable the widget to accept drops

    rows = 0;
    columns = 0;
    rowsWithEmptySpaces = 0;
    columnsWithEmptySpaces = 0;

    xMax = 0;
    yMax = 0;

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(1,1,1,1);

    setLayout(gridLayout);
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
        qDebug() << row << " " << col<<'\n';
        // Cast the layout to QGridLayout
        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
        if (gridLayout)
        {
            QLayoutItem* item = gridLayout->itemAtPosition(row, col);
            if (item) {
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                if (label->property("type") =="empty") {
                    expandBoard(row,col);
                    label->setProperty("type", "minion card");
                }
            }
            
            gridLayout->addWidget(newCardLabel, row, col);
        }
        else {
            qWarning() << "The layout is not a QGridLayout!";
        }

        event->acceptProposedAction();  // Accept the drop action
    }
}

void qGameBoardWidget::expandBoard(int& row, int& column)
{
    if (rows == BOARD_MAX_SIZE && columns == BOARD_MAX_SIZE)
        return;
    qDebug() << "got here";
    //pt primul card pus
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    if (rowsWithEmptySpaces == 1 && columnsWithEmptySpaces == 1)
    {
        rows = 1 ;
        columns = 1;
        rowsWithEmptySpaces = rows+2;
        columnsWithEmptySpaces = columns+2;
        row = 1;
        column = 1;
        QLayoutItem* item = gridLayout->itemAtPosition(0, 0);
        if (item)
        {
            QWidget* widget = item->widget();
            if (widget)
            {
                gridLayout->removeWidget(widget);
                gridLayout->addWidget(widget, 1, 1);
            }
        }
        for (size_t i = 0; i < rows+2; ++i)
        {
            for (size_t j = 0; j < columns+2; ++j)
            {
                if (i != 1 || j != 1)
                {
                    QLabel* emptySpace = createWhiteSpace();
                    emptySpace->setProperty("type", "empty");
                    gridLayout->addWidget(emptySpace, i, j);
                    /*if (m_possiblePositions.find({ i,j }) == m_possiblePositions.end())
                        m_possiblePositions.emplace(( (i,j), emptySpace ));*/
                }
            }
        }
        this->resize((columns+2) * CARD_WIDTH, (rows+2) * CARD_HEIGTH);
        return;
    }  

    bool existsOnLeftCol = false;
    bool existsOnRightCol = false;
    bool existsOnTopRow = false;
    bool existsOnBottomRow = false;

    std::vector<std::pair<int, int>>& vCreateWhiteSpaces=checkPositionsForWhiteSpaces(gridLayout,row,column,
        existsOnLeftCol, existsOnRightCol, existsOnTopRow, existsOnBottomRow);
    
    qDebug() << "leftcol:" << existsOnLeftCol
        << "\nrightcol:" << existsOnRightCol
        << "\ntopRow:" << existsOnTopRow
        << "\nbottomRow" << existsOnBottomRow << '\n';
}

std::vector<std::pair<int, int>>& qGameBoardWidget::checkPositionsForWhiteSpaces(QGridLayout*& gridLayout, int row, int column,
    bool& existsOnLeftCol, bool& existsOnRightCol, bool& existsOnTopRow, bool& existsOnBottomRow)
{
    std::vector<std::pair<int, int>> vCreateWhiteSpaces;
    if (checkPosition(gridLayout, row - 1, column - 1))//top left
        existsOnLeftCol = true;
    else
        vCreateWhiteSpaces.emplace_back(row - 1, column - 1);
    
    if (checkPosition(gridLayout, row, column - 1))//left
        existsOnLeftCol = true;
    else
        vCreateWhiteSpaces.emplace_back(row, column - 1);
    
    if (checkPosition(gridLayout, row + 1, column - 1))
        existsOnLeftCol = true;
    else
        vCreateWhiteSpaces.emplace_back(row + 1, column - 1);
    
    //existsOnRightColumn
    if (checkPosition(gridLayout, row - 1, column + 1))//top left
        existsOnRightCol = true;
    else
        vCreateWhiteSpaces.emplace_back(row - 1, column + 1);

    if (checkPosition(gridLayout, row, column + 1))//left
        existsOnRightCol = true;
    else
        vCreateWhiteSpaces.emplace_back(row, column + 1);

    if (checkPosition(gridLayout, row + 1, column + 1))
        existsOnRightCol = true;
    else
        vCreateWhiteSpaces.emplace_back(row + 1, column + 1);

    ////existsOnTopRow

    if (checkPosition(gridLayout, row-1, column - 1))//top left
        existsOnTopRow = true;
    else
        vCreateWhiteSpaces.emplace_back(row-1, column - 1);

    if (checkPosition(gridLayout, row-1, column))//left
        existsOnTopRow = true;
    else
        vCreateWhiteSpaces.emplace_back(row-1, column );

    if (checkPosition(gridLayout, row -1, column + 1))
        existsOnTopRow = true;
    else
        vCreateWhiteSpaces.emplace_back(row - 1, column + 1);

    //existsOnBottomRow
    if (checkPosition(gridLayout, row + 1, column - 1))//top left
        existsOnBottomRow = true;
    else
        vCreateWhiteSpaces.emplace_back(row + 1, column - 1);

    if (checkPosition(gridLayout, row + 1, column))//left
        existsOnBottomRow = true;
    else
        vCreateWhiteSpaces.emplace_back(row + 1, column);

    if (checkPosition(gridLayout, row + 1, column + 1))
        existsOnBottomRow = true;
    else
        vCreateWhiteSpaces.emplace_back(row + 1, column + 1);

    return vCreateWhiteSpaces;
}

void qGameBoardWidget::setBoardPosition(const int x, const int y, const int card_width, const int card_height)
{
    setGeometry(x,y,card_width,card_height);
    setupEmptyBoard();
}

void qGameBoardWidget::addWidgetOnBoard(qDraggableLabel* card, int row, int column)
{
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    gridLayout->addWidget(card, row, column);
}

void qGameBoardWidget::setupEmptyBoard()
{
    rows = 1;
    columns = 1; 
    rowsWithEmptySpaces = rows;
    columnsWithEmptySpaces = columns;
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    this->resize(CARD_WIDTH, CARD_HEIGTH);
    QLabel* emptySpace = createWhiteSpace();
    // Add to grid layout at the specified position
    gridLayout->addWidget(emptySpace, 0,0);
    
    this->show();
}

QLabel*& qGameBoardWidget::createWhiteSpace()
{
    QLabel* emptySpace = new QLabel(this);
    emptySpace->setStyleSheet("border: 2px solid red; background-color: white;");
    emptySpace->setFixedSize(CARD_WIDTH, CARD_HEIGTH);  // Ensure the QLabel is the right size
    emptySpace->setProperty("type", "empty");
    emptySpace->setAlignment(Qt::AlignCenter);
    return emptySpace;
}

bool qGameBoardWidget::checkPosition( QGridLayout*& gridLayout,int i, int j)
{
    if (i < 0 || i >= BOARD_MAX_SIZE || j < 0 || j >= BOARD_MAX_SIZE)
        return false;
    if (gridLayout->itemAtPosition(i, j) == nullptr)
        return false;
    QLayoutItem* item = gridLayout->itemAtPosition(i,j);
    if (item) {
        QLabel* label = qobject_cast<QLabel*>(item->widget());
        if (label->property("type") == "empty")
            return false;
    }
    return true;
}


