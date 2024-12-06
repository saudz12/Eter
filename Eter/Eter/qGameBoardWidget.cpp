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
        // Cast the layout to QGridLayout
        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
        if (gridLayout)
        {
            QLayoutItem* item = gridLayout->itemAtPosition(row, col);
            if (item) {
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                if (label->property("type") == "empty") {
                    label->setProperty("type", "minion card");
                    label->setPixmap(newCardLabel->pixmap().copy());
                    currCardPixmap = newCardLabel->pixmap();
                    expandBoard(row, col);
                    
                    redrawBoard(gridLayout);
                }
            }
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

    //pt primul card pus
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
    if (rowsWithEmptySpaces == 1 && columnsWithEmptySpaces == 1)
    {
        placeFirstCard(gridLayout,row,column);
        m_cardPosition.erase(std::make_pair(0, 0));
        return;
    }

    existsOnLeftCol = false;
    existsOnRightCol = false;
    existsOnTopRow = false;
    existsOnBottomRow = false;

    std::unordered_set<std::pair<int, int>, PairHash1> vCreateWhiteSpaces=checkPositionsForWhiteSpaces(gridLayout,row,column,
        existsOnLeftCol, existsOnRightCol, existsOnTopRow, existsOnBottomRow);
    
    qDebug() << "leftcol:" << existsOnLeftCol
        << "\nrightcol:" << existsOnRightCol
        << "\ntopRow:" << existsOnTopRow
        << "\nbottomRow" << existsOnBottomRow << '\n';
    
    if (vCreateWhiteSpaces.empty())
        return;

    if (existsOnBottomRow == false && existsOnLeftCol == false && existsOnRightCol == false && existsOnTopRow == false)
        return;

    std::vector<std::pair<std::function<void(QGridLayout*&, int&, int&)>,bool>> functionCalls = createFunctionCallsVector();

    for (int i=0;i<functionCalls.size();++i)
    {
        const auto& [function, exists] = functionCalls[i];
        if (exists==false)
        {
            function(gridLayout, row, column);
            qDebug() << i << '\n';
        }
    }
    QLabel* newCard = createNewMinionCard();
    addNewMinionCardToGrid(newCard, gridLayout, row, column);
}

