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

#include "Player.h"

class Eter : public QMainWindow
{
    Q_OBJECT

private:
    ///members
    Ui::EterClass* ui;
    QHBoxLayout* hboxLayoutRedCards;
    QHBoxLayout* hboxLayoutBlueCards;

    std::vector<QString> m_pathBlueCards;
    std::vector<QString> m_pathRedCards;

    std::deque<QPixmap> m_pixmapBlueCards;
    std::deque<QPixmap> m_pixmapRedCards;

    std::deque<std::deque<QPixmap>> m_matrixTextures;

    Player m_pRed{ 'R' }, m_pBlue{ 'B' };

    uint16_t WINDOW_WIDTH, WINDOW_HEIGTH;

    ///functions

    void movePushButtonStartGame();

    void generatePathsForMinionCards();
    void placeHorizontalLayout(std::vector<QString>& m_pathCards);
    void loadCards(std::vector<QString>&, std::deque<QPixmap>&,char);
public:
    QPushButton* pushButtonStartGame;

    Eter(QWidget *parent = nullptr);
    ~Eter();

    void initializeGameWindow();
    
    void loadTexturesForMinions();
private slots:
    void onPushButtonStartGameClicked();

};
