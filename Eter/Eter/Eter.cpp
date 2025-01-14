#include "Eter.h"

Eter::Eter(QWidget *parent)
    : QMainWindow(parent), ui {new Ui::EterClass},
     m_wasFirstCardPlaced{false}
{
    ui->setupUi(this);

    initializeEterLogo();
    initializeGameWindow();
    initializeButtons();
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

void Eter::initializeButtons()
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

    if(!radioButtonPlayIllusion)
        radioButtonPlayIllusion = new QRadioButton("Play Illusion", this);
    radioButtonPlayIllusion->setGeometry(pushButtonStartTimed->x(), pushButtonStartTimed->y() + 50, 130, 30);
    radioButtonPlayIllusion->setVisible(true);

    connect(pushButtonStartTraining, &QPushButton::clicked, this, &Eter::onPushButtonStartTrainingClicked);
    connect(pushButtonStartElemental, &QPushButton::clicked, this, &Eter::onPushButtonStartElementalClicked);
    connect(pushButtonStartMage, &QPushButton::clicked, this, &Eter::onPushButtonStartMageClicked);
    connect(pushButtonStartTournament, &QPushButton::clicked, this, &Eter::onPushButtonStartTournamentClicked);
    connect(pushButtonStartTimed, &QPushButton::clicked, this, &Eter::onPushButtonStartTimedClicked);
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

void Eter::loadElementalCardsPaths()
{
    QString basePath = QDir::currentPath() + "/textures/spell_";
    for (size_t i = 0; i < 24; i++)
    {
        m_elementalCardsPaths.emplace_back(basePath + QString::number(i) + ".jpg");
        qDebug() << basePath + QString::number(i) + ".jpg";
    }
}

void Eter::loadIllusion(QPointer<QLabel>& label,QString path)
{
    label = new QLabel(this);

    QString dirIllusion = QDir::currentPath() + "/textures/";

    QPixmap pixmap{ dirIllusion + path};
    label->setFixedSize(CARD_WIDTH, CARD_HEIGHT);
    label->setGeometry(0, 0, CARD_WIDTH, CARD_WIDTH);
    label->setText("illusion");
    label->setProperty("type", QString("illusion"));
    pixmap = pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pixmap);
    label->hide();
}

void Eter::initializeElementalCards()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> distribution(0, 23);

    uint16_t firstCardNumber{ distribution(gen) };
    distribution.reset();
    uint16_t secondCardNumber{ distribution(gen) };

    while (firstCardNumber == secondCardNumber)
    {
        distribution.reset();
        secondCardNumber = distribution(gen);
    }

    QPixmap firstCardPixmap(m_elementalCardsPaths[firstCardNumber]);
    QPixmap secondCardPixmap(m_elementalCardsPaths[secondCardNumber]);

    qDebug() << m_elementalCardsPaths[firstCardNumber];
    qDebug() << m_elementalCardsPaths[secondCardNumber];

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
        char color = mimeData->property("color").toString().toLatin1().at(0);
        m_activeColor = GetColour(color);
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
    }
    checkWin();
}

void Eter::handleIllusionCard(const QMimeData* mimeData, int row, int column)
{

}

void Eter::checkWin()
{
    if (m_gameview->CheckWin())
    {
        QMessageBox::information(nullptr,"Information",QString(GetColour(m_activeColor)) + QString(" player won the game"));
        resetUItoNormal();
        if (m_activeGamemode == GameView::LaunchOptions::ELEMENTAL)
        {
            resetElements();
        }
    }
}

void Eter::resetElements()
{
    labelRedElementalCard->hide();
    labelBlueElementalCard->hide();
}

void Eter::initializeGameMessage()
{
    labelGameMessage = new QLabel(this);
    labelGameMessage->setGeometry(1600, 450, 200, 100);
    labelGameMessage->setText("It's red player's turn");
    labelGameMessage->setStyleSheet("QLabel { border: 2px solid red; }");
    labelGameMessage->show();
}

void Eter::resetGameMessage()
{
    labelGameMessage->setText("It's red player's turn");
    labelGameMessage->setStyleSheet("QLabel { border: 2px solid red; }");
    labelGameMessage->hide();
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
    resetGameMessage();
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
    m_activeGamemode = GameView::LaunchOptions::TRAINING;
    m_gameview = std::make_unique<GameView>(GameOptions::EnabledIllusion,
        GameOptions::DisabledMage,
        GameOptions::DisabledElemental,
        GameOptions::DisabledTournament,
        GameOptions::DisabledTimed,
        GameOptions::DisabledEter);
    plRed = std::make_unique<qtCompletePlayer>(m_gameview->GetRedPlayer(), CARD_WIDTH, CARD_HEIGHT, true);//red starts first
    plBlue = std::make_unique<qtCompletePlayer>(m_gameview->GetBluePlayer(), CARD_WIDTH, CARD_HEIGHT, false);
    loadIllusion(labelRedIllusion, QString("red_back.jpg"));
    loadIllusion(labelBlueIllusion, QString("blue_back.jpg"));
    initializeGameMessage();
    resizeGameLogo();
    placeHorizontalLayout();
    initializeGridLayoutBoard();
}

void Eter::onPushButtonStartElementalClicked()
{
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
    loadElementalCardsPaths();
    initializeElementalCards();
    placeHorizontalLayout();
    initializeGridLayoutBoard();
}

void Eter::onPushButtonStartMageClicked()
{
    m_activeGamemode = GameView::LaunchOptions::MAGE_DUEL;
}

void Eter::onPushButtonStartTournamentClicked()
{
    m_activeGamemode = GameView::LaunchOptions::TOURNAMENT;
}

void Eter::onPushButtonStartTimedClicked()
{
    m_activeGamemode = GameView::LaunchOptions::TIMED;
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