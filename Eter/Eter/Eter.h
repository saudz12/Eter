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
#include "qmessagebox.h"

#include "qtCompletePlayer.h"
#include "qtCompleteBoard.h"

#include "qDraggableLabel.h"
#include "qGameBoardWidget.h"

#include "ConsolePlayableGUI.h"

#include <memory>

class Eter : public QMainWindow
{
    Q_OBJECT

private:
    ///members
    Ui::EterClass* ui;
    QPointer<QHBoxLayout> hboxLayoutRedCards;
    QPointer<QHBoxLayout> hboxLayoutBlueCards;

    QPointer<QLabel> labelEterLogo;

    QPointer<QLabel> labelFirstElementalCard;
    QPointer<QLabel> labelSecondElementalCard;

    //aici un game final
    std::unique_ptr<GameView> m_gameview;

    std::unique_ptr<qtCompletePlayer> plRed;
    std::unique_ptr<qtCompletePlayer> plBlue;

    std::vector<QString> m_elementalCardsPaths;

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

    const int FIRST_ELEMENTAL_CARD_X = 200;
    const int FIRST_ELEMENTAL_CARD_Y = 200;
    const int SECOND_ELEMENTAL_CARD_X = 1300;
    const int SECOND_ELEMENTAL_CARD_Y = 600;

    const uint16_t BOARD_SIZE=3;

    const int CARDS_SPACING = 10;

    bool m_wasFirstCardPlaced;
    
    ///functions

    void changeDraggabilityHBoxLayout(QPointer<QHBoxLayout>& currentLayout,bool enabled);
    void placeHorizontalLayout();
    void placeHorizontalLayoutRedSide();
    void placeHorizontalLayoutBlueSide();

    void removeCardFromHorizontalLayout(QPointer<QHBoxLayout> hboxLayout,int valueToRemove);

    void resizeGameLogo();

    void placeCardInsideHLayout(qtCompletePlayer &pl,
        QPointer<QHBoxLayout>& hboxLayoutCards,QPointer<QWidget>& widgetHBoxCards);

    void loadElementalCardsPaths();
    void initializeElementalCards();

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
