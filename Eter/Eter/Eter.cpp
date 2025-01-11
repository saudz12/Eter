#include "Eter.h"

Eter::Eter(QWidget *parent)
    : QMainWindow(parent), ui {new Ui::EterClass},
     m_gameview{},
     plRed{Colours::RED,CARD_WIDTH,CARD_HEIGHT,m_gameview.GetGameFinal().GetActiveColor()==Colours::RED ?true:false},
     plBlue{Colours::BLUE,CARD_WIDTH,CARD_HEIGHT,m_gameview.GetGameFinal().GetActiveColor() == Colours::BLUE ? true : false }
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
    pushButtonStartTraining = new QPushButton("Start training game", this);
    pushButtonStartTraining->setGeometry(WINDOW_HEIGTH /30, WINDOW_WIDTH / 15+20, 120, 30);
    pushButtonStartTraining->setVisible(true);

    pushButtonStartElemental = new QPushButton("Start elemental game", this);
    pushButtonStartElemental->setGeometry(pushButtonStartTraining->x(), pushButtonStartTraining->y()+50, 120, 30);
    pushButtonStartElemental->setVisible(true);

    pushButtonStartMage = new QPushButton("Start mage duel game", this);
    pushButtonStartMage->setGeometry(pushButtonStartElemental->x(), pushButtonStartElemental->y() + 50, 130, 30);
    pushButtonStartMage->setVisible(true);

    pushButtonStartTournament = new QPushButton("Start tournament game", this);
    pushButtonStartTournament->setGeometry(pushButtonStartMage->x(), pushButtonStartMage->y() + 50, 130, 30);
    pushButtonStartTournament->setVisible(true);

    pushButtonStartTimed = new QPushButton("Start timed game", this);
    pushButtonStartTimed->setGeometry(pushButtonStartTournament->x(), pushButtonStartTournament->y() + 50, 130, 30);
    pushButtonStartTimed->setVisible(true);

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
    placeCardInsideHLayout(plRed, hboxLayoutRedCards,widgetHBoxRedCards);
    widgetHBoxRedCards->setParent(this);
    widgetHBoxRedCards->setVisible(true);
}

void Eter::placeHorizontalLayoutBlueSide()
{
    placeCardInsideHLayout(plBlue, hboxLayoutBlueCards,widgetHBoxBlueCards);
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
    QString dir = QDir::currentPath() + "/textures/raw/eterLogo.jpg";
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

        labelCards.push_back(labels[i]);
    }
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

void Eter::onPushButtonStartTrainingClicked()
{
    resizeGameLogo();
    placeHorizontalLayout();
    initializeGridLayoutBoard();
}

void Eter::initializeGridLayoutBoard()
{
    widgetBoard = new qGameBoardWidget(this,BOARD_SIZE,CARD_WIDTH,CARD_HEIGHT,CARDS_SPACING);
    connect(widgetBoard, &qGameBoardWidget::boardResized, this, &Eter::onBoardResized);
    widgetBoard->setBoardPosition((WINDOW_WIDTH-REDCARDS_OFFSET_WINDOW_WIDTH-CARDS_SPACING)/2,
                                (WINDOW_HEIGTH-CARDS_SPACING)/2,
                                CARD_WIDTH,CARD_HEIGHT);
    widgetBoard->show();
    connect(widgetBoard, &qGameBoardWidget::cardDropAccepted, this, &Eter::cardDropHandler);
}

void Eter::initializeEterLogo()
{
    QString dir = QDir::currentPath() + "/textures/raw/eterLogo.jpg";
    QPixmap logoPixmap(dir);
    labelEterLogo = new QLabel(this);
    labelEterLogo->setGeometry(300, 0, 1000, 1000);
    logoPixmap = logoPixmap.scaled(labelEterLogo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    labelEterLogo->setPixmap(logoPixmap);
}

void Eter::scaleCoordinates(int& row, int& column)
{
    row--;
    column--;
}

void Eter::onPushButtonStartElementalClicked()
{
}

void Eter::onPushButtonStartMageClicked()
{
}

void Eter::onPushButtonStartTournamentClicked()
{
}

void Eter::onPushButtonStartTimedClicked()
{
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
    char color = mimeData->property("color").toString().toLatin1().at(0);
    Colours currentColor = GetColour(color);
    int value = mimeData->property("value").toInt();
    if (mimeData->property("color").toString() == QString('R'))
    {
        changeDraggabilityHBoxLayout(hboxLayoutRedCards,false);
        changeDraggabilityHBoxLayout(hboxLayoutBlueCards, true);
        removeCardFromHorizontalLayout(hboxLayoutRedCards, mimeData->property("value").toInt());
    }
    else
    {
        changeDraggabilityHBoxLayout(hboxLayoutBlueCards, false);
        changeDraggabilityHBoxLayout(hboxLayoutRedCards, true);
        removeCardFromHorizontalLayout(hboxLayoutBlueCards, mimeData->property("value").toInt());
    }
    scaleCoordinates(row, column);
    m_gameview.PlaceCard(row, column, value);
}