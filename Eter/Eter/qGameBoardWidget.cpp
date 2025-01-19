#include "qGameBoardWidget.h"

qGameBoardWidget::qGameBoardWidget(QWidget* parent, int board_max_size, int card_width, int card_heigth, int spacing) :
    QWidget{ parent },
    CARD_WIDTH{ card_width },
    CARD_HEIGTH{ card_heigth },
    BOARD_MAX_SIZE{ board_max_size },
    wasIllusionChecked{false},
    isCurrentCardIllusion{false}
{
    setAcceptDrops(true);

    wasFirstCardPlaced = false;

    maxRow = maxColumn = 0;

    minRow = minColumn = 10;

    gridLayout = new QGridLayout(this);
    setLayout(gridLayout);
}

void qGameBoardWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction(); 
    }
    else {
        event->ignore(); 
    }
}

void qGameBoardWidget::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasText())
    {
        if (event->mimeData()->property("type") == QString("minion"))
        {
            handleMinionCardDrop(event);
        }
    }
}

void qGameBoardWidget::handleMinionCardDrop(QDropEvent* event)
{
    QPoint dropPosition = event->position().toPoint();

    int row = dropPosition.y() / CARD_HEIGTH;
    int col = dropPosition.x() / CARD_WIDTH;

    qDebug() << "determined row:" << row << " determined column:" << col << '\n';

    QLabel* newCardLabel=nullptr;

    if (event->mimeData()->hasFormat("application/x-card-pixmap")) 
    {
        newCardLabel = setupCurrentCard(event, row, col);
    }
    const int originalRow = row, originalCol = col;
    if (gridLayout)
    {
        QLayoutItem* item = gridLayout->itemAtPosition(row, col);

        if (item)
        {
            QLabel* label = qobject_cast<QLabel*>(item->widget());
            if (label->property("type") == QString("empty"))
            {
                handleMinionCardPlaceOnEmptySpace(newCardLabel,label,row,col);
            }
            else if (m_cardPosition[{row, col}].back()->property("isIllusion").toBool()==true
                && currentCardValue < m_cardPosition[{row, col}].back()->property("value").toInt() && !isEterCard)
            {
                coverIllusion( label, row, col);
            }
            else if (label->property("type") == QString("minion"))
            {

                qDebug() << m_cardPosition[{row, col}].back()->property("isIllusion").toBool() << " " << isCurrentCardIllusion << '\n';;
                if (m_cardPosition[{row, col}].back()->property("isEter").toBool() == true)// ceva peste eter
                {

                }
                else if (isCurrentCardIllusion) // iluzie peste card
                {

                }
                else if (currentCardValue > m_cardPosition[{row, col}].back()->property("value").toInt())
                {
                    handleMinionCardPlaceOnTop(label, newCardLabel, row, col);
                }
            }
        }
    }
    for (auto& cardStack : m_cardPosition)
    {
        qDebug() << cardStack.first.first << " " << cardStack.first.second << ":";
        for (int i = 0; i < cardStack.second.size(); ++i)
        {
            qDebug() << cardStack.second[i]->property("value").toString() << " ";
        }
        qDebug() << '\n';
    }
    event->acceptProposedAction();
    emit cardDropAccepted(event->mimeData(), originalRow,originalCol);
}


void qGameBoardWidget::resizeEvent(QResizeEvent* event)
{
    emit boardResized();
    QWidget::resizeEvent(event);
}

void qGameBoardWidget::expandBoard(int& row, int& column)
{

    if (wasFirstCardPlaced==false)
    {
        wasFirstCardPlaced = true;
        placeFirstCard( row, column);
        QLabel* newCard = createNewMinionCard();

        return;
    }

    std::vector<std::function<void(int&, int&)>> functionCalls = createFunctionCallsVector(row,column);

    for (int i = 0; i < functionCalls.size(); ++i)
    {
        functionCalls[i]( row, column);
    }
    QLabel* newCard = createNewMinionCard();
    addNewMinionCardToGrid(newCard,row, column);
}

