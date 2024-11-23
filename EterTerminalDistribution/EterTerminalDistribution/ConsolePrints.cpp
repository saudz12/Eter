#include "ConsolePrints.h"

//move this in a class whenever..

void playerTurn(bool ok) {
	if (ok)
		std::cout << "Player 1(Red's) Turn\n"; 
	else
		std::cout << "Player 2(Blue's) Turn:\n";
}

void showHand(hand& currHand)
{
	std::cout << '\n';
	for (auto& i : currHand)
		std::cout << i.first.GetValue() << ": " << i.second << "\n";
}

void placeOption() {
	std::cout << "Select a card (val) and whre to put it(x and y): ";
}


void helpOption() {
	std::cout << "\nYou can only add cards in proximity of other cards. \n";
	std::cout << "Such the board will extend to a maximum of 3 collumns and rows(3x3) in any directoin. \n";
	std::cout << "The card uses format X position in the board, Y position in the board(with the top right corner AWLWAYS in{0, 0}, x refering to rows and y to collumns) and value to add which will check if a card of that value is available in hand. \n";
	std::cout << "If the selected card is valid, it will be removed from the hand and placed on the board if the space is beyond valid empty or a card of lower value is placed there. \n";
	std::cout << "The first to have a full line(row, collumn or diagonal of size 3) with cards of his color wins. Like checkmate in chess, the other player will be given a chance to ruin your chance of checking/crossing. \n";
	std::cout << " \n";
}
