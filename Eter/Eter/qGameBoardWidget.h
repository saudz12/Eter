#pragma once
#include "qwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QMimeData>
#include <QDropEvent>
#include "qDraggableLabel.h"

class qGameBoardWidget : public QWidget
{
	Q_OBJECT
private:
	const int CARD_WIDTH, CARD_HEIGTH;
	const int BOARD_MAX_SIZE;
	int rows;
	int columns;
public:
	qGameBoardWidget(QWidget* parent = nullptr,int board_max_size=0,int card_width=0,int card_heigth=0,int spacing=0);
	
private:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
public:
	void setBoardPosition(const int x,const int y,const int card_width,const int card_height);
	void addWidgetOnBoard(qDraggableLabel* card,int row,int column);
	void setupEmptyBoard();
};

