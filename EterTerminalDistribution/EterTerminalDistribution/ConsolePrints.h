#pragma once
#define PLACE_OPTION 1
#define HAND_OPTION 2
#define HELP_OPTION 3

#include "Includes.h"
#include "Player.h"


void playerTurn(bool ok);

void placeOption();

void showHand(hand& currHand);

void helpOption();


