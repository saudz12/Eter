#pragma once
#include "Board.h"
#include "functionsElementalCards.h"
#include <functional>

//either we implement it at the end of each function - can use set of moves(--note to self: figure it out) instead of deep copy
bool isolatedSpaces(Board& boardModel) {
	uint16_t l = boardModel.getRowCount(), c = boardModel.getColCount();
	
	resizeableMatrix& matr = boardModel.getMatrix();

	//reusing line checker - simulating queue of adjacent nodes
	lineChecker visitedStack;

	uint16_t cardStackCount = 0;

	std::vector<std::vector<bool>> checkedMat;
	uint16_t uniqueVisited = 0;

	checkedMat.resize(l);
	for (int i = 0; i < l; i++)
		checkedMat[i].resize(c, 0);

	for (uint16_t i = 0; i < l; i++) {
		for (uint16_t j = 0; j < c; j++) {
			if (matr[i][j].empty())
				continue;
			if (cardStackCount == 0) {
				visitedStack.emplace_back(i, j);
				checkedMat[i][j] = true;
			}
			cardStackCount++;
		}
	}

	while (!visitedStack.empty())
	{
		score& front = visitedStack.front();
		uint16_t i = front.first;
		uint16_t j = front.second;

		uniqueVisited++;

		if (i != 0) {
			if (!matr[i - 1][j].empty() && !checkedMat[i - 1][j]) {
				checkedMat[i - 1][j] = true;
				visitedStack.emplace_back(i - 1, j);
			}
		}
		if (j != 0) {
			if (!matr[i][j - 1].empty() && !checkedMat[i][j - 1]) {
				checkedMat[i][j - 1] = true;
				visitedStack.emplace_back(i, j - 1);
			}
		}
		if (i != l - 1) {
			if (!matr[i + 1][j].empty() && !checkedMat[i + 1][j]) {
				checkedMat[i + 1][j] = true;
				visitedStack.emplace_back(i + 1, j);
			}
		}
		if (j != c - 1) {
			if (!matr[i][j + 1].empty() && !checkedMat[i][j + 1]) {
				checkedMat[i][j + 1] = true;
				visitedStack.emplace_back(i, j + 1);
			}
		}
		if (i != 0 && j != 0) {
			if (!matr[i - 1][j - 1].empty() && !checkedMat[i - 1][j - 1]) {
				checkedMat[i - 1][j - 1] = true;
				visitedStack.emplace_back(i - 1, j - 1);
			}
		}
		if (i != 0 && j != c - 1) {
			if (!matr[i - 1][j + 1].empty() && !checkedMat[i - 1][j + 1]) {
				checkedMat[i - 1][j + 1] = true;
				visitedStack.emplace_back(i - 1, j + 1);
			}
		}
		if (i != l - 1 && j != 0) {
			if (!matr[i + 1][j - 1].empty() && !checkedMat[i + 1][j - 1]) {
				checkedMat[i + 1][j - 1] = true;
				visitedStack.emplace_back(i + 1, j - 1);
			}
		}
		if (i != l - 1 && j != c - 1) {
			if (!matr[i + 1][j + 1].empty() && !checkedMat[i + 1][j + 1]) {
				checkedMat[i + 1][j + 1] = true;
				visitedStack.emplace_back(i + 1, j + 1);
			}
		}

		visitedStack.pop_front();
	}

	return uniqueVisited != cardStackCount;
}

void TestIsolatedSpacesFunc(Board& boardModel) {
	uint16_t x;
	uint16_t y;
	std::cin >> x >> y;
	if (boardModel.checkPosition(x, y)) {
		std::cout << "Invalid position..\n";
		return;
	}
	cardStack removed = std::move(boardModel.getMatrix()[x][y]);
	boardModel.getMatrix()[x][y] = std::move(cardStack());
	if (!isolatedSpaces(boardModel)) {
		std::cout << "Valid deletion";
		return;
	}
	std::cout << "Invalid move";
	boardModel.getMatrix()[x][y] = std::move(removed);
}

//either we do this so it works for each type of function
void checkFuntion(std::function<void>& funcionToCheck, Board& currModel) {
	//deep copy
	Board oldModel;
	Board::cloneMatrix(currModel, oldModel);

	//funcionToCheck(currModel, T...);

	if (isolatedSpaces(currModel)) {
		Board::cloneMatrix(currModel, oldModel);
	}
}

template<typename T>
void checkFuntion(std::function<void>& funcionToCheck, Board& currModel, T t1) {
	Board oldModel;
	Board::cloneMatrix(currModel, oldModel);
	
	//funcionToCheck(currModel, T...);
}

template<typename T1, typename T2>
void checkFuntion(std::function<void>& funcionToCheck, Board& currModel, T1& t1, T2& t2) {
	Board oldModel;
	Board::cloneMatrix(currModel, oldModel);

	//funcionToCheck(currModel, T...);
}

template<typename T1, typename T2, typename T3>
void checkFuntion(std::function<void>& funcionToCheck, Board& currModel, T1& t1, T2& t2, T3& t3) {
	Board oldModel;
	Board::cloneMatrix(currModel, oldModel);

	//funcionToCheck(currModel, T...);
}

template<typename T1, typename T2, typename T3, typename T4>
void checkFuntion(std::function<void>& funcionToCheck, Board& currModel, T1& t1, T2& t2, T3& t3, T4& t4) {
	Board oldModel;
	Board::cloneMatrix(currModel, oldModel);

	//funcionToCheck(currModel, T...);
}