void qGameBoardWidget::setBoardPosition(const int x, const int y, const int card_width, const int card_height)
{
    setGeometry(x, y, card_width, card_height);
    setupEmptyBoard();
}

void qGameBoardWidget::addWidgetOnBoard(QPointer<qDraggableLabel>& card, int row, int column)
{
    gridLayout->addWidget(card, row, column);
}

void qGameBoardWidget::setupEmptyBoard()
{
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

int16_t qGameBoardWidget::verifyTopCardsExist(const int& row,const int& column)
{
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
    return addRow;
}

int16_t qGameBoardWidget::verifyLeftCardsExist( const int& row, const int& column)
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
    return addColumn;
}

int16_t qGameBoardWidget::verifyBottomCardsExist( const int& row, const int& column)
{
    bool existsCards = false;
    bool isRowEmpty = false;
    int addRow = 1;
    for (int i = column - 1; i <= column + 1; i++)
    {
        QLayoutItem* item = gridLayout->itemAtPosition(row + 1, i);
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
    return addRow;
}

int16_t qGameBoardWidget::verifyRightCardsExist( const int& row, const int& column)
{
    bool existsCards = false;
    bool isColEmpty = false;
    int addColumn = 1;
    for (int j = row - 1; j <= row + 1; j++)
    {
        QLayoutItem* item = gridLayout->itemAtPosition(j, column + 1);
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
    return addColumn;
}

void qGameBoardWidget::updateCardsForTopRow( const int& row, const int& column,const int& addRow)
{
    std::unordered_set<std::pair<int, int>, PairHash1> updatedEmptyPositions;
    for (auto it = m_emptyPositions.begin(); it != m_emptyPositions.end(); ++it)
    {
        auto [oldRow, oldColumn] = *it;
        updatedEmptyPositions.emplace(std::make_pair(oldRow + addRow, oldColumn));
    }
    m_emptyPositions = std::move(updatedEmptyPositions);

    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> updatedCardPositions;
    for (auto it = m_cardPosition.begin(); it != m_cardPosition.end(); ++it)
    {
        auto& [position, card] = *it;
        auto& [oldRow, oldColumn] = position;
        updatedCardPositions.emplace(std::make_pair(std::make_pair(oldRow + addRow, oldColumn), card));
    }

    std::unordered_map<std::pair<int, int>,std::deque<QPixmap>, PairHash1> updatedPixmapPosition;
    for (auto it = m_pixmapPosition.begin(); it != m_pixmapPosition.end(); ++it)
    {
        auto& [position, pixmap] = *it;
        auto& [oldRow, oldColumn] = position;
        updatedPixmapPosition.emplace(std::make_pair(std::make_pair(oldRow + addRow, oldColumn), pixmap));
    }

    m_cardPosition = std::move(updatedCardPositions);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}

void qGameBoardWidget::updateCardsForLeftCol( const int& row, const int& column, const int& addColumn)
{
    std::unordered_set<std::pair<int, int>, PairHash1> updatedEmptyPositions;
    for (auto it = m_emptyPositions.begin(); it != m_emptyPositions.end(); ++it)
    {
        auto [row, column] = *it;

        updatedEmptyPositions.emplace(std::make_pair(row, column + addColumn));
    }
    m_emptyPositions = std::move(updatedEmptyPositions);

    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> updatedCardPositions;
    std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> updatedPixmapPosition;

    for (auto it = m_cardPosition.begin(); it != m_cardPosition.end(); ++it)
    {
        auto& [position, card] = *it;
        auto& [row, column] = position;
        updatedCardPositions.emplace(std::make_pair(std::make_pair(row, column + addColumn),card));
    }

    for (auto it = m_pixmapPosition.begin(); it != m_pixmapPosition.end(); ++it)
    {
        auto& [position, pixmap] = *it;
        auto& [row, column] = position;
        updatedPixmapPosition.emplace(std::make_pair(std::make_pair(row, column + addColumn), pixmap));
    }

    m_cardPosition = std::move(updatedCardPositions);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}

bool qGameBoardWidget::checkPosition( int i, int j)
{
    return (m_cardPosition.find({ i,j }) == m_cardPosition.end());
}

void qGameBoardWidget::addRowBelow( int& row, int& column)
{
    qDebug() << "added row below\n";
    if (maxRow-minRow+1 == BOARD_MAX_SIZE)
        return;
    for (int j = column - 1; j <= column + 1; ++j)
    {
        m_emptyPositions.emplace(std::make_pair(row + 1, j));
    }
}

void qGameBoardWidget::addColumnRight( int& row, int& column)
{
    qDebug() << "added column right\n";
    if (maxColumn-minRow+1 == BOARD_MAX_SIZE)
        return;
    for (int i = row - 1; i <= row + 1; ++i)
    {
        m_emptyPositions.emplace(std::make_pair(i, column + 1));
    }
}

void qGameBoardWidget::addRowTop( int& row, int& column)
{
    qDebug() << "added row top";

    int addRow = verifyTopCardsExist(row,column);

    if (maxRow-minRow+1 == BOARD_MAX_SIZE)
        return;
    if (addRow == 1)
    {
        updateCardsForTopRow( row, column,addRow);
    }
    for (int j = column - 1; j <= column + 1; ++j)
    {
        m_emptyPositions.emplace(std::make_pair(row+addRow-1, j));
    }
    
    row+=addRow;
}

void qGameBoardWidget::addColumnLeft( int& row, int& column)
{
    qDebug() << "added column left\n";

    int addColumn = verifyLeftCardsExist( row, column);

    if (maxColumn-minColumn+1 == BOARD_MAX_SIZE)
        return;

    if (addColumn == 1)
    {
        updateCardsForLeftCol( row, column, addColumn);
    }
    for (int i = row - 1; i <= row + 1; ++i)
    {
        m_emptyPositions.emplace(std::make_pair(i , column + addColumn - 1));
    }
    
    column+=addColumn;
}

void qGameBoardWidget::clearBoard() {
    if (!gridLayout) return;
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->hide();  // Hide instead of delete
        }
        delete item;
    }
}

