#include "Eter.h"

Eter::Eter(QWidget *parent)
    : QMainWindow(parent), ui {new Ui::EterClass}
{
    ui->setupUi(this);
    
    WINDOW_WIDTH = this->width();
    WINDOW_HEIGTH = this->height();

    initializeGameWindow();
}

Eter::~Eter()
{
    //delete pushButtonStartGame;
    //delete ui;
}

void Eter::initializeGameWindow()
{
    showMaximized();
    pushButtonStartGame = new QPushButton("Start game", this);
    pushButtonStartGame->setGeometry(WINDOW_WIDTH / 20, WINDOW_HEIGTH / 10, 100, 30);
    pushButtonStartGame->setVisible(true);

    connect(pushButtonStartGame, &QPushButton::clicked, this, &Eter::onPushButtonStartGameClicked);
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
            //incarc in functie de indicele din vectorul cu cai
            horizontalPixmap.emplace_back(cardPath[cardValue]);
            auxRemainingCards--;
        }
    }
}

void Eter::generatePathsForMinionCards()
{
    for (size_t i = 0; i < 5; i++)
    {
        m_pathBlueCards.emplace_back(QDir::currentPath() + "/textures/blue_" + QString::number(i) + ".jpg");
        m_pathRedCards.emplace_back(QDir::currentPath() + "/textures/blue_" + QString::number(i) + ".jpg");
    }
}

void Eter::loadTexturesForMinions()
{
    generatePathsForMinionCards();

    loadCards(m_pathRedCards,m_pixmapRedCards, m_pRed.GetPlayerColor());
    loadCards(m_pathBlueCards, m_pixmapBlueCards, m_pBlue.GetPlayerColor());

}

void Eter::placeHorizontalLayout(std::vector<QString>& m_pathCards)
{

}

void Eter::onPushButtonStartGameClicked()
{
    loadTexturesForMinions();
}


