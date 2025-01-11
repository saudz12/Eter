#pragma once
#define PLACE_OPTION 1
#define HAND_OPTION 2
#define HELP_OPTION 3

#include "Includes.h"
#include "Player.h"

///Basic Interaction
void playerTurn(bool ok);

void placeCardOption(uint16_t& val, uint16_t& x, uint16_t& y);

void helpMenuOption();

void printOptionsForPlayer();

void printMenu();

void awaitCoordinates(uint16_t& x, uint16_t& y);

void printOptionsForCards(uint16_t& option);

void printOptionsForExplostion();
//--------------------------------------------- Remake

void PrintStandardMenu(int16_t& option, GameOptions enabledElemental, bool usedElemental, GameOptions enabledMages, bool usedMage);
void PlayerTurn(Colours currCol);

///Player Interction
void printHand(const Hand& currHand);
void printHand(const CardCounter& currHand);
void printCovered(const CoveredSet& covered, const ResizeableMatrix& matrix);





