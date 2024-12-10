#include "qGameBoardWidget.h"

qGameBoardWidget::qGameBoardWidget(QWidget* parent, int board_max_size, int card_width, int card_heigth, int spacing) :
    QWidget{ parent },
    CARD_WIDTH{ card_width },
    CARD_HEIGTH{ card_heigth },
    BOARD_MAX_SIZE{ board_max_size }
{
    setAcceptDrops(true); // Enable the widget to accept drops

    rows = 0;
    columns = 0;
    rowsWithEmptySpaces = 0;
    columnsWithEmptySpaces = 0;
    wasFixedBoardCreated = false;
    maxRow = maxColumn = 0;

    offsetColumn = 0;
    offsetRow = 0;

    minRow = minColumn = 10;

    QGridLayout* gridLayout = new QGridLayout(this);

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
        qDebug() << "determined row:" << row << " determined column:" << col << '\n';

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
        if (gridLayout)
        {
            if (maxRow == BOARD_MAX_SIZE && maxColumn == BOARD_MAX_SIZE)
            {

            }
            else if (maxRow == BOARD_MAX_SIZE)
            {
                row++;
                offsetRow++;
            }
            else if (maxColumn == BOARD_MAX_SIZE)
            {
                col++;
                offsetColumn++;
            }
            QLayoutItem* item = gridLayout->itemAtPosition(row, col);
            
            if (item)
            {
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                if (label->property("type") == QString("empty"))
                {
                    currCardPixmap = newCardLabel->pixmap();
                    label = createNewMinionCard();
                    updateMinMaxRowCol();
                    bool expand = expandBoard(row, col);
                    updateMinMaxRowCol();

                    if(expand == true && !(BOARD_MAX_SIZE == maxRow-minRow+1 && BOARD_MAX_SIZE == maxColumn-minColumn+1))
                    {
                        redrawBoard(gridLayout);
                    }
                    else if (BOARD_MAX_SIZE == maxRow-minRow+1 && BOARD_MAX_SIZE == maxColumn-minColumn+1)
                    {
                        removeWidgetFromGrid(gridLayout, row, col);
                        addNewMinionCardToGrid(label, gridLayout, row, col);
                        if (wasFixedBoardCreated == false)
                        {
                            createFixedSizeBoard(gridLayout);
                            wasFixedBoardCreated = true;
                        }
                    }

                }
                else if (label->property("type") == QString("minion"))
                {
                    label = createNewMinionCard();
                    removeWidgetFromGrid(gridLayout, row, col);
                    addNewMinionCardToGrid(label, gridLayout, row, col);
                }
                
            }
        }
        else
        {
            qWarning() << "The layout is not a QGridLayout!";
        }

        event->acceptProposedAction();
    }
}

void qGameBoardWidget::resizeEvent(QResizeEvent* event)
{
    emit boardResized(); // Emit signal when resized
    QWidget::resizeEvent(event); // Call base class implementation
}

bool qGameBoardWidget::expandBoard(int& row, int& column)
{
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    if (maxRow-minRow+1 == BOARD_MAX_SIZE  && maxColumn-minRow+1 ==BOARD_MAX_SIZE )
    {
        return false;
    }
    //pt primul card pus
    if (rowsWithEmptySpaces == 1 && columnsWithEmptySpaces == 1)
    {
        placeFirstCard(gridLayout, row, column);
        return true;
    }

    //existsOnLeftCol = false;
    //existsOnRightCol = false;
    //existsOnTopRow = false;
    //existsOnBottomRow = false;

    //qDebug() << "leftcol:" << existsOnLeftCol
    //    << "\nrightcol:" << existsOnRightCol
    //    << "\ntopRow:" << existsOnTopRow
    //    << "\nbottomRow" << existsOnBottomRow << '\n';


    //if (existsOnBottomRow == false && existsOnLeftCol == false && existsOnRightCol == false && existsOnTopRow == false)
    //    return false;

    std::vector<std::function<void(QGridLayout*&, int&, int&)>> functionCalls = createFunctionCallsVector(gridLayout,row,column);

    for (int i = 0; i < functionCalls.size(); ++i)
    {
        functionCalls[i](gridLayout, row, column);
    }

    QLabel* newCard = createNewMinionCard();
    addNewMinionCardToGrid(newCard, gridLayout, row, column);

    return true;
}

