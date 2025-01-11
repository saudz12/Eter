#pragma once
#include "Essential.h"

namespace Elementals {
	class Flame {
	public:
		static CommonErrors checkFuncFlame(Board& _board, int16_t _xi, int16_t _yi, Player& _player, int16_t _val, int16_t _xd, int16_t _yd);
		static void RevevalIllusion(Board& _board, int16_t _xi, int16_t _yi);
		static void PlaceCard(Board& _board, Player& _player, int16_t _val, int16_t _xp, int16_t _yp);
	};

	class Fire {
	public:
		static CommonErrors checkFuncFire(Board& _board, int16_t _val);
		static void ReturnToHand(Board& _board, int16_t _val, Player& _player1, Player& _player2);
	};
}