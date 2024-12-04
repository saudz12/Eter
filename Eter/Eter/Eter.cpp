#include "Eter.h"

Eter::Eter(QWidget *parent)
    : QMainWindow(parent), ui {new Ui::EterClass}
{
    ui->setupUi(this);

    initializeGameWindow();
    initializePushButtons();
    initializeHandCardLayouts();
    BLUE_CARDS_OFFSET_WINDOW_HEIGHT = WINDOW_HEIGTH - 30;
}

Eter::~Eter()
{
    delete pushButtonStartGame;
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
    pushButtonStartGame = new QPushButton("Start game", this);
    pushButtonStartGame->setGeometry(WINDOW_WIDTH / 30, WINDOW_HEIGTH / 20, 100, 30);
    pushButtonStartGame->setVisible(true);

    connect(pushButtonStartGame, &QPushButton::clicked, this, &Eter::onPushButtonStartGameClicked);
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
    placeCardInsideHLayout(plRed.GetPathCards(), plRed.GetPixmapCards(), hboxLayoutRedCards,widgetHBoxRedCards);
    widgetHBoxRedCards->setParent(this);
    widgetHBoxRedCards->setVisible(true);
}

void Eter::placeHorizontalLayoutBlueSide()
{
    placeCardInsideHLayout(plBlue.GetPathCards(), plBlue.GetPixmapCards(), hboxLayoutBlueCards,widgetHBoxBlueCards);
    widgetHBoxBlueCards->setParent(this);
    widgetHBoxBlueCards->setVisible(true);
}

void Eter::placeCardInsideHLayout(std::vector<QString>& pathCards, std::deque<QPixmap>& pixmapCards,
    QHBoxLayout*& hboxLayoutCards,QWidget*& widgetHBoxCards)
{
    int index = 0;
    for (const auto& card : pixmapCards)
    {
        QPixmap resizedCard = card.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        qDraggableLabel* currCardLabelDraggable = new qDraggableLabel(resizedCard,CARD_WIDTH,CARD_HEIGHT,widgetHBoxCards);
        
        hboxLayoutCards->addWidget(currCardLabelDraggable);

        labelCards.push_back(currCardLabelDraggable);
        index++;
    }
}

void Eter::placeHorizontalLayout()
{
    placeHorizontalLayoutRedSide();
    placeHorizontalLayoutBlueSide();
}

void Eter::onPushButtonStartGameClicked()
{
    placeHorizontalLayout();
    initializeGridLayoutBoard();
}

void Eter::initializeGridLayoutBoard()
{
    widgetBoard = new qGameBoardWidget(this,BOARD_SIZE,CARD_WIDTH,CARD_HEIGHT,CARDS_SPACING);
    widgetBoard->setBoardPosition((WINDOW_WIDTH-REDCARDS_OFFSET_WINDOW_WIDTH-CARDS_SPACING)/2,
                                (WINDOW_HEIGTH-CARDS_SPACING)/2,
                                CARD_WIDTH,CARD_HEIGHT);
    widgetBoard->show();
}


