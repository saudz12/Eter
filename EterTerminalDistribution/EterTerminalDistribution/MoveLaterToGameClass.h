#pragma once
#include "Board.h"
#include <functional>

//either we implement it at the end of each function (can use set of moves(--note to self: figure it out) instead of deep copy) or just call it like this. true if it has isolated spaces
bool isolatedSpaces(Board& boardModel);

//test function
void TestIsolatedSpacesFunc(Board& boardModel);