void qGameBoardWidget::setBoardPosition(const int x, const int y, const int card_width, const int card_height)
{
    setGeometry(x, y, card_width, card_height);
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
    gridLayout->addWidget(emptySpace, 0, 0);

    this->show();
}

QLabel* qGameBoardWidget::createWhiteSpace()
{
    QLabel* emptySpace = new QLabel(this);
    emptySpace->setStyleSheet("border: 2px solid red; background-color: white;");
    emptySpace->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
    emptySpace->setProperty("type", "empty");
    emptySpace->setAlignment(Qt::AlignCenter);
    return emptySpace;
}

bool qGameBoardWidget::checkPosition(QGridLayout*& gridLayout, int i, int j)
{
    if (m_cardPosition.find({ i,j }) == m_cardPosition.end())
        return false;
    return true;
}

void qGameBoardWidget::addRowBelow(QGridLayout*& gridLayout, int& row, int& column)
{
    qDebug() << "added row below\n";
    if (maxRow-minRow+1 == BOARD_MAX_SIZE)
        return;
    for (int j = column - 1; j <= column + 1; ++j)
    {
        m_emptyPositions.emplace(std::make_pair(row + 1, j));
    }
}

void qGameBoardWidget::addColumnRight(QGridLayout*& gridLayout, int& row, int& column)
{
    qDebug() << "added column right\n";
    if (maxColumn-minRow+1 == BOARD_MAX_SIZE)
        return;
    for (int i = row - 1; i <= row + 1; ++i)
    {
        m_emptyPositions.emplace(std::make_pair(i, column + 1));
    }

}

void qGameBoardWidget::addRowTop(QGridLayout*& gridLayout, int& row, int& column)
{
    qDebug() << "added row top";
    bool existsCards = false;
    bool isRowEmpty = false;
    int addRow = 1;
    for (int i = column - 1; i <= column + 1; i++)
    {
        QLayoutItem* item = gridLayout->itemAtPosition(row - 1, i);
        if (item) {

            QWidget* widget = item->widget();
            QLabel* label = qobject_cast<QLabel*>(widget);
            if (label) {
                if (label->property("type") == "minion")
                {
                    isRowEmpty = false;
                    existsCards = true;
                    break;
                }
                else if (label->property("type") == "empty")
                {
                    isRowEmpty = true;
                }
            }
        }
    }
    if (existsCards == false && isRowEmpty == true)
        addRow = 0;
    if (maxRow-minRow+1 == BOARD_MAX_SIZE)
        return;
    // Update empty positions
    std::unordered_set<std::pair<int, int>, PairHash1> updatedEmptyPositions;
    for (auto it = m_emptyPositions.begin(); it != m_emptyPositions.end(); ++it)
    {
        auto [oldRow, oldColumn] = *it;
        updatedEmptyPositions.emplace(std::make_pair(oldRow + addRow, oldColumn));
    }
    m_emptyPositions = std::move(updatedEmptyPositions);

    // Update card positions
    std::unordered_map<std::pair<int, int>, QLabel*, PairHash1> updatedCardPositions;
    for (auto it = m_cardPosition.begin(); it != m_cardPosition.end(); ++it)
    {
        auto& [position, card] = *it;
        auto& [oldRow, oldColumn] = position;
        updatedCardPositions.emplace(std::make_pair(std::make_pair(oldRow + addRow, oldColumn), card));
    }

    // Update pixmap positions
    std::unordered_map<std::pair<int, int>, QPixmap, PairHash1> updatedPixmapPosition;
    for (auto it = m_pixmapPosition.begin(); it != m_pixmapPosition.end(); ++it)
    {
        auto& [position, pixmap] = *it;
        auto& [oldRow, oldColumn] = position;
        updatedPixmapPosition.emplace(std::make_pair(std::make_pair(oldRow + addRow, oldColumn), pixmap));
    }

    m_cardPosition = std::move(updatedCardPositions);
    m_pixmapPosition = std::move(updatedPixmapPosition);

    // Add new row of white spaces
    for (int j = column - 1; j <= column + 1; ++j)
    {
        m_emptyPositions.emplace(std::make_pair(row+addRow-1, j));
    }
    
    row+=addRow;
}

