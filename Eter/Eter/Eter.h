#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Eter.h"
#include "qstring.h"
#include <QDir>
#include <vector>
#include <QHBoxLayout>
#include <qlayout.h>
#include <deque>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <QResizeEvent>
#include <qwidget.h>
#include <qlabel.h>
#include <QGuiApplication>
#include <QScreen>

#include "Player.h"

class Eter : public QMainWindow
{
    Q_OBJECT

private:
    ///members
    Ui::EterClass* ui;
    QHBoxLayout* hboxLayoutRedCards;
    QHBoxLayout* hboxLayoutBlueCards;

    QWidget* widgetHBoxRedCards;
    QWidget* widgetHBoxBlueCards;

    std::vector<QString> m_pathBlueCards;
    std::vector<QString> m_pathRedCards;

    std::deque<QPixmap> m_pixmapBlueCards;
    std::deque<QPixmap> m_pixmapRedCards;

    std::deque <QLabel*> m_labelCards;

    std::deque<std::deque<QPixmap>> m_matrixTextures;

    Player m_pRed{ 'R' }, m_pBlue{ 'B' };

    int WINDOW_WIDTH, WINDOW_HEIGTH;
    const int REDCARDS_OFFSET_WINDOW_WIDTH=100;
    const int REDCARDS_OFFSET_WINDOW_HEIGHT = 30;
    const int BLUECARDS_OFFSET_WINDOW_WIDTH = REDCARDS_OFFSET_WINDOW_WIDTH;
    int BLUE_CARDS_OFFSET_WINDOW_HEIGHT;

    const int CARD_WIDTH = 80;
    const int CARD_HEIGHT = 80;
    
    ///functions

    void generatePathsForMinionCards();
    void placeHorizontalLayout();
    void loadCards(std::vector<QString>&, std::deque<QPixmap>&,char);
    void placeHorizontalLayoutRedSide();
    void placeHorizontalLayoutBlueSide();

    void placeCardInsideLayout(std::vector<QString>& pathCards, std::deque<QPixmap>& pixmapCards,
        QHBoxLayout*& hboxLayoutCards);
public:
    QPushButton* pushButtonStartGame;

    Eter(QWidget *parent = nullptr);
    ~Eter();

    void initializeGameWindow();
    void initializePushButtons();
    void initializeHandCardLayouts();

    void loadTexturesForMinions();
private slots:
    void onPushButtonStartGameClicked();

};