std::unordered_set<std::pair<int, int>, PairHash1> qGameBoardWidget::checkPositionsForWhiteSpaces(QGridLayout*& gridLayout, int row, int column,
    bool& existsOnLeftCol, bool& existsOnRightCol, bool& existsOnTopRow, bool& existsOnBottomRow)
{
    //existOnLeftColumn
    std::unordered_set<std::pair<int, int>, PairHash1> vCreateWhiteSpaces;
    if (checkPosition(gridLayout, row - 1, column - 1))
        existsOnLeftCol = true;
    else
        vCreateWhiteSpaces.emplace(row - 1, column - 1);
    
    if (checkPosition(gridLayout, row, column - 1))
        existsOnLeftCol = true;
    else
        vCreateWhiteSpaces.emplace(row, column - 1);
    
    if (checkPosition(gridLayout, row + 1, column - 1))
        existsOnLeftCol = true;
    else
        vCreateWhiteSpaces.emplace(row + 1, column - 1);
    
    //existsOnRightColumn
    if (checkPosition(gridLayout, row - 1, column + 1))
        existsOnRightCol = true;
    else
        vCreateWhiteSpaces.emplace(row - 1, column + 1);

    if (checkPosition(gridLayout, row, column + 1))
        existsOnRightCol = true;
    else
        vCreateWhiteSpaces.emplace(row, column + 1);

    if (checkPosition(gridLayout, row + 1, column + 1))
        existsOnRightCol = true;
    else
        vCreateWhiteSpaces.emplace(row + 1, column + 1);

    //existsOnTopRow

    if (checkPosition(gridLayout, row-1, column - 1))
        existsOnTopRow = true;
    else
        vCreateWhiteSpaces.emplace(row-1, column - 1);

    if (checkPosition(gridLayout, row-1, column))
        existsOnTopRow = true;
    else
        vCreateWhiteSpaces.emplace(row-1, column );

    if (checkPosition(gridLayout, row -1, column + 1))
        existsOnTopRow = true;
    else
        vCreateWhiteSpaces.emplace(row - 1, column + 1);

    //existsOnBottomRow
    if (checkPosition(gridLayout, row + 1, column - 1))
        existsOnBottomRow = true;
    else
        vCreateWhiteSpaces.emplace(row + 1, column - 1);

    if (checkPosition(gridLayout, row + 1, column))
        existsOnBottomRow = true;
    else
        vCreateWhiteSpaces.emplace(row + 1, column);

    if (checkPosition(gridLayout, row + 1, column + 1))
        existsOnBottomRow = true;
    else
        vCreateWhiteSpaces.emplace(row + 1, column + 1);

    

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

QLabel* qGameBoardWidget::createWhiteSpace()
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

void qGameBoardWidget::addRowBelow(QGridLayout*& gridLayout, int& row,int& column)
{
    for (int j = column; j <=column+2; ++j)
    {
        QLabel* whiteSpace = createWhiteSpace();
        whiteSpace->setProperty("type", "empty");
        gridLayout->addWidget(whiteSpace, row + 1, j);
        m_emptyPositions.emplace(std::make_pair(row + 1, j));
    }
    gridLayout->setRowStretch(gridLayout->rowCount() , 1); 
    gridLayout->setColumnStretch(gridLayout->columnCount() , 1);
    // Resize the widget dynamically
    int newHeight = (gridLayout->columnCount() * CARD_HEIGTH);
    int newWidth = (gridLayout->rowCount() * CARD_WIDTH);
    this->resize(newWidth, newHeight);
}

void qGameBoardWidget::addColumnRight(QGridLayout*& gridLayout, int& row, int& column)
{
    
}

void qGameBoardWidget::addRowTop(QGridLayout*& gridLayout, int& row, int& column)
{
}

void qGameBoardWidget::addColumnLeft(QGridLayout*& gridLayout, int& row, int& column)
{
    std::unordered_set<std::pair<int, int>, PairHash1> updatedEmptyPositions;
    for (auto it = m_emptyPositions.begin(); it != m_emptyPositions.end(); ++it)
    {
        auto [row, column] = *it;

        updatedEmptyPositions.emplace(std::make_pair(row, column + 1));
    }
    m_emptyPositions = std::move(updatedEmptyPositions);
    std::unordered_map<std::pair<int, int>, QLabel*, PairHash1> updatedCardPositions;
    std::unordered_map<std::pair<int, int>, QPixmap, PairHash1> updatedPixmapPosition;
    //coloana din stanga
    for (auto it = m_cardPosition.begin(); it != m_cardPosition.end(); ++it)
    {
        auto& [position, card] = *it;
        auto& [row, column] = position;
        updatedCardPositions.emplace(std::make_pair(std::make_pair(row, column + 1), card));
    }

    for (auto it = m_pixmapPosition.begin(); it != m_pixmapPosition.end(); ++it)
    {
        auto& [position, pixmap] = *it;
        auto& [row, column] = position;
        updatedPixmapPosition.emplace(std::make_pair(std::make_pair(row, column + 1), pixmap));
    }

    m_cardPosition = std::move(updatedCardPositions);
    m_pixmapPosition = std::move(updatedPixmapPosition);

    for (int i = row - 1; i <= row + 1; ++i)
    {
        QLabel* whiteSpace = createWhiteSpace();
        whiteSpace->setProperty("type", "empty");
        gridLayout->addWidget(whiteSpace, i, column);
        m_emptyPositions.emplace(std::make_pair(i, column));
    }

    int newHeight = (gridLayout->columnCount() * CARD_HEIGTH);//+ gridLayout->contentsMargins().top() + gridLayout->contentsMargins().bottom();
    int newWidth = (gridLayout->rowCount() * CARD_WIDTH);//+ gridLayout->contentsMargins().left() + gridLayout->contentsMargins().right();
    this->resize(newWidth, newHeight);
    column++;
}

void qGameBoardWidget::redrawBoard(QGridLayout*& gridLayout) {
    clearBoard(gridLayout);

    // Remove and replace empty spaces
    for (const auto& emptySpace : m_emptyPositions) {
        const auto& [row, column] = emptySpace;
        gridLayout->addWidget(createWhiteSpace(), row, column);
        qDebug() << "empty:" << row << "," << column << '\n';
    }
    for (auto& pixmap : m_pixmapPosition)
    {
        auto& [pos, image] = pixmap;
        qDebug() << pos.first << " " << pos.second << "\n";
        qDebug() << image<<'\n';
    }
    // Remove previous cards and add new ones
    for (auto& card : m_cardPosition) {
        auto& [position, cardLabel] = card;
        auto& [row, column] = position;

        // Remove previous card at the same position
        QLayoutItem* existingItem = gridLayout->itemAtPosition(row, column);
        if (existingItem) {
            QWidget* existingWidget = existingItem->widget();
            if (existingWidget) {
                // Delete the previous card (QLabel)
                delete existingWidget;
            }
            //delete existingItem;  // Delete the layout item itself
        }

        // Set the pixmap to the new card
        if (m_pixmapPosition.find({row, column}) != m_pixmapPosition.end()) {
            qDebug() << "Found pixmap for position:" << row << "," << column;
            qDebug() << "Pixmap:" << m_pixmapPosition[{row, column}];
            cardLabel->setPixmap(m_pixmapPosition[{row, column}]);
        } else {
            qDebug() << "No pixmap found for position:" << row << "," << column;
        }

        cardLabel->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
        cardLabel->show();

        // Add the new card to the grid layout
        gridLayout->addWidget(cardLabel, row, column);

        qDebug() << "Card placed at:" << row << "," << column << '\n';
    }
}


void qGameBoardWidget::clearBoard(QGridLayout*& gridLayout) {
    if (!gridLayout) return;
    std::vector<QLabel> vCardLabels;
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->hide();  // Hide instead of delete
        }
        delete item; // Delete the layout item itself
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

    for (size_t i = 0; i < rows + 2; ++i)
    {
        for (size_t j = 0; j < columns + 2; ++j)
        {
            if (!(i == 1 && j == 1))
            {
                QLabel* emptySpace = createWhiteSpace();
                emptySpace->setProperty("type", "empty");
                gridLayout->addWidget(emptySpace, i, j);
                if (m_emptyPositions.find({ i,j }) == m_emptyPositions.end())
                    m_emptyPositions.emplace(std::make_pair(i, j));
            }
        }
    }

    QLabel* label = new QLabel(this);
    label->setPixmap(pixmapFirstCard);
    label->setProperty("type", "minion");
    label->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
    m_cardPosition.emplace(std::make_pair(std::make_pair(row, column), label));
    m_pixmapPosition.emplace(std::make_pair(std::make_pair(row,column), label->pixmap().copy()));

    m_cardPosition.erase(std::make_pair(0, 0));
    m_pixmapPosition.erase(std::make_pair(0, 0));
    this->resize(gridLayout->columnCount() * CARD_HEIGTH, gridLayout->rowCount() * CARD_WIDTH);
}