void qGameBoardWidget::addColumnLeft(QGridLayout*& gridLayout, int& row, int& column)
{
    bool existsCards = false;
    bool isColEmpty = false;
    int addColumn = 1;
    for (int j = row - 1; j <= row + 1; j++)
    {
        QLayoutItem* item = gridLayout->itemAtPosition(j, column - 1);
        if (item) {
            QWidget* widget = item->widget();
            QLabel* label = qobject_cast<QLabel*>(widget);
            if (label) {
                if (label->property("type") == "minion")
                {
                    isColEmpty = false;
                    existsCards = true;
                    break;
                }
                else if (label->property("type") == "empty")
                {
                    isColEmpty = true;
                }
            }
        }
    }
    if (existsCards == false && isColEmpty == true)
        addColumn = 0;
    qDebug() << "added column left\n";
    if (maxColumn-minColumn+1 == BOARD_MAX_SIZE)
        return;
    std::unordered_set<std::pair<int, int>, PairHash1> updatedEmptyPositions;
    for (auto it = m_emptyPositions.begin(); it != m_emptyPositions.end(); ++it)
    {
        auto [row, column] = *it;

        updatedEmptyPositions.emplace(std::make_pair(row, column + addColumn));
    }
    m_emptyPositions = std::move(updatedEmptyPositions);
    std::unordered_map<std::pair<int, int>, QLabel*, PairHash1> updatedCardPositions;
    std::unordered_map<std::pair<int, int>, QPixmap, PairHash1> updatedPixmapPosition;
    //coloana din stanga
    for (auto it = m_cardPosition.begin(); it != m_cardPosition.end(); ++it)
    {
        auto& [position, card] = *it;
        auto& [row, column] = position;
        updatedCardPositions.emplace(std::make_pair(std::make_pair(row, column + addColumn), card));
    }

    for (auto it = m_pixmapPosition.begin(); it != m_pixmapPosition.end(); ++it)
    {
        auto& [position, pixmap] = *it;
        auto& [row, column] = position;
        updatedPixmapPosition.emplace(std::make_pair(std::make_pair(row, column + addColumn), pixmap));
    }

    m_cardPosition = std::move(updatedCardPositions);
    m_pixmapPosition = std::move(updatedPixmapPosition);

    for (int i = row - 1; i <= row + 1; ++i)
    {
        m_emptyPositions.emplace(std::make_pair(i+addColumn-1, column));
    }

    column+=addColumn;
}

