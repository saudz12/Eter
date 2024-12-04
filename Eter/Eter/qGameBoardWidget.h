#pragma once
#include "qwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QMimeData>
#include <QDropEvent>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "qDraggableLabel.h"

class qGameBoardWidget : public QWidget
{
	Q_OBJECT
private:
	struct PairHash {
		std::size_t operator()(const std::pair<int, int>& p) const {
			// Combine the hash of both elements
			std::size_t hash1 = std::hash<int>()(p.first);
			std::size_t hash2 = std::hash<int>()(p.second);

			// Combine the two hashes using bitwise XOR and a prime multiplier
			return hash1 ^ (hash2 * 31);
		}
	};
private:
	const int CARD_WIDTH, CARD_HEIGTH;
	const int BOARD_MAX_SIZE;
	int rows;
	int columns;
	int rowsWithEmptySpaces, columnsWithEmptySpaces;
	std::unordered_set<std::pair<int, int>,PairHash> m_possiblePositions;
	std::unordered_map<std::pair<int, int>, QLabel*,PairHash> m_cardPosition;
	int xMax, yMax;
public:
	qGameBoardWidget(QWidget* parent = nullptr,int board_max_size=0,int card_width=0,int card_heigth=0,int spacing=0);
	
private:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void expandBoard(int& row,int& column);
	std::vector<std::pair<int,int>>& checkPositionsForWhiteSpaces(QGridLayout*& gridLayout,int row,int column,
		bool& existsOnLeftCol,bool& existsOnRightCol ,bool& existsOnTopRow, bool& existsOnBottomRow);
	bool checkPosition( QGridLayout*& board, int i, int j);
public:
	void setBoardPosition(const int x,const int y,const int card_width,const int card_height);
	void addWidgetOnBoard(qDraggableLabel* card,int row,int column);
	void setupEmptyBoard();
	QLabel*& createWhiteSpace();

	
};

