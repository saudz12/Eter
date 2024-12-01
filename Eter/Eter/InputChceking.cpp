#include "InputChecking.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction)
{
	const resizeableMatrix& matrix = board.getMatrix();

	//valid typing
	if (type != ID_ROW && type != ID_COLUMN) {
		return INVALID_LINE_TYPE;
	}

	//insine bounds
	if (lineCnt < 0 || type == ID_ROW && lineCnt > board.getLineCount() - 1 || type == ID_COLUMN && lineCnt > board.getColCount() - 1) {
		return OUTSIDE_BOUNDS;
	}

	//valid direction
	if (type == ID_ROW && direction != DIR_LEFT && direction != DIR_RIGHT || type == ID_COLUMN && direction != DIR_UP && direction != DIR_DOWN) {
		return INVALID_DIRECTION;
	}

	//full line and no eters
	if (type == ID_ROW) {
		for (auto& stack : matrix[lineCnt])
		{
			if (stack.empty()) {
				return INVALID_LINE_STRUCTURE;
			}
			if (stack.back().GetIsEterCard())
			{
				return ETER_PROPERTY_VIOALTION;
			}
		}
	}
	if (type == ID_COLUMN) {
		for (auto& row : matrix)
		{
			if (row[lineCnt].empty()) {
				return INVALID_LINE_STRUCTURE;
			}
			if (row[lineCnt].back().GetIsEterCard())
			{
				return ETER_PROPERTY_VIOALTION;
			}
		}
	}

	return NO_ERRORS;
}

const int CheckWhirlpool(Board& board, uint16_t x, uint16_t y, std::string_view linetype, std::string_view preference)
{
	resizeableMatrix& matrix = board.getMatrix();

	int ratioX = (linetype == ID_ROW) ? 0 : 1;
	int ratioY = (linetype == ID_ROW) ? 1 : 0;

	if (linetype != ID_ROW && linetype != ID_COLUMN) {
		return INVALID_LINE_TYPE;
	}

	if (linetype == ID_ROW && (preference != DIR_LEFT || preference != DIR_RIGHT) || linetype == ID_COLUMN && (preference != DIR_UP || preference != DIR_DOWN)) {
		return INVALID_DIRECTION;
	}
	if (!matrix[x][y].empty()) {
		return EMPTY_SPACE;
	}

	if ((x < 0 || x >= board.getRowCount()) || (y < 0 || y >= board.getColCount())) {
		return OUTSIDE_BOUNDS;
	}

	//check if the adjacent spaces are out of bounds
	if (linetype == ID_ROW) {
		if (y - 1 < 0 || y + 1 >= board.getColCount())
		{
			return ADJACENT_OUTSIDE_BOUNDS;
		}
	}
	else {
		if (x - 1 < 0 || x + 1 >= board.getRowCount())
		{
			return ADJACENT_OUTSIDE_BOUNDS;
		}
	}

	//check if the adjancent spaces are empty
	if (matrix[x - ratioX][y - ratioY].empty() || matrix[x + ratioX][y + ratioY].empty())
	{
		return ADJACENT_SPACES_EMPTY;
	}
	//check if one of the adjancent spaces is an eter card
	if (matrix[x - ratioX][y - ratioY].back().GetIsEterCard() || matrix[x + ratioX][y + ratioY].back().GetIsEterCard())
	{
		return ETER_PROPERTY_VIOALTION;
	}

	return NO_ERRORS;
}