void qGameBoardWidget::redrawBoard(QGridLayout*& gridLayout)
{
    clearBoard(gridLayout);
    
    // Create a set to store valid empty spaces after filtering
    std::unordered_set<std::pair<int, int>, PairHash1> validEmptySpaces;

    // Filter empty spaces based on adjacency (cardinal and diagonal)
    for (const auto& emptySpace : m_emptyPositions)
    {
        const auto& [row, column] = emptySpace;

        bool hasAdjacentCard = false;
        std::vector<std::pair<int, int>> adjacentPositions = {
            {row - 1, column},
            {row + 1, column},
            {row, column - 1},
            {row, column + 1},
            {row - 1, column - 1},
            {row - 1, column + 1},
            {row + 1, column - 1},
            {row + 1, column + 1}
        };

        for (const auto& [adjRow, adjCol] : adjacentPositions)
        {
            if (m_cardPosition.find({ adjRow, adjCol }) != m_cardPosition.end())
            {
                hasAdjacentCard = true;
                break;
            }
        }

        if (hasAdjacentCard)
        {
            if (BOARD_MAX_SIZE == maxColumn-minColumn+1)
            {
                if (column >= minColumn && column <= BOARD_MAX_SIZE)//if (column >=offsetColumn +1 && column <=offsetColumn+ BOARD_MAX_SIZE)
                {
                    validEmptySpaces.insert(emptySpace);
                }
            }
            else if (maxRow-minRow+1 == BOARD_MAX_SIZE)
            {
                if (row >=minRow && row <= BOARD_MAX_SIZE)//if (row >=offsetRow+ 1 && row <=offsetRow+ BOARD_MAX_SIZE)
                {
                    validEmptySpaces.insert(emptySpace);
                }
            }
            else
                validEmptySpaces.insert(emptySpace);
        }
    }

    m_emptyPositions = std::move(validEmptySpaces);

    for (const auto& emptySpace : m_emptyPositions)
    {
        const auto& [row, column] = emptySpace;
        gridLayout->addWidget(createWhiteSpace(), row, column);
        qDebug() << "empty:" << row << "," << column << '\n';
    }

    for (auto& card : m_cardPosition)
    {
        auto& [position, cardLabel] = card;
        auto& [row, column] = position;

        QLayoutItem* existingItem = gridLayout->itemAtPosition(row, column);
        if (existingItem)
        {
            QWidget* existingWidget = existingItem->widget();
            if (existingWidget)
            {
                delete existingWidget;
            }
        }

        if (m_pixmapPosition.find({ row, column }) != m_pixmapPosition.end())
        {
            qDebug() << "Found pixmap for position:" << row << "," << column;
            qDebug() << "Pixmap:" << m_pixmapPosition[{row, column}];
            cardLabel->setPixmap(m_pixmapPosition[{row, column}]);
        }
        else
        {
            qDebug() << "No pixmap found for position:" << row << "," << column;
        }
        cardLabel->setProperty("type", "minion");
        cardLabel->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
        //cardLabel->setAlignment(Qt::AlignCenter);
        cardLabel->show();
        int toAddRow = row, toAddColumn = column;
        addNewMinionCardToGrid(cardLabel, gridLayout, toAddRow, toAddColumn);

        qDebug() << "Card placed at:" << row << "," << column << '\n';
    }
    int newHeight = (gridLayout->rowCount() * CARD_HEIGTH);

    int newWidth = (gridLayout->columnCount() * CARD_WIDTH);
    
    QWidget* parentWidget = gridLayout->parentWidget();
    if (parentWidget) {
        parentWidget->resize(newWidth, newHeight);
    }
}

void qGameBoardWidget::clearBoard(QGridLayout*& gridLayout) {
    if (!gridLayout) return;
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->hide();  // Hide instead of delete

        }
        delete item;
    }
}

void qGameBoardWidget::placeFirstCard(QGridLayout*& gridLayout, int& row, int& column)
{
    rows = 1;
    columns = 1;
    rowsWithEmptySpaces = rows + 2;
    columnsWithEmptySpaces = columns + 2;
    row = 1;
    column = 1;
    maxColumn = maxRow = 1;
    minRow = minColumn = 1;
    QPixmap pixmapFirstCard;
    QLayoutItem* firstItem = gridLayout->itemAtPosition(0, 0);
    if (firstItem)
    {
        QWidget* widget = firstItem->widget();
        if (widget)
        {
            QLayoutItem* item = gridLayout->itemAtPosition(0, 0);
            if (item) {
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                pixmapFirstCard = label->pixmap();
            }
        }
    }
    removeWidgetFromGrid(gridLayout, 0, 0);
    for (size_t i = 0; i < rows + 2; ++i)
    {
        for (size_t j = 0; j < columns + 2; ++j)
        {
            if (!(i == 1 && j == 1))
            {
                QLabel* emptySpace = createWhiteSpace();
                gridLayout->addWidget(emptySpace, i, j);
                if (m_emptyPositions.find({ i,j }) == m_emptyPositions.end())
                    m_emptyPositions.emplace(std::make_pair(i, j));
            }
        }
    }

    QLabel* label = createNewMinionCard();
    label->setPixmap(currCardPixmap.copy());
    m_cardPosition.emplace(std::make_pair(std::make_pair(row, column), label));
    m_pixmapPosition.emplace(std::make_pair(std::make_pair(row, column), label->pixmap().copy()));

    m_cardPosition.erase(std::make_pair(0, 0));
    m_pixmapPosition.erase(std::make_pair(0, 0));
    this->resize(gridLayout->columnCount() * CARD_HEIGTH, gridLayout->rowCount() * CARD_WIDTH);
}

