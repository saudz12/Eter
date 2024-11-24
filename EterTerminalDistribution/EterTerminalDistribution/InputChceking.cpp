#include "InputChceking.h"

const int CheckHurricaneInput(Board& board, uint16_t lineCnt, std::string_view type, std::string_view direction)
{
	const resizeableMatrix& matrix = board.getMatrix();

	if (type != ID_ROW && type != ID_COLUMN) {
		return INVALID_LINE_TYPE;
	}

	if (lineCnt < 0 || type == ID_ROW && lineCnt > board.getLineCount() - 1 || type == ID_COLUMN && lineCnt > board.getColCount() - 1) {
		return OUTSIDE_BOUNDS;
	}
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

	if (type == ID_ROW && direction != DIR_LEFT && direction != DIR_RIGHT || type == ID_COLUMN && direction != DIR_UP && direction != DIR_DOWN) {
		return INVALID_DIRECTION;
	}
	return NO_ERRORS;
}
