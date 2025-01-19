#include "Eter.h"
#include <fstream>

Eter::Eter(QWidget *parent)
    : QMainWindow(parent), ui {new Ui::EterClass},
     m_wasFirstCardPlaced{false}
{
    ui->setupUi(this);
    
    initializeEterLogo();
    initializeGameWindow();
    initializePushButtons();
    initializeHandCardLayouts();

    BLUE_CARDS_OFFSET_WINDOW_HEIGHT = WINDOW_HEIGTH - 30;
}

Eter::~Eter()
{
    delete pushButtonStartTraining;
    delete pushButtonStartElemental;
    delete ui;
}

void Eter::initializeGameWindow()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        QRect screenGeometry = screen->availableGeometry();
        WINDOW_WIDTH = screenGeometry.width();
        WINDOW_HEIGTH = screenGeometry.height();

        this->resize(WINDOW_WIDTH, WINDOW_HEIGTH);
    }
    this->showMaximized();
}

void Eter::initializePushButtons()
{
    if(!pushButtonStartTraining)
        pushButtonStartTraining = new QPushButton("Start training game", this);
    pushButtonStartTraining->setGeometry(WINDOW_HEIGTH /30, WINDOW_WIDTH / 15+20, 120, 30);
    pushButtonStartTraining->setVisible(true);

    if(!pushButtonStartElemental)
        pushButtonStartElemental = new QPushButton("Start elemental game", this);
    pushButtonStartElemental->setGeometry(pushButtonStartTraining->x(), pushButtonStartTraining->y()+50, 120, 30);
    pushButtonStartElemental->setVisible(true);

    if(!pushButtonStartMage)
        pushButtonStartMage = new QPushButton("Start mage duel game", this);
    pushButtonStartMage->setGeometry(pushButtonStartElemental->x(), pushButtonStartElemental->y() + 50, 130, 30);
    pushButtonStartMage->setVisible(true);

    if(!pushButtonStartTournament)
        pushButtonStartTournament = new QPushButton("Start tournament game", this);
    pushButtonStartTournament->setGeometry(pushButtonStartMage->x(), pushButtonStartMage->y() + 50, 130, 30);
    pushButtonStartTournament->setVisible(true);

    if(!pushButtonStartTimed)
        pushButtonStartTimed = new QPushButton("Start timed game", this);
    pushButtonStartTimed->setGeometry(pushButtonStartTournament->x(), pushButtonStartTournament->y() + 50, 130, 30);
    pushButtonStartTimed->setVisible(true);

    connect(pushButtonStartTraining, &QPushButton::clicked, this, &Eter::onPushButtonStartTrainingClicked);
    connect(pushButtonStartElemental, &QPushButton::clicked, this, &Eter::onPushButtonStartElementalClicked);
    connect(pushButtonStartMage, &QPushButton::clicked, this, &Eter::onPushButtonStartMageClicked);
    connect(pushButtonStartTournament, &QPushButton::clicked, this, &Eter::onPushButtonStartTournamentClicked);
    connect(pushButtonStartTimed, &QPushButton::clicked, this, &Eter::onPushButtonStartTimedClicked);
}

void Eter::initializeRadioButtons()
{
    if (!radioButtonPlayIllusion)
        radioButtonPlayIllusion = new QRadioButton("Play Illusion", this);
    radioButtonPlayIllusion->setGeometry(pushButtonStartTimed->x(), pushButtonStartTimed->y() + 50, 130, 30);
    radioButtonPlayIllusion->setVisible(true);
    QObject::connect(widgetBoard, &qGameBoardWidget::isRadioButtonToggledIllusions,
        this, &Eter::IllusionHandler);
    QObject::connect(this, &Eter::signalRemoveIllusionCard, widgetBoard, &qGameBoardWidget::removeCardIllusion);
}

void Eter::initializeHandCardLayouts()
{
    //red cards
    widgetHBoxRedCards = new QWidget(this);
    widgetHBoxRedCards->setGeometry(REDCARDS_OFFSET_WINDOW_WIDTH,
                                    REDCARDS_OFFSET_WINDOW_HEIGHT,
                                    width() - REDCARDS_OFFSET_WINDOW_WIDTH,
                                    CARD_HEIGHT);
    hboxLayoutRedCards = new QHBoxLayout(widgetHBoxRedCards);
    widgetHBoxRedCards->setLayout(hboxLayoutRedCards);

    //blue cards
    widgetHBoxBlueCards = new QWidget(this);
    widgetHBoxBlueCards->setGeometry(REDCARDS_OFFSET_WINDOW_WIDTH,
                                    WINDOW_HEIGTH - CARD_HEIGHT - 50,
                                    width() - REDCARDS_OFFSET_WINDOW_WIDTH,
                                    CARD_HEIGHT);
    hboxLayoutBlueCards = new QHBoxLayout(widgetHBoxBlueCards);
    widgetHBoxBlueCards->setLayout(hboxLayoutBlueCards);
}

