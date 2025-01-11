#include "MoveLaterToGameClass.h"

bool isolatedSpaces(Board& boardModel)
{
	uint16_t l = boardModel.getRowCount(), c = boardModel.getColCount();

	ResizeableMatrix& matr = boardModel.getMatrix();

	//reusing line checker - simulating queue of adjacent nodes
	LineChecker visitedStack;

	uint16_t CardStackCount = 0;

	std::vector<std::vector<bool>> checkedMat;
	uint16_t uniqueVisited = 0;

	checkedMat.resize(l);
	for (int i = 0; i < l; i++)
		checkedMat[i].resize(c, false);

	for (uint16_t i = 0; i < l; i++) {
		for (uint16_t j = 0; j < c; j++) {
			if (matr[i][j].empty())
				continue;
			if (CardStackCount == 0) {
				visitedStack.emplace_back(i, j);
				checkedMat[i][j] = true;
			}
			CardStackCount++;
		}
	}

	while (!visitedStack.empty())
	{
		Score& front = visitedStack.front();
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

	return (uniqueVisited != CardStackCount);
}

void TestIsolatedSpacesFunc(Board& boardModel) {
	uint16_t x;
	uint16_t y;
	std::cin >> x >> y;
	if (boardModel.checkPosition(x, y)) {
		qDebug() << "Invalid position..\n";
		return;
	}
	CardStack removed = std::move(boardModel.getMatrix()[x][y]);
	boardModel.getMatrix()[x][y] = std::move(CardStack());
	if (!isolatedSpaces(boardModel)) {
		qDebug() << "Valid deletion";
		return;
	}
	qDebug() << "Invalid move";
	boardModel.getMatrix()[x][y] = std::move(removed);
}
