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
#include "qdialog.h"

#include "qtCompletePlayer.h"

#include "qDraggableLabel.h"
#include "qGameBoardWidget.h"
#include "qDialogExplosionCard.h"

#include "ConsolePlayableGUI.h"

#include <memory>
#include <json.hpp>

using json = nlohmann::json;

//id, name, file path, effect
using elementalCardInfo = std::tuple<int16_t, QString, QString, QString>;

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
    std::vector<elementalCardInfo> m_elementalCardsInfo;

    //uiBoard
    QPointer<qGameBoardWidget> widgetBoard;

    //buttons
    QPointer<QPushButton> pushButtonStartTraining;
    QPointer<QPushButton> pushButtonStartElemental;
    QPointer<QPushButton> pushButtonStartMage;
    QPointer<QPushButton> pushButtonStartTournament;
    QPointer<QPushButton> pushButtonStartTimed;
    QPointer<QPushButton> pushButtonSaveGame;
    QPointer<QPushButton> pushButtonLoadGame;

    QPointer<QRadioButton> radioButtonPlayIllusion;

    //illusions
    QPointer<QLabel> labelRedIllusion;
    QPointer<QLabel> labelBlueIllusion;

    //explosions
    QPointer<qDialogExplosionCard> dialogExplosion;

    GameView::LaunchOptions m_activeGamemode;

    //object placement details
    int WINDOW_WIDTH, WINDOW_HEIGTH;
    const int REDCARDS_OFFSET_WINDOW_WIDTH = 100;
    const int REDCARDS_OFFSET_WINDOW_HEIGHT = 30;
    const int BLUECARDS_OFFSET_WINDOW_WIDTH = REDCARDS_OFFSET_WINDOW_WIDTH;
    int BLUE_CARDS_OFFSET_WINDOW_HEIGHT;

    const int FIRST_ELEMENTAL_CARD_X = 1300;
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
    void addCardToHorizontalLayout(QPointer<QHBoxLayout> hboxLayout, QPointer<qDraggableLabel> labeltoAdd);

    void resizeGameLogo();

    void placeCardInsideHLayout(qtCompletePlayer &pl,
        QPointer<QHBoxLayout>& hboxLayoutCards,QPointer<QWidget>& widgetHBoxCards);

    void loadElementalCardsFromJSON();
    void loadIllusion(QPointer<QLabel>& label, QString path);

    void initializeElementalCards();
    void handleMinionCard(const QMimeData* mimeData, int row, int column);
    void handleIllusionCard(const QMimeData* mimeData, int row, int column);

    bool checkWin();
    void resetUItoNormal();
    void resetElements();
    void changeLabelMessageBox(const QMimeData* mimeData);
    void initializeGameMessage();

    ///explosions
    void initializeExplosionDialog(std::shared_ptr<ExplosionCard>& card);
    bool m_wasExplosionPlayed;
public:
    static const int CARD_WIDTH=80;
    static const int CARD_HEIGHT=80;

    Eter(QWidget *parent = nullptr);
    ~Eter();

    void initializeGameWindow();
    void initializePushButtons();
    void initializeRadioButtons();
    void initializeHandCardLayouts();

    void initializeGridLayoutBoard();
    void initializeEterLogo();

    void scaleCoordinates(int& row, int& column);

    void loadElementsFromJSON();
private slots:
    void onPushButtonStartTrainingClicked();
    void onPushButtonStartElementalClicked();
    void onPushButtonStartMageClicked();
    void onPushButtonStartTournamentClicked();
    void onPushButtonStartTimedClicked();
    void onPushButtonSaveGame();
    void onPushButtonLoadGame();
    void onBoardResized();
    void cardDropHandler(const QMimeData* mimeData,int row,int column);
    void IllusionHandler(bool* toogled);
    void handlerExplCardAccept(ExplosionCard card);
    void handlerExplCardReject(ExplosionCard card);
signals:
    void signalRemoveIllusionCard(int row, int col);
    void signalRemoveCard(int row, int col);
    void signalReturnCard(int row, int col, int& value, Colours& color, bool& isEter, bool& isIllusion);
    void signalRemoveMargins(std::vector<MarginType> marginsToRemove);
    void signalPlaceHoleCard(int row, int col,QPixmap pixmaphole);
};