void Eter::placeHorizontalLayoutRedSide()
{
    placeCardInsideHLayout(*plRed, hboxLayoutRedCards,widgetHBoxRedCards);
    widgetHBoxRedCards->setParent(this);
    widgetHBoxRedCards->setVisible(true);
}

void Eter::placeHorizontalLayoutBlueSide()
{
    placeCardInsideHLayout(*plBlue, hboxLayoutBlueCards,widgetHBoxBlueCards);
    widgetHBoxBlueCards->setParent(this);
    widgetHBoxBlueCards->setVisible(true);
}

void Eter::removeCardFromHorizontalLayout(QPointer<QHBoxLayout> hboxLayout,int valueToRemove)
{
    for (int i = 0; i < hboxLayout->count(); ++i) 
    {
        QLayoutItem* item = hboxLayout->itemAt(i);
        if (item) 
        {
            QWidget* widget = item->widget();
            if (widget && widget->property("value").toInt() == valueToRemove) 
            {
                delete widget;
                break;
            }
        }
    }
}

void Eter::addCardToHorizontalLayout(QPointer<QHBoxLayout> hboxLayout, QPointer<qDraggableLabel> labeltoAdd)
{
    hboxLayout->addWidget(labeltoAdd);
}

void Eter::resizeGameLogo()
{
    QString dir = QDir::currentPath() + "/textures/raw/eter.png";
    QPixmap logoPixmap(dir);
    labelEterLogo->setGeometry(0, 0, 150, 150);
    logoPixmap = logoPixmap.scaled(labelEterLogo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    labelEterLogo->setPixmap(logoPixmap);
}

void Eter::placeCardInsideHLayout(qtCompletePlayer& pl,
    QPointer<QHBoxLayout>& hboxLayoutCards, QPointer<QWidget>& widgetHBoxCards)
{
    const std::deque<QPointer<qDraggableLabel>>& labels = pl.GetLabelsCards();
    for(int i=0;i< labels.size();++i)
    {
        hboxLayoutCards->addWidget(labels[i]);
    }
}

void Eter::loadElementalCardsFromJSON()
{
    std::ifstream inputFile("data/elementalCards.json");

    if (!inputFile.is_open()) {
        qDebug() << "Could not open the file!";
        return;
    }

    json jsonData;

    inputFile >> jsonData;

    inputFile.close();

    for (const auto& item : jsonData)
    {
        int16_t id = item["id"];
        QString name = QString::fromStdString(item["name"]);
        QString effect = QString::fromStdString(item["effect"]);
        QString filePath = QDir::currentPath() + QString::fromStdString(item["filepath"]);

        m_elementalCardsInfo.push_back({ id, name, effect, filePath });
    }
}

void Eter::initializeElementalCards()
{
    int16_t firstCardNumber = m_gameview->firstElementalCardId();
    int16_t secondCardNumber = m_gameview->secondElementalCardId();

    QPixmap firstCardPixmap(std::get<3>(m_elementalCardsInfo[firstCardNumber - 1]));
    QPixmap secondCardPixmap(std::get<3>(m_elementalCardsInfo[secondCardNumber - 1]));

    labelRedElementalCard = new QLabel(this);
    labelBlueElementalCard = new QLabel(this);

    labelRedElementalCard->setGeometry(FIRST_ELEMENTAL_CARD_X, FIRST_ELEMENTAL_CARD_Y, CARD_WIDTH, CARD_HEIGHT);
    firstCardPixmap = firstCardPixmap.scaled(labelRedElementalCard->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    labelRedElementalCard->setPixmap(firstCardPixmap);

    labelBlueElementalCard->setGeometry(SECOND_ELEMENTAL_CARD_X, SECOND_ELEMENTAL_CARD_Y, CARD_WIDTH, CARD_HEIGHT);
    secondCardPixmap = secondCardPixmap.scaled(labelBlueElementalCard->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    labelBlueElementalCard->setPixmap(secondCardPixmap);

    labelRedElementalCard->show();
    labelBlueElementalCard->show();
}

void Eter::handleMinionCard(const QMimeData* mimeData, int row, int column)
{
    int value = mimeData->property("value").toInt();

    if (m_wasFirstCardPlaced == false)
    {
        m_wasFirstCardPlaced = true;
    }
    else
    {
        scaleCoordinates(row, column);
    }
    if (!m_gameview->PlaceCard(row, column, value))
    {
        QMessageBox::warning(nullptr, "Warning", "Cannot place that card there");
    }
    else
    {
        m_gameview->EndTurn();
        if (!checkWin())
        {
            if (m_gameview->GetCanPlayExplosion() && !m_wasExplosionPlayed)
            {
                m_wasExplosionPlayed = true;
                std::shared_ptr<ExplosionCard> card = std::make_shared<ExplosionCard>(m_gameview->GenerateNewExplosionCard());
                initializeExplosionDialog(card);
            }
            char color = mimeData->property("color").toString().toLatin1().at(0);
            m_activeColor = GetColour(color);
            changeLabelMessageBox(mimeData);
        }
    }
}

void Eter::handleIllusionCard(const QMimeData* mimeData, int row, int column)
{
    int value = mimeData->property("value").toInt();

    if (m_wasFirstCardPlaced == false)
    {
        m_wasFirstCardPlaced = true;
    }
    else
    {
        scaleCoordinates(row, column);
    }
    IllusionErrors placeIllusionResult = m_gameview->PlaceIllusion(row, column, value);
    if (placeIllusionResult ==IllusionErrors::_INVALID_SPACE)
    {
        QMessageBox::warning(nullptr, "Warning", "Cannot place a illusion there");
    }
    else if (placeIllusionResult==IllusionErrors::_ILLUSION_ALREADY_USED)
    {
        emit signalRemoveIllusionCard(row, column, IllusionErrors::_ILLUSION_ALREADY_USED);
        QMessageBox::warning(nullptr, "Warning", "Player "+QString(GetColour(GetOppositeColour(m_activeColor)))+" already used the illusion");
    }
    else
    {
        m_gameview->EndTurn();
        if (!checkWin())
        {
            char color = mimeData->property("color").toString().toLatin1().at(0);
            m_activeColor = GetColour(color);
            changeLabelMessageBox(mimeData);
        }
    }

}

bool Eter::checkWin()
{
    if (m_gameview->CheckWin())
    {
        QMessageBox::information(nullptr,"Information",QString(GetColour(m_activeColor)) + QString(" player won the game"));
        resetUItoNormal();
        if (m_activeGamemode == GameView::LaunchOptions::ELEMENTAL)
        {
            resetElements();
        }
        return true;
    }
    return false;
}

void Eter::resetElements()
{
    labelRedElementalCard->hide();
    labelBlueElementalCard->hide();
}

void Eter::changeLabelMessageBox(const QMimeData* mimeData)
{
    if (mimeData->property("color").toString() == QString('R'))
    {
        labelGameMessage->setText("It's blue player's turn");
        labelGameMessage->setStyleSheet("QLabel { border: 2px solid blue; }");
        changeDraggabilityHBoxLayout(hboxLayoutRedCards, false);
        changeDraggabilityHBoxLayout(hboxLayoutBlueCards, true);
        removeCardFromHorizontalLayout(hboxLayoutRedCards, mimeData->property("value").toInt());
    }
    else
    {
        labelGameMessage->setText("It's red player's turn");
        labelGameMessage->setStyleSheet("QLabel { border: 2px solid red; }");
        changeDraggabilityHBoxLayout(hboxLayoutBlueCards, false);
        changeDraggabilityHBoxLayout(hboxLayoutRedCards, true);
        removeCardFromHorizontalLayout(hboxLayoutBlueCards, mimeData->property("value").toInt());
    }
    labelGameMessage->setAlignment(Qt::AlignCenter);
    labelGameMessage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Eter::initializeGameMessage()
{
    labelGameMessage = new QLabel(this);
    labelGameMessage->setGeometry(pushButtonStartTraining->x()-25, WINDOW_HEIGTH-100, 150, 50);
    labelGameMessage->setText("It's red player's turn");
    labelGameMessage->setStyleSheet("QLabel { border: 2px solid red; }");
    labelGameMessage->setAlignment(Qt::AlignCenter);
    labelGameMessage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    labelGameMessage->show();
}

void Eter::showExplosionCard(ExplosionCard card)
{

}

void Eter::initializeExplosionDialog(std::shared_ptr<ExplosionCard>& card)
{
    dialogExplosion = new qDialogExplosionCard(this,card,m_gameview->GetBoardSize());
    dialogExplosion->show();
    connect(dialogExplosion, &qDialogExplosionCard::acceptExplCard, this, &Eter::handlerExplCardAccept);
    connect(dialogExplosion, &qDialogExplosionCard::rejectExlpCard, this, &Eter::handlerExplCardReject);
}

void Eter::resetUItoNormal()
{
    widgetBoard->hide();
    if (!hboxLayoutRedCards.isNull()) {
        for (int i = 0; i < hboxLayoutRedCards->count(); ++i) {
            QWidget* widget = hboxLayoutRedCards->itemAt(i)->widget();
            if (widget) {
                widget->hide();
            }
        }
    }
    if (!hboxLayoutBlueCards.isNull()) {
        for (int i = 0; i < hboxLayoutBlueCards->count(); ++i) {
            QWidget* widget = hboxLayoutBlueCards->itemAt(i)->widget();
            if (widget) {
                widget->hide();
            }
        }
    }
    initializeEterLogo();
}

void Eter::changeDraggabilityHBoxLayout(QPointer<QHBoxLayout>& currentLayout,bool enable)
{
    for (int i = 0; i < currentLayout->count(); ++i)
    {
        QLayoutItem* item = currentLayout->itemAt(i);
        if (item)
        {
            QWidget* widget = item->widget();
            QPointer<qDraggableLabel> label = qobject_cast<qDraggableLabel*>(widget);
            if (label)
            {
                label->setDraggable(enable);
            }
        }
    }
}

void Eter::placeHorizontalLayout()
{
    placeHorizontalLayoutRedSide();
    placeHorizontalLayoutBlueSide();
}

void Eter::initializeGridLayoutBoard()
{
    widgetBoard = new qGameBoardWidget(this,m_gameview->GetBoardSize(), CARD_WIDTH, CARD_HEIGHT, CARDS_SPACING);
    connect(widgetBoard, &qGameBoardWidget::boardResized, this, &Eter::onBoardResized);
    widgetBoard->setBoardPosition((WINDOW_WIDTH-REDCARDS_OFFSET_WINDOW_WIDTH-CARDS_SPACING)/2,
                                (WINDOW_HEIGTH-CARDS_SPACING)/2,
                                CARD_WIDTH,CARD_HEIGHT);
    widgetBoard->show();
    connect(widgetBoard, &qGameBoardWidget::cardDropAccepted, this, &Eter::cardDropHandler);
    connect(this, &Eter::signalRemoveCard, widgetBoard, &qGameBoardWidget::removeCard);
}

void Eter::initializeEterLogo()
{
    QString dir = QDir::currentPath() + "/textures/raw/eter.png";
    QPixmap logoPixmap(dir);
    if(!labelEterLogo)
        labelEterLogo = new QLabel(this);
    labelEterLogo->setGeometry(300, 100, 1000, 500);
    logoPixmap = logoPixmap.scaled(labelEterLogo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    labelEterLogo->setPixmap(logoPixmap);
}

void Eter::scaleCoordinates(int& row, int& column)
{
    row--;
    column--;
}

void Eter::onPushButtonStartTrainingClicked()
{
    m_wasExplosionPlayed = false;
    m_activeGamemode = GameView::LaunchOptions::TRAINING;
    m_gameview = std::make_unique<GameView>(GameOptions::EnabledIllusion,
        GameOptions::DisabledMage,
        GameOptions::DisabledElemental,
        GameOptions::DisabledTournament,
        GameOptions::DisabledTimed,
        GameOptions::DisabledEter);
    plRed = std::make_unique<qtCompletePlayer>(m_gameview->GetRedPlayer(), CARD_WIDTH, CARD_HEIGHT, true);//red starts first
    plBlue = std::make_unique<qtCompletePlayer>(m_gameview->GetBluePlayer(), CARD_WIDTH, CARD_HEIGHT, false);
    initializeGameMessage();
    resizeGameLogo();
    placeHorizontalLayout();
    initializeGridLayoutBoard();
    initializeRadioButtons();
}

void Eter::onPushButtonStartElementalClicked()
{
    m_wasExplosionPlayed = false;
    m_activeGamemode = GameView::LaunchOptions::ELEMENTAL;
    m_gameview = std::make_unique<GameView>(GameOptions::EnabledIllusion,
        GameOptions::DisabledMage,
        GameOptions::EnabledElemental,
        GameOptions::DisabledTournament,
        GameOptions::DisabledTimed,
        GameOptions::EnabledEter);
    plRed = std::make_unique<qtCompletePlayer>(m_gameview->GetRedPlayer(), CARD_WIDTH, CARD_HEIGHT, true);//red starts first
    plBlue = std::make_unique<qtCompletePlayer>(m_gameview->GetBluePlayer(), CARD_WIDTH, CARD_HEIGHT, false);
    resizeGameLogo();
    initializeGameMessage();
    loadElementalCardsFromJSON();
    initializeElementalCards();
    placeHorizontalLayout();
    initializeGridLayoutBoard();
    initializeRadioButtons();
}

void Eter::onPushButtonStartMageClicked()
{
    m_wasExplosionPlayed = false;
    m_activeGamemode = GameView::LaunchOptions::MAGE_DUEL;
    initializeGameMessage();
    initializeRadioButtons();
}

void Eter::onPushButtonStartTournamentClicked()
{
    m_wasExplosionPlayed = false;
    m_activeGamemode = GameView::LaunchOptions::TOURNAMENT;
    initializeGameMessage();
    initializeRadioButtons();
}

void Eter::onPushButtonStartTimedClicked()
{
    m_wasExplosionPlayed = false;
    m_activeGamemode = GameView::LaunchOptions::TIMED;
    initializeGameMessage();
    initializeRadioButtons();
}

void Eter::onBoardResized()
{
    int newX = (this->width() - widgetBoard->width()-REDCARDS_OFFSET_WINDOW_WIDTH) / 2;
    int newY = (this->height() - widgetBoard->height()) / 2;
    if(widgetBoard)
        widgetBoard->move(newX, newY);
}

void Eter::cardDropHandler(const QMimeData* mimeData, int row, int column)
{
    if (mimeData->property("type") == QString("minion") && !radioButtonPlayIllusion->isChecked())
        handleMinionCard(mimeData, row, column);
    else if (mimeData->property("type") == QString("minion") && radioButtonPlayIllusion->isChecked())
        handleIllusionCard(mimeData, row, column);
}

void Eter::IllusionHandler(bool* toogled)
{
    *toogled = radioButtonPlayIllusion->isChecked();
}

void Eter::handlerExplCardAccept(ExplosionCard card)
{
    connect(this, &Eter::signalReturnCard, widgetBoard, &qGameBoardWidget::returnCard);
    connect(this, &Eter::signalRemoveCard, widgetBoard, &qGameBoardWidget::removeCard);
    connect(this, &Eter::signalRemoveMargins, widgetBoard, &qGameBoardWidget::removeMargins);
    connect(this, &Eter::signalPlaceHoleCard, widgetBoard, &qGameBoardWidget::placeHoleCard);
    if (m_gameview->tryToApplyExplosionOnBoard(card))
    {
        std::vector<MarginType> marginsToRemove=m_gameview->applyExplosionOnBoard(card);
        for (const auto& action : card.GetExplosionMap())
        {
            const auto& [position, type] = action;
            const auto& [row, col] = position;

            switch (type)
            {   
            case ReturnRemoveOrHoleCard::RemoveCard :
                emit signalRemoveCard(row, col);
                break;
            case ReturnRemoveOrHoleCard::ReturnCard: {
                int value = -1;
                Colours color = Colours::INVALID_COL;
                bool isEter = false;
                bool isIllusion = false;
                emit signalReturnCard(row, col, value, color, isEter, isIllusion);
                QString path;
                if (value != -1)
                {
                    if (color == Colours::RED)
                    {
                        path = QDir::currentPath() + QString("/textures/red_") + QString::number(value) + QString(".jpg");
                    }
                    else if (color == Colours::BLUE)
                    {
                        path = QDir::currentPath() + QString("/textures/blue_") + QString::number(value) + QString(".jpg");
                    }
                }
                QPixmap image(path);
                image = image.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QPointer<qDraggableLabel> labelToadd = new qDraggableLabel(image, CARD_WIDTH, CARD_HEIGHT, true);
                if (value != -1)
                {
                    if (color == Colours::RED)
                    {
                        addCardToHorizontalLayout(hboxLayoutRedCards, labelToadd);
                    }
                    else if (color == Colours::BLUE)
                    {
                        addCardToHorizontalLayout(hboxLayoutBlueCards, labelToadd);
                    }
                }
                break;
            }
            case ReturnRemoveOrHoleCard::HoleCard: {
                QPixmap pixmapHole(QDir::currentPath() + QString("/textures/hole_sprite.png"));
                emit signalPlaceHoleCard(row, col,pixmapHole);
                break;
            }
            case ReturnRemoveOrHoleCard::Default:
                break;
            }
        }
        widgetBoard->updateMinMaxRowCol();
        widgetBoard->createBoard();

        if(!marginsToRemove.empty())
            emit signalRemoveMargins(marginsToRemove);
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "Cannot use the explosion card because the cards are no longer adjacent");
    }
}

void Eter::handlerExplCardReject(ExplosionCard card)
{
}