QLabel* qGameBoardWidget::createNewMinionCard()
{
    QLabel* newCard = new QLabel(this);
    newCard->setPixmap(currCardPixmap.copy());
    newCard->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
    newCard->setProperty("type", "minion");
    return newCard;
}

void qGameBoardWidget::addNewMinionCardToGrid(QLabel*& newCard, QGridLayout*& gridLayout, int& row, int& column)
{
    m_cardPosition[{row, column}] = newCard;
    m_pixmapPosition[{row, column}] = newCard->pixmap().copy();
    
    gridLayout->addWidget(newCard, row, column);

}

void qGameBoardWidget::removeWidgetFromGrid(QGridLayout*& gridLayout, int row, int column)
{
    QLayoutItem* item = gridLayout->itemAtPosition(row, column);
    if (item) {
        QWidget* widget = item->widget(); // Get the widget associated with the layout item
        if (widget) {
            gridLayout->removeWidget(widget); // Remove the widget from the layout
            //widget->deleteLater(); // Optionally delete the widget
            widget->hide();
            m_cardPosition.erase({ row, column });
            m_pixmapPosition.erase({ row, column });
        }
        //delete item; // Delete the layout item
    }
}

std::vector<std::function<void(QGridLayout*&, int&, int&)>> qGameBoardWidget::createFunctionCallsVector(QGridLayout*& gridLayout, int& row,int& column)
{
    std::vector<std::function<void(QGridLayout*&, int&, int&)>> functionCalls;
    QLayoutItem* item;
    item = gridLayout->itemAtPosition(row - 1, column);
    if (item == nullptr) {
        functionCalls.push_back([this](QGridLayout*& gridLayout, int& row, int& column) {
            addRowTop(gridLayout, row, column);
            });
    };
    item = gridLayout->itemAtPosition(row, column - 1);
    if (item == nullptr) {
        functionCalls.push_back([this](QGridLayout*& gridLayout, int& row, int& column) {
            addColumnLeft(gridLayout, row, column);
            });
    }
    item =gridLayout->itemAtPosition(row, column + 1);
    if(item == nullptr)
        functionCalls.push_back([this](QGridLayout*& gridLayout, int& row, int& column) {
            addColumnRight(gridLayout, row, column);
            });
    item = gridLayout->itemAtPosition(row + 1, column);
    if (item == nullptr)
        functionCalls.push_back([this](QGridLayout*& gridLayout, int& row, int& column) {
            addRowBelow(gridLayout, row, column);
            });
    return functionCalls;
}

void qGameBoardWidget::stretchGridLayout(QGridLayout*& gridLayout)
{
    // Stretch all rows equally
    for (int i = 0; i < gridLayout->rowCount(); ++i)
        gridLayout->setRowStretch(i, 1);

    // Stretch all columns equally
    for (int j = 0; j < gridLayout->columnCount(); ++j)
        gridLayout->setColumnStretch(j, 1);
}

