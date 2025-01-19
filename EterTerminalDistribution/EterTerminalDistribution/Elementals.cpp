#include "Elementals.h"

CommonErrors Elementals::Flame::checkFuncFlame(Board& _board, int16_t _xi, int16_t _yi, Player& _player, int16_t _val, int16_t _xd, int16_t _yd)
{
	BoardErrors tryPlace = _board.CanPlace(_xd, _yd, _val);
	if (_board.CheckPos(_xi, _yi) == BoardErrors::_OUTSIDE_BOUND || _board.CanPlace(_xd, _yd, _val) == BoardErrors::_OUTSIDE_BOUND)
		return CommonErrors::_OUTSIDE_BOUND;
	if (!_board.ViewTop(_xi, _yi).GetIsIllusionCard())
		return CommonErrors::_NOT_ILLUSION;
	return CommonErrors::_NO_ERRORS;
}

void Elementals::Flame::RevevalIllusion(Board& _board, int16_t _xi, int16_t _yi)
{
	_board.RemoveIllusionProperty(_xi, _yi);
}

void Elementals::Flame::PlaceCard(Board& _board, Player& _player, int16_t _val, int16_t _xp, int16_t _yp)
{
	_board.PlaceCard(_player.PlayCard(_val), _xp, _yp);
}

CommonErrors Elementals::Fire::checkFuncFire(Board& _board, int16_t _val)
{
	if (_val < 1 || _val > 4)
		return CommonErrors::_INVALID_CARD_VALUE;
	int occurence = 0;
	for (int i = 0; i < _board.GetRowCount(); i++)
		for (int j = 0; j < _board.GetColCount(); j++)
		{
			occurence += int(_board.ViewTop(i, j).GetValue() == _val);
			if (occurence == 2)
				return CommonErrors::_NO_ERRORS;
		}
	return CommonErrors::_NO_CARDS_OF_VALUE;
}

void Elementals::Fire::ReturnToHand(Board& _board, int16_t _val, Player& _player1, Player& _player2)
{
	for (int i = 0; i < _board.GetRowCount(); i++)
		for (int j = 0; j < _board.GetColCount(); j++)
		{
			auto& top = _board.ViewTop(i, j);
			if (top.GetValue() != _val)
				continue;

			Player& owner = _player1;
			if (top.GetColor() == Colours::BLUE)
				owner = _player2;

			owner.ReturnCard(_board.RemoveTop(i, j));
		}
}