void qGameBoardWidget::placeFirstCard( int& row, int& column)
{
    row = column = 1;
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
    removeWidgetFromGrid( 0, 0);
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
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
    label->setPixmap(currCardPixmap);
    addNewMinionCardToGrid(label, row, column);

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

void qGameBoardWidget::addNewMinionCardToGrid(QLabel*& newCard, int& row, int& column)
{
    newCard->setProperty("value", currentCardValue);
    newCard->setProperty("color", currentCardColor);
    newCard->setProperty("isIllusion", isCurrentCardIllusion);
    newCard->setProperty("isEter", isEterCard);
    m_cardPosition[{row, column}].emplace_back(newCard);
    m_pixmapPosition[{row, column}].emplace_back(newCard->pixmap());
    gridLayout->addWidget(newCard, row, column);
}

void qGameBoardWidget::removeWidgetFromGrid( int row, int column)
{
    QLayoutItem* item = gridLayout->itemAtPosition(row, column);
    if (item) {
        QWidget* widget = item->widget();
        if (widget) {

            //widget->deleteLater(); // Optionally delete the widget
            widget->hide();
            gridLayout->removeWidget(widget);
            if(!m_cardPosition[{row,column}].empty())
                m_cardPosition[{ row, column }].pop_back();
            if(!m_pixmapPosition[{row,column}].empty())
                m_pixmapPosition[{ row, column }].pop_back();
            //delete item; // Delete the layout item
        }
    }
    updateMinMaxRowCol();
}

std::vector<std::function<void(int&, int&)>> qGameBoardWidget::createFunctionCallsVector( int& row,int& column)
{
    std::vector<std::function<void(int&, int&) >> functionCalls;
    QLayoutItem* item;
    bool enteredHere = false;
    item = gridLayout->itemAtPosition(row, column - 1);
    if (item == nullptr || item != nullptr && verifyLeftCardsExist(row, column) == 0) {
        functionCalls.push_back([&enteredHere,this](int& row, int& column) {
            addColumnLeft(row, column);
            });
    }
    
    if (!enteredHere)
    {
        item = gridLayout->itemAtPosition(row - 1, column);
        if (item == nullptr || item != nullptr && verifyTopCardsExist(row, column) == 0) {
            functionCalls.push_back([this](int& row, int& column) {
                addRowTop(row, column);
                });
        };
    }
    item =gridLayout->itemAtPosition(row, column + 1);
    if(item == nullptr || item!=nullptr && verifyRightCardsExist(row,column)==0)
        functionCalls.push_back([this]( int& row, int& column) {
            addColumnRight( row, column);
            });
    item = gridLayout->itemAtPosition(row + 1, column);
    if (item == nullptr || item != nullptr && verifyBottomCardsExist( row, column) == 0)
        functionCalls.push_back([this]( int& row, int& column) {
            addRowBelow( row, column);
            });
    return functionCalls;
}

void qGameBoardWidget::stretchGridLayout()
{
    for (int i = 0; i < gridLayout->rowCount(); ++i)
        gridLayout->setRowStretch(i, 1);

    for (int j = 0; j < gridLayout->columnCount(); ++j)
        gridLayout->setColumnStretch(j, 1);

    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
}

void qGameBoardWidget::createBoard()
{
    clearBoard();

    m_emptyPositions.clear();

    stretchGridLayout();

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
        if (!cardLabel.empty())
        {
            for (const auto& [adjRow, adjCol] : adjacentPositions)
            {
                if (m_cardPosition.find({ adjRow, adjCol }) == m_cardPosition.end())
                {
                    if (BOARD_MAX_SIZE == maxColumn - minColumn + 1 &&
                        maxRow - minRow + 1 == BOARD_MAX_SIZE)
                    {
                        if (adjRow >= minRow && adjRow <= BOARD_MAX_SIZE && adjCol >= minColumn && adjCol <= BOARD_MAX_SIZE)
                        {
                            m_emptyPositions.insert({ adjRow,adjCol });
                        }
                        else
                            continue;
                    }
                    else if (BOARD_MAX_SIZE == maxColumn - minColumn + 1)
                    {
                        if (adjCol >= minColumn && adjCol <= BOARD_MAX_SIZE)
                        {
                            m_emptyPositions.insert({ adjRow,adjCol });
                        }
                    }
                    else if (maxRow - minRow + 1 == BOARD_MAX_SIZE)
                    {
                        if (adjRow >= minRow && adjRow <= BOARD_MAX_SIZE)
                        {
                            m_emptyPositions.insert({ adjRow,adjCol });
                        }
                    }
                    else
                        m_emptyPositions.insert({ adjRow,adjCol });
                }
            }
        }
        else
            m_emptyPositions.insert({ row,column });
    }

    addCardsToRedrawnBoard();

    addEmptySpacesToRedrawnBoard();

    int newHeight = (gridLayout->rowCount() * CARD_HEIGTH) +
        gridLayout->contentsMargins().top() +
        gridLayout->contentsMargins().bottom();

    int newWidth = (gridLayout->columnCount() * CARD_WIDTH) +
        gridLayout->contentsMargins().left() +
        gridLayout->contentsMargins().right();

    QWidget* parentWidget = gridLayout->parentWidget();
    if (parentWidget) 
    {
        parentWidget->resize(newWidth, newHeight);
    }
}

