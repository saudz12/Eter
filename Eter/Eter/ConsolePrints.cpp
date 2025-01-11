#include "ConsolePrints.h"

//move this in a class whenever..

void playerTurn(bool ok) {
	if (ok)
		qDebug() << "Player 1(Red's) Turn\n"; 
	else
		qDebug() << "Player 2(Blue's) Turn:\n";
}

void showHand(Hand& currHand)
{
	qDebug() << '\n';
	for (auto& i : currHand)
		qDebug() << i.first.GetValue() << ": " << i.second << "\n";
}

void placeOption() {
	qDebug() << "Select a card (val) and whre to put it(x and y): ";
}


void helpOption() {
	qDebug() << "\nYou can only add cards in proximity of other cards. \n";
	qDebug() << "Such the board will extend to a maximum of 3 collumns and rows(3x3) in any directoin. \n";
	qDebug() << "The card uses format X position in the board, Y position in the board(with the top right corner AWLWAYS in{0, 0}, x refering to rows and y to collumns) and value to add which will check if a card of that value is available in hand. \n";
	qDebug() << "If the selected card is valid, it will be removed from the hand and placed on the board if the space is beyond valid empty or a card of lower value is placed there. \n";
	qDebug() << "The first to have a full line(row, collumn or diagonal of size 3) with cards of his color wins. Like checkmate in chess, the other player will be given a chance to ruin your chance of checking/crossing. \n";
	qDebug() << " \n";
}

void printOptionsForPlayer()
{
	qDebug() << "\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Show Covered\n4. Check Stack\n";
}

void printMenu()
{
	printOptionsForPlayer();
	qDebug() << "5. Use Elemental Power\n6. Test Isolated Spaces in Board\n7. Help\n8. Use explosion card\n9. Use Mage Card\n";
}

void printOptionsForCards()
{
	qDebug() << "\nOptions:\n1. Place eter card\n2. Play a minion card as an illusion\n3. Play a minion card\n";
}

void printExplosionOptions()
{
	qDebug() << "0. Don't use the explosion\n1. Use the explosion\n2. Rotate the explosion\n";
}