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
    showMaximized();
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

void Eter::loadCards(std::vector<QString>& cardPath,std::deque<QPixmap>& horizontalPixmap,char playerColor)
{
    hand currPlayerHandCard;
    if (playerColor == 'R')
        currPlayerHandCard = m_pRed.GetHandCards();
    else
        currPlayerHandCard = m_pBlue.GetHandCards();

    for (auto& currCard :currPlayerHandCard)
    {
        auto& [currMinionCard, remainingCards] = currCard;
        int cardValue = currMinionCard.GetValue();
        int auxRemainingCards = remainingCards;
        while (auxRemainingCards != 0)
        {
            horizontalPixmap.emplace_back(cardPath[cardValue]);
            auxRemainingCards--;
        }
    }
}

void Eter::placeHorizontalLayoutRedSide()
{
    placeCardInsideLayout(m_pathRedCards, m_pixmapRedCards, hboxLayoutRedCards);
    widgetHBoxRedCards->setParent(this);
    widgetHBoxRedCards->setVisible(true);
}

void Eter::placeHorizontalLayoutBlueSide()
{
    placeCardInsideLayout(m_pathBlueCards, m_pixmapBlueCards, hboxLayoutBlueCards);
    widgetHBoxBlueCards->setParent(this);
    widgetHBoxBlueCards->setVisible(true);
}

void Eter::placeCardInsideLayout(std::vector<QString>& pathCards, std::deque<QPixmap>& pixmapCards, QHBoxLayout*& hboxLayoutCards)
{
    int index = 0;
    for (const auto& card : pixmapCards)
    {
        QLabel* currCardLabel = new QLabel(widgetHBoxBlueCards);
        QPixmap resizedCard = card.scaled(CARD_WIDTH, CARD_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        currCardLabel->setPixmap(resizedCard);
        qDebug() << index * (CARD_WIDTH)+REDCARDS_OFFSET_WINDOW_WIDTH << '\n';

        currCardLabel->setAlignment(Qt::AlignCenter);
        currCardLabel->setFixedSize(CARD_WIDTH, CARD_HEIGHT);
        hboxLayoutCards->addWidget(currCardLabel);

        m_labelCards.push_back(currCardLabel);
        index++;
    }
}

void Eter::generatePathsForMinionCards()
{
    for (size_t i = 0; i < 5; i++)
    {
        m_pathBlueCards.emplace_back(QDir::currentPath() + "/textures/blue_" + QString::number(i) + ".jpg");
        m_pathRedCards.emplace_back(QDir::currentPath() + "/textures/red_" + QString::number(i) + ".jpg");
    }
}

void Eter::loadTexturesForMinions()
{
    generatePathsForMinionCards();

    loadCards(m_pathRedCards,m_pixmapRedCards, m_pRed.GetPlayerColor());
    loadCards(m_pathBlueCards, m_pixmapBlueCards, m_pBlue.GetPlayerColor());

}

void Eter::placeHorizontalLayout()
{
    placeHorizontalLayoutRedSide();
    placeHorizontalLayoutBlueSide();
}

void Eter::onPushButtonStartGameClicked()
{
    loadTexturesForMinions();
    placeHorizontalLayout();
}