void qGameBoardWidget::updateMinMaxRowCol()
{
    minRow = minColumn = 10;
    maxRow = maxColumn = -1;
    for (auto& card : m_cardPosition)
    {
        auto& [position, cardLabel] = card;
        auto& [row, column] = position;
        if (!cardLabel.empty())
        {
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
}

void qGameBoardWidget::createEmptySpacesForRedrawnBoard()
{
    std::unordered_set<std::pair<int, int>, PairHash1> validEmptySpaces;

    for (const auto& cardPositon : m_cardPosition)
    {
        const auto& [position, labelCard] = cardPositon;
        const auto& [row, column] = position;
        qDebug() << "size:"<<labelCard.size() << '\n';
        if (!labelCard.empty() && labelCard.size())
        {
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
                if (/*adjRow >= minRow && adjRow <= BOARD_MAX_SIZE && adjCol >= minColumn && adjCol <= BOARD_MAX_SIZE && */
                    m_cardPosition.find({ adjRow, adjCol }) == m_cardPosition.end() || m_cardPosition[{adjRow, adjCol}].empty())
                {
                    if (BOARD_MAX_SIZE == maxColumn - minColumn + 1)
                    {
                        if (adjCol >= minColumn && adjCol <= BOARD_MAX_SIZE)
                        {
                            validEmptySpaces.insert({ adjRow,adjCol });
                        }
                    }
                    else if (maxRow - minRow + 1 == BOARD_MAX_SIZE)
                    {
                        if (adjRow >= minRow && adjRow <= BOARD_MAX_SIZE)
                        {
                            validEmptySpaces.insert({ adjRow,adjCol });
                        }
                    }
                    else
                        validEmptySpaces.insert({ adjRow,adjCol });
                }
            }
        }
    }

    m_emptyPositions = std::move(validEmptySpaces);
}

void qGameBoardWidget::addCardsToRedrawnBoard()
{
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
            if (!m_pixmapPosition[{row, column}].empty() && !cardLabel.empty())
            {
                cardLabel.back()->setPixmap(m_pixmapPosition[{row, column}].back());
            }
        }
        if (!cardLabel.empty())
        {
            cardLabel.back()->setProperty("type", "minion");
            cardLabel.back()->setFixedSize(CARD_WIDTH, CARD_HEIGTH);
            cardLabel.back()->show();
            int toAddRow = row, toAddColumn = column;
            //addNewMinionCardToGrid(cardLabel.back(), gridLayout, toAddRow, toAddColumn);
            gridLayout->addWidget(cardLabel.back(), toAddRow, toAddColumn);
            qDebug() << "Card placed at:" << row << "," << column << '\n';
        }
    }
}