void qGameBoardWidget::createFixedSizeBoard(QGridLayout*& gridLayout)
{
    clearBoard(gridLayout);

    m_emptyPositions.clear();

    gridLayout->setSpacing(0); // No spacing between cells
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (auto& card : m_cardPosition)
    {

        auto& [position, cardLabel] = card;
        auto& [row, column] = position;

        bool hasAdjacentCard = false;
        std::vector<std::pair<int, int>> adjacentPositions = {
            {row - 1, column},
            {row + 1, column},
            {row, column - 1},
            {row, column + 1},
            {row - 1, column - 1},
            {row - 1, column + 1},
            {row + 1, column - 1},
            {row + 1, column + 1}
        };

        for (const auto& [adjRow, adjCol] : adjacentPositions)
        {
            if (adjRow >= minRow && adjRow <= BOARD_MAX_SIZE && adjCol >= minRow && adjCol <= BOARD_MAX_SIZE
                && m_cardPosition.find({ adjRow, adjCol }) == m_cardPosition.end())
            {
                m_emptyPositions.insert(std::make_pair(adjRow, adjCol));

                QLayoutItem* existingItem = gridLayout->itemAtPosition(adjRow, adjCol);
                if (existingItem)
                {
                    QWidget* existingWidget = existingItem->widget();
                    if (existingWidget)
                    {
                        delete existingWidget;
                    }
                }

                QLabel* whiteSpace = createWhiteSpace();
                gridLayout->addWidget(whiteSpace, adjRow, adjCol);
            }
        }

        if (m_pixmapPosition.find({ row, column }) != m_pixmapPosition.end())
        {
            qDebug() << "Found pixmap for position:" << row << "," << column;
            qDebug() << "Pixmap:" << m_pixmapPosition[{row, column}];
            cardLabel->setPixmap(m_pixmapPosition[{row, column}]);
        }
        else
        {
            qDebug() << "No pixmap found for position:" << row << "," << column;
        }
        cardLabel->setProperty("type", "minion");
        cardLabel->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
        cardLabel->setAlignment(Qt::AlignCenter);
        cardLabel->show();
        int toAddRow = row, toAddColumn = column;
        addNewMinionCardToGrid(cardLabel, gridLayout, toAddRow, toAddColumn);

        qDebug() << "Card placed at:" << row << "," << column << '\n';
    }
    int newHeight = (gridLayout->rowCount() * CARD_HEIGTH) +
        gridLayout->contentsMargins().top() +
        gridLayout->contentsMargins().bottom();

    int newWidth = (gridLayout->columnCount() * CARD_WIDTH) +
        gridLayout->contentsMargins().left() +
        gridLayout->contentsMargins().right();

    QWidget* parentWidget = gridLayout->parentWidget();
    if (parentWidget) {
        parentWidget->resize(newWidth, newHeight);
    }

    stretchGridLayout(gridLayout);
}

void qGameBoardWidget::rearrangeCards(QGridLayout*& gridLayout)
{
    std::unordered_map<std::pair<int, int>, QLabel*, PairHash1> updatedCardPosition;
    std::unordered_map<std::pair<int, int>, QPixmap, PairHash1> updatedPixmapPosition;
    for (const auto& card : m_cardPosition)
    {
        const auto& [position, cardLabel] = card;
        const auto& [row, column] = position;
        updatedCardPosition.insert(std::make_pair(std::make_pair(row - 1, column - 1), cardLabel));
    }

    for (const auto& pixmap : m_pixmapPosition)
    {
        const auto& [position, cardPixmap] = pixmap;
        const auto& [row, column] = position;
        updatedPixmapPosition.insert(std::make_pair(std::make_pair(row - 1, column - 1), cardPixmap));
    }

    m_cardPosition = std::move(updatedCardPosition);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}

void qGameBoardWidget::alignCardsToTopLeft()
{
    int xOffset = this->contentsMargins().left();  // Left margin offset
    int yOffset = this->contentsMargins().top();   // Top margin offset

    for (const auto& [position, cardLabel] : m_cardPosition)
    {
        const auto& [row, column] = position;
        int x = column * CARD_WIDTH + xOffset;  // Calculate x based on column
        int y = row * CARD_HEIGTH + yOffset;   // Calculate y based on row

        if (cardLabel)
        {
            cardLabel->setGeometry(x, y, CARD_WIDTH, CARD_HEIGTH);  // Move the QLabel
            cardLabel->show();  // Ensure it's visible
        }
    }

    for (const auto& emptySpace : m_emptyPositions)
    {
        const auto& [row, column] = emptySpace;
        int x = column * CARD_WIDTH + xOffset;
        int y = row * CARD_HEIGTH + yOffset;

        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(layout());
        if (gridLayout) {
            QLayoutItem* item = gridLayout->itemAtPosition(row, column);
            if (item && item->widget()) {
                item->widget()->setGeometry(x, y, CARD_WIDTH, CARD_HEIGTH);
                item->widget()->show();
            }
        }
    }

    update();  // Repaint the widget to reflect changes
}

void qGameBoardWidget::updateMinMaxRowCol()
{
    for (auto& card : m_cardPosition)
    {
        auto& [position, cardLabel] = card;
        auto& [row, column] = position;
        if (row > maxRow)
            maxRow = row;
        if (column > maxColumn)
        maxColumn = column;
        if (row < minRow)
            minRow = row;
        if (column < minColumn)
            minColumn = column;
    }
}


