#pragma once
#include "qwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QMimeData>
#include <QDropEvent>
#include <qpointer.h>
#include "qdir.h"

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <tuple>


#include "qDraggableLabel.h"

struct PairHash1 {
	std::size_t operator()(const std::pair<int, int>& p) const {

		std::size_t hash1 = std::hash<int>()(p.first);
		std::size_t hash2 = std::hash<int>()(p.second);

		return hash1 ^ (hash2 * 31);
	}
};

class qGameBoardWidget : public QWidget
{
	Q_OBJECT
private:
	const int CARD_WIDTH, CARD_HEIGTH;
	const int BOARD_MAX_SIZE;

	std::unordered_set<std::pair<int, int>,PairHash1> m_emptyPositions;
	std::unordered_map<std::pair<int, int>, std::deque<QLabel*>,PairHash1> m_cardPosition;
	std::unordered_map<std::pair<int, int>, std::deque<QPixmap>, PairHash1> m_pixmapPosition;

	int maxRow, maxColumn;
	int minRow, minColumn;
	
	int currentCardValue;
	QString currentCardColor;

	QPixmap currCardPixmap;

	bool wasFirstCardPlaced;
	bool wasFixedBoardCreated;
	bool wasIllusionChecked;
	bool isCurrentCardIllusion;
public:
	qGameBoardWidget(QWidget* parent = nullptr,int board_max_size=0,int card_width=0,int card_heigth=0,int spacing=0);
	
private:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void handleMinionCardDrop(QDropEvent* event);
	void resizeEvent(QResizeEvent* event) override;
	void expandBoard(int& row,int& column);
	bool checkPositionsForWhiteSpaces(QGridLayout*& gridLayout,int row,int column,
		bool& existsOnLeftCol,bool& existsOnRightCol ,bool& existsOnTopRow, bool& existsOnBottomRow);
	int16_t verifyTopCardsExist(QGridLayout*& gridLayout, const int& row, const int& column);
	int16_t verifyLeftCardsExist(QGridLayout*& gridLayout, const int& row, const int& column);
	int16_t verifyBottomCardsExist(QGridLayout*& gridLayout, const int& row, const int& column);
	int16_t verifyRightCardsExist(QGridLayout*& gridLayout, const int& row, const int& column);
	void updateCardsForTopRow(QGridLayout*& gridLayout,const int& row,const int& column,const int& addRow);
	void updateCardsForLeftCol(QGridLayout*& gridLayout,const int& row,const int& column,const int& addColumn);
	bool checkPosition( QGridLayout*& board, int i, int j);
	void addRowBelow(QGridLayout*& gridLayout,int& row,int& column);
	void addColumnRight(QGridLayout*& gridLayout, int& row, int& column);
	void addRowTop(QGridLayout*& gridLayout, int& row, int& column);
	void addColumnLeft(QGridLayout*& gridLayout, int& row, int& column);
	void redrawBoard(QGridLayout*& gridLayout);
	void clearBoard(QGridLayout*& gridLayout);
	void placeFirstCard(QGridLayout*& gridLayout,int& row,int& column);
	QLabel* createNewMinionCard();
	void addNewMinionCardToGrid(QLabel*& newCard,QGridLayout*& gridLayout, int& row, int& column);
	void removeWidgetFromGrid(QGridLayout*& gridLayout, int row, int column);
	std::vector<std::function<void(QGridLayout*&, int&, int&)>> createFunctionCallsVector(QGridLayout*& gridLayout, int&row,int&column);
	void stretchGridLayout(QGridLayout*& gridLayout);
	void createFixedSizeBoard(QGridLayout*& gridLayout);
	void updateMinMaxRowCol();
	void createEmptySpacesForRedrawnBoard();
	void addEmptySpacesToRedrawnBoard(QGridLayout*& gridLayout);
	void addCardsToRedrawnBoard(QGridLayout*& gridLayout);
	void loadIllusion(Colours color);
	void scaleCoordinates(int& row, int& col);
public:
	void setBoardPosition(const int x,const int y,const int card_width,const int card_height);
	void addWidgetOnBoard(QPointer<qDraggableLabel>& card,int row,int column);
	void setupEmptyBoard();
	QLabel* createWhiteSpace();
signals:
	void boardResized();
	void cardDropAccepted(const QMimeData* mimeData,int row,int column);
	void isRadioButtonToggledIllusions(bool* toggled);
public slots:
	void removeCard(int row,int col, IllusionErrors error);
};