void qGameBoardWidget::loadIllusion(Colours color)
{
    QString dirIllusion = QDir::currentPath() + "/textures/";
    QString colorPath;
    if (color == Colours::BLUE)
        colorPath = "blue_back.jpg";
    else
        colorPath = "red_back.jpg";
    QPixmap pixmap{ dirIllusion + colorPath};
    currCardPixmap = pixmap;
}

void qGameBoardWidget::scaleCoordinates(int& row, int& col)
{
    row++;
    col++;
}

QLabel* qGameBoardWidget::setupCurrentCard(QDropEvent* event, int row, int col)
{
    QLabel* newCardLabel = new QLabel(this);
    isCurrentCardIllusion = false; 

    QByteArray pixmapData = event->mimeData()->data("application/x-card-pixmap");
    QDataStream stream(&pixmapData, QIODevice::ReadOnly);
    QPixmap droppedCardPixmap;
    stream >> droppedCardPixmap;
    bool isIllusionChecked = false;
    emit isRadioButtonToggledIllusions(&isIllusionChecked);
    if (isIllusionChecked == true)
    {
        loadIllusion(GetColour(event->mimeData()->property("color").toString().toLatin1().at(0)));
        droppedCardPixmap = currCardPixmap;
        isCurrentCardIllusion = true;
    }

    newCardLabel->setPixmap(droppedCardPixmap.scaled(CARD_WIDTH, CARD_HEIGTH));

    currentCardValue = event->mimeData()->property("value").toInt();
    currentCardColor = event->mimeData()->property("color").toString();
    isEterCard = event->mimeData()->property("isEter").toBool();
    return newCardLabel;
}