QLabel* qGameBoardWidget::createNewMinionCard()
{
    QLabel* newCard = new QLabel(this);
    newCard->setPixmap(currCardPixmap);
    newCard->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
    newCard->setProperty("type", "minion");
    return newCard;
}

void qGameBoardWidget::addNewMinionCardToGrid(QLabel*& newCard, QGridLayout*& gridLayout, int& row, int& column)
{
    m_cardPosition.emplace(std::make_pair(std::make_pair(row, column), newCard));
    m_pixmapPosition.emplace(std::make_pair(std::make_pair(row, column), newCard->pixmap()));
}

std::vector<std::pair<std::function<void(QGridLayout*&, int&, int&)>, bool>> qGameBoardWidget::createFunctionCallsVector()
{
    std::vector<std::pair<std::function<void(QGridLayout*&, int&, int&)>, bool>> functionCalls;

    functionCalls.push_back(std::make_pair([this](QGridLayout*& gridLayout, int& row, int& column) {
        addRowTop(gridLayout, row, column);
        }, existsOnTopRow));
    functionCalls.push_back(std::make_pair(([this](QGridLayout*& gridLayout, int& row, int& column) {
        addColumnLeft(gridLayout, row, column);
        }), existsOnLeftCol));
    functionCalls.push_back(std::make_pair([this](QGridLayout*& gridLayout, int& row, int& column) {
        addColumnRight(gridLayout, row, column);
        }, existsOnRightCol));
    functionCalls.push_back(std::make_pair([this](QGridLayout*& gridLayout, int& row, int& column) {
        addRowBelow(gridLayout, row, column);
        }, existsOnBottomRow));
    return functionCalls;
}


