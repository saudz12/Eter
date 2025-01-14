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
#include "qradiobutton.h"

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
    //hand card
    QPointer<QHBoxLayout> hboxLayoutRedCards; 
    QPointer<QHBoxLayout> hboxLayoutBlueCards;
    QPointer<QWidget> widgetHBoxRedCards;
    QPointer<QWidget> widgetHBoxBlueCards;
    bool m_wasFirstCardPlaced;

    //game message box
    QPointer<QLabel> labelGameMessage;

    //eter logo
    QPointer<QLabel> labelEterLogo;

    //de pus in qElementalMode
    QPointer<QLabel> labelRedElementalCard;
    QPointer<QLabel> labelBlueElementalCard;

    //current gamemode
    std::unique_ptr<GameView> m_gameview;
    
    //players
    std::unique_ptr<qtCompletePlayer> plRed;
    std::unique_ptr<qtCompletePlayer> plBlue;
    Colours m_activeColor;

    //de pus in qElementalMode
    std::vector<QString> m_elementalCardsPaths;

    //uiBoard
    QPointer<qGameBoardWidget> widgetBoard;

    //buttons
    QPointer<QPushButton> pushButtonStartTraining;
    QPointer<QPushButton> pushButtonStartElemental;
    QPointer<QPushButton> pushButtonStartMage;
    QPointer<QPushButton> pushButtonStartTournament;
    QPointer<QPushButton> pushButtonStartTimed;

    QPointer<QRadioButton> radioButtonPlayIllusion;

    //illusions
    QPointer<QLabel> labelRedIllusion;
    QPointer<QLabel> labelBlueIllusion;

    GameView::LaunchOptions m_activeGamemode;

    //object placement details
    int WINDOW_WIDTH, WINDOW_HEIGTH;
    const int REDCARDS_OFFSET_WINDOW_WIDTH = 100;
    const int REDCARDS_OFFSET_WINDOW_HEIGHT = 30;
    const int BLUECARDS_OFFSET_WINDOW_WIDTH = REDCARDS_OFFSET_WINDOW_WIDTH;
    int BLUE_CARDS_OFFSET_WINDOW_HEIGHT;

    const int FIRST_ELEMENTAL_CARD_X = 200;
    const int FIRST_ELEMENTAL_CARD_Y = 200;
    const int SECOND_ELEMENTAL_CARD_X = 1300;
    const int SECOND_ELEMENTAL_CARD_Y = 600;

    //trebuie scos
    const uint16_t BOARD_SIZE=3;

    const int CARDS_SPACING = 10;

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
    void loadIllusion(QPointer<QLabel>& label, QString path);

    void initializeElementalCards();
    void handleMinionCard(const QMimeData* mimeData, int row, int column);
    void handleIllusionCard(const QMimeData* mimeData, int row, int column);

    void checkWin();
    void resetUItoNormal();
    void resetElements();

    void initializeGameMessage();
public:
    static const int CARD_WIDTH=80;
    static const int CARD_HEIGHT=80;

    Eter(QWidget *parent = nullptr);
    ~Eter();

    void initializeGameWindow();
    void initializeButtons();
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