void qGameBoardWidget::coverIllusion(QLabel* label,int& row,int& col)
{
    label = createNewMinionCard();
    QString dir = QDir::currentPath() + "/textures/";
    if (currentCardColor == GetColour(Colours::RED))
    {
        QPixmap underneathCard(dir + QString("blue_") + QString::number(m_cardPosition[{row, col}].back()->property("value").toInt()) + QString(".jpg"));
        underneathCard = underneathCard.scaled(CARD_WIDTH, CARD_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        qDebug() << dir + QString("blue_" + m_cardPosition[{row, col}].back()->property("value").toInt() + QString(".jpg"));
        currCardPixmap = underneathCard;
        label->setPixmap(underneathCard);
    }
    else
    {
        QPixmap underneathCard(dir + QString("red_") + QString::number(m_cardPosition[{row, col}].back()->property("value").toInt()) + QString(".jpg"));
        qDebug() << dir + QString("red_" + m_cardPosition[{row, col}].back()->property("value").toInt() + QString(".jpg"));
        underneathCard = underneathCard.scaled(CARD_WIDTH, CARD_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        currCardPixmap = underneathCard;
        label->setPixmap(underneathCard);
    }
    currentCardValue = m_cardPosition[{row, col}].back()->property("value").toInt();
    currentCardColor = m_cardPosition[{row, col}].back()->property("color").toString().toLatin1().at(0);
    removeWidgetFromGrid( row, col);
    addNewMinionCardToGrid(label, row, col);
}

void qGameBoardWidget::handleMinionCardPlaceOnTop(QLabel* label, QLabel* newCardLabel, int& row, int& col)
{
    currCardPixmap = newCardLabel->pixmap();
    label = createNewMinionCard();
    addNewMinionCardToGrid(label, row, col);
}

void qGameBoardWidget::handleMinionCardPlaceOnEmptySpace(QLabel* newCardLabel,QLabel* labelOnBoard,int& row,int& col)
{
    currCardPixmap = newCardLabel->pixmap();
    labelOnBoard = createNewMinionCard();
    updateMinMaxRowCol();
    expandBoard(row, col);
    updateMinMaxRowCol();
    if (wasFirstCardPlaced)
    {
        createBoard();
    }
}

void qGameBoardWidget::removeTopMargin()
{
    // New containers to store updated positions
    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> updatedCardPosition;
    std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> updatedPixmapPosition;

    // Adjust card positions
    for (const auto& [position, labels] : m_cardPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedCardPosition.emplace(std::make_pair(row - 1, col), labels);
    }

    // Adjust pixmap positions
    for (const auto& [position, pixmaps] : m_pixmapPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedPixmapPosition.emplace(std::make_pair(row - 1, col), pixmaps);
    }

    // Replace the original maps with the updated maps
    m_cardPosition = std::move(updatedCardPosition);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}


void qGameBoardWidget::removeLeftMargin()
{
    // New containers to store updated positions
    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> updatedCardPosition;
    std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> updatedPixmapPosition;

    // Adjust card positions
    for (const auto& [position, labels] : m_cardPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedCardPosition.emplace(std::make_pair(row, col - 1), labels);
    }

    // Adjust pixmap positions
    for (const auto& [position, pixmaps] : m_pixmapPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedPixmapPosition.emplace(std::make_pair(row, col - 1), pixmaps);
    }

    // Replace the original maps with the updated maps
    m_cardPosition = std::move(updatedCardPosition);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}

void qGameBoardWidget::removeBottomMargin()
{
    // New containers to store updated positions
    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> updatedCardPosition;
    std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> updatedPixmapPosition;

    // Adjust card positions
    for (const auto& [position, labels] : m_cardPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedCardPosition.emplace(std::make_pair(row + 1, col), labels);
    }

    // Adjust pixmap positions
    for (const auto& [position, pixmaps] : m_pixmapPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedPixmapPosition.emplace(std::make_pair(row + 1, col), pixmaps);
    }

    // Replace the original maps with the updated maps
    m_cardPosition = std::move(updatedCardPosition);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}

void qGameBoardWidget::removeRightMargin()
{
    // New containers to store updated positions
    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> updatedCardPosition;
    std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> updatedPixmapPosition;

    // Adjust card positions
    for (const auto& [position, labels] : m_cardPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedCardPosition.emplace(std::make_pair(row, col + 1), labels);
    }

    // Adjust pixmap positions
    for (const auto& [position, pixmaps] : m_pixmapPosition)
    {
        auto [row, col] = position;  // Extract row and column
        updatedPixmapPosition.emplace(std::make_pair(row, col + 1), pixmaps);
    }

    // Replace the original maps with the updated maps
    m_cardPosition = std::move(updatedCardPosition);
    m_pixmapPosition = std::move(updatedPixmapPosition);
}

void qGameBoardWidget::scaleCoordinatesForBoard()
{
    std::unordered_map<std::pair<int, int>, std::deque<QLabel*>, PairHash1> cardPosition;
    std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> pixmapPosition;
    for (auto& card : m_cardPosition)
    {
        auto& [row, col] = card.first;
        cardPosition.emplace(std::make_pair(row - 1, col - 1), card.second);
    }
    for (auto& pixmap : m_pixmapPosition)
    {
        auto& [row, col] = pixmap.first;
        pixmapPosition.emplace(std::make_pair(row-1, col - 1), pixmap.second);
    }
    m_cardPosition = std::move(cardPosition);
    m_pixmapPosition = std::move(pixmapPosition);
}

void qGameBoardWidget::addEmptySpacesToRedrawnBoard()
{
    for (const auto& emptySpace : m_emptyPositions)
    {
        const auto& [row, column] = emptySpace;
        gridLayout->addWidget(createWhiteSpace(), row, column);
        qDebug() << "empty:" << row << "," << column << '\n';
    }
}

void qGameBoardWidget::removeCardIllusion(int row,int col)
{
    scaleCoordinates(row, col);

    qDebug() << "row:" << row << "col:" << col << '\n';
    removeWidgetFromGrid( row, col);
    createBoard();
    QLabel* emptySpace = createWhiteSpace();
    gridLayout->addWidget(emptySpace, row, col);
    m_emptyPositions.emplace(std::make_pair(row, col));
    
}

void qGameBoardWidget::removeCard(int row, int col)
{
    scaleCoordinates(row, col);
    if (!m_cardPosition[{row, col}].empty())
    {
        removeWidgetFromGrid(row, col);
    }
}

void qGameBoardWidget::returnCard(int row, int col, int& value, Colours& color, bool& isEter, bool& isIllusion)
{
    scaleCoordinates(row, col);
    if (!m_cardPosition[{row, col}].empty())
    {
        if (gridLayout)
        {
            QLayoutItem* item = gridLayout->itemAtPosition(row, col);

            if (item)
            {
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                value = label->property("value").toInt();
                color = GetColour(label->property("color").toString().toLatin1()[0]);
                isEter = label->property("isEter").toBool();
                isIllusion = label->property("isIllusion").toBool();

                removeWidgetFromGrid(row, col);
            }
        }
    }
}

void qGameBoardWidget::removeMargins(std::vector<MarginType> marginsToRemove)
{
    for (int i = 0; i < marginsToRemove.size(); i++)
    {
        switch (marginsToRemove[i])
        {
            case MarginType::MARGIN_TOP:
                qDebug() << "top";
                removeTopMargin();
                break;
            case MarginType::MARGIN_BOT:
                qDebug() << "bot";
                removeBottomMargin();
                break;
            case MarginType::MARGIN_LEFT:
                qDebug() << "left";
                removeLeftMargin();
                break;
            case MarginType::MARGIN_RIGHT:
                qDebug() << "right";
                removeRightMargin();
                break;
            default:
                break;
        }
    }
    for (auto& card : m_cardPosition)
    {
        qDebug() << card.first.first << " " << card.first.second<<'\n';
    }
    createBoard();
}

void qGameBoardWidget::placeHoleCard(int row, int col, QPixmap pixmapHole)
{
    scaleCoordinates(row, col);
    if (m_cardPosition.find({ row,col }) != m_cardPosition.end())
    {
        while (!m_cardPosition[{row, col}].empty())
        {
            m_cardPosition[{row, col}].pop_back();
        }
    }
    pixmapHole = pixmapHole.scaled(CARD_WIDTH, CARD_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel* holeLabel = new QLabel(this);
    holeLabel->setPixmap(pixmapHole);
    holeLabel->setProperty("isHole", true);
    holeLabel->setProperty("value", 100);
    holeLabel->setProperty("color", "invalid");
    holeLabel->setProperty("isEter", false);
    holeLabel->setProperty("isIllusion", false);

    m_cardPosition[{row, col}].emplace_back(holeLabel);
    m_pixmapPosition[{row, col}].emplace_back(holeLabel->pixmap());
    gridLayout->addWidget(holeLabel, row, col);
}

void qGameBoardWidget::placeCardsOnBoard(ResizeableMatrix matrix)
{
    m_cardPosition.clear();
    m_emptyPositions.clear();
    m_pixmapPosition.clear();

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            while (!matrix[i][j].empty())
            {
                QLabel* newCard = new QLabel(this);
                QString currentCardPath = QDir::currentPath() + QString("/textures/");
                if (matrix[i][j].back().GetIsIllusionCard())
                {
                    if(matrix[i][j].back().GetColor()==Colours::RED)
                        currentCardPath=currentCardPath+ QString("/red_back.jpg");
                    else if(matrix[i][j].back().GetColor() == Colours::BLUE)
                        currentCardPath = currentCardPath + QString("/blue_back.jpg");
                }
                else if (matrix[i][j].back().GetCardType() == CardType::HoleCard)
                {
                    currentCardPath = currentCardPath + QString("/hole_sprite.png");
                }
                else
                {
                    if (matrix[i][j].back().GetColor() == Colours::RED)
                        currentCardPath = currentCardPath + QString("/red_")+QString::number(matrix[i][j].back().GetValue())
                        +QString(".jpg");
                    else if (matrix[i][j].back().GetColor() == Colours::BLUE)
                        currentCardPath = currentCardPath + QString("/blue_") + QString::number(matrix[i][j].back().GetValue())
                        + QString(".jpg");
                }
                QPixmap pixmapCard(currentCardPath);
                pixmapCard = pixmapCard.scaled(CARD_WIDTH, CARD_HEIGTH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                newCard->setPixmap(pixmapCard);
                newCard->setProperty("isHole", matrix[i][j].back().GetIsIllusionCard());
                newCard->setProperty("value", matrix[i][j].back().GetValue());
                newCard->setProperty("color", QString(GetColour(matrix[i][j].back().GetColor())));
                newCard->setProperty("isEter", matrix[i][j].back().GetIsEterCard());
                newCard->setProperty("isIllusion", matrix[i][j].back().GetIsIllusionCard());
                m_cardPosition[{i+1, j+1}].emplace_front( newCard);
                m_pixmapPosition[{i+1, j+1}].emplace_front(pixmapCard);
                matrix[i][j].pop_back();
            }
        }
    }
    updateMinMaxRowCol();
    createBoard();
}


