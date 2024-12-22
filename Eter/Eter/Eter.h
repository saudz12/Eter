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
#include "qgridlayout.h"
#include "qpointer.h"

#include "qtCompletePlayer.h"
#include "qtCompleteBoard.h"

#include "qDraggableLabel.h"
#include "qGameBoardWidget.h"

class Eter : public QMainWindow
{
    Q_OBJECT

private:
    ///members
    Ui::EterClass* ui;
    QHBoxLayout* hboxLayoutRedCards;
    QHBoxLayout* hboxLayoutBlueCards;

    qtCompletePlayer plRed{ 'R' }, plBlue{ 'B' };
    qtCompleteBoard board{BOARD_SIZE};

    QPointer<QWidget> widgetHBoxRedCards;
    QPointer<QWidget> widgetHBoxBlueCards;

    std::deque <qDraggableLabel*> labelCards;

    QPointer<qGameBoardWidget> widgetBoard;

    int WINDOW_WIDTH, WINDOW_HEIGTH;
    const int REDCARDS_OFFSET_WINDOW_WIDTH = 100;
    const int REDCARDS_OFFSET_WINDOW_HEIGHT = 30;
    const int BLUECARDS_OFFSET_WINDOW_WIDTH = REDCARDS_OFFSET_WINDOW_WIDTH;
    int BLUE_CARDS_OFFSET_WINDOW_HEIGHT;

    const uint16_t BOARD_SIZE=3;

    const int CARDS_SPACING = 10;

    const int CARD_WIDTH = 80;
    const int CARD_HEIGHT = 80;
    
    ///functions

    void placeHorizontalLayout();
    void placeHorizontalLayoutRedSide();
    void placeHorizontalLayoutBlueSide();

    void placeCardInsideHLayout(std::vector<QString>& pathCards, std::deque<QPixmap>& pixmapCards,
        QHBoxLayout*& hboxLayoutCards,QPointer<QWidget>& widgetHBoxCards);
public:
    QPointer<QPushButton> pushButtonStartGame;

    Eter(QWidget *parent = nullptr);
    ~Eter();

    void initializeGameWindow();
    void initializePushButtons();
    void initializeHandCardLayouts();

    void initializeGridLayoutBoard();


private slots:
    void onPushButtonStartGameClicked();
    void onBoardResized();
};
