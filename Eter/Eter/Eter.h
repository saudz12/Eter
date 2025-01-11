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
#include <qdir.h>

#include "qtCompletePlayer.h"
#include "qtCompleteBoard.h"

#include "qDraggableLabel.h"
#include "qGameBoardWidget.h"

#include "ConsolePlayableGUI.h"

class Eter : public QMainWindow
{
    Q_OBJECT

private:
    ///members
    Ui::EterClass* ui;
    QPointer<QHBoxLayout> hboxLayoutRedCards;
    QPointer<QHBoxLayout> hboxLayoutBlueCards;

    QPointer<QLabel> labelEterLogo;

    qtCompletePlayer plRed;
    qtCompletePlayer plBlue;
    qtCompleteBoard board{BOARD_SIZE};

    QPointer<QWidget> widgetHBoxRedCards;
    QPointer<QWidget> widgetHBoxBlueCards;

    std::deque<QPointer<qDraggableLabel>>labelCards;

    QPointer<qGameBoardWidget> widgetBoard;

    QPointer<QPushButton> pushButtonStartTraining;
    QPointer<QPushButton> pushButtonStartElemental;
    QPointer<QPushButton> pushButtonStartMage;
    QPointer<QPushButton> pushButtonStartTournament;
    QPointer<QPushButton> pushButtonStartTimed;

    int WINDOW_WIDTH, WINDOW_HEIGTH;
    const int REDCARDS_OFFSET_WINDOW_WIDTH = 100;
    const int REDCARDS_OFFSET_WINDOW_HEIGHT = 30;
    const int BLUECARDS_OFFSET_WINDOW_WIDTH = REDCARDS_OFFSET_WINDOW_WIDTH;
    int BLUE_CARDS_OFFSET_WINDOW_HEIGHT;

    const uint16_t BOARD_SIZE=3;

    const int CARDS_SPACING = 10;
    
    ///functions

    void placeHorizontalLayout();
    void placeHorizontalLayoutRedSide();
    void placeHorizontalLayoutBlueSide();

    void removeCardFromHorizontalLayout(QPointer<QHBoxLayout> hboxLayout,int valueToRemove);

    void placeCardInsideHLayout(qtCompletePlayer &pl,
        QPointer<QHBoxLayout>& hboxLayoutCards,QPointer<QWidget>& widgetHBoxCards);

    //aici un game final
    GameView m_gameview;
public:
    static const int CARD_WIDTH=80;
    static const int CARD_HEIGHT=80;

    Eter(QWidget *parent = nullptr);
    ~Eter();

    void initializeGameWindow();
    void initializePushButtons();
    void initializeHandCardLayouts();

    void initializeGridLayoutBoard();
    void initializeEterLogo();

    void scaleCoordinates(int& row, int& column);
private slots:
    void onPushButtonStartTrainingClicked();
    void onPushButtonStartElementalClicked();
    void onPushButtonStartMageClicked();
    void onPushButtonStartTournamentClicked();
    void onPushButtonStartTimedClicked();
    void onBoardResized();
    void cardDropHandler(const QMimeData* mimeData,int row,int column);
};
