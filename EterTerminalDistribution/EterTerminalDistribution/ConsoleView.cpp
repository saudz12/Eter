#include "ConsoleView.h"

//move all this in a class whenever..

///----------------------------------------------
void playerTurn(bool ok) {
	if (ok)
		std::cout << "Player 1(Red's) Turn\n"; 
	else
		std::cout << "Player 2(Blue's) Turn:\n";
}


void placeCardOption(uint16_t& val, uint16_t& x, uint16_t& y) {
	std::cout << "Select a card (val): ";
	std::cin >> val;
	awaitCoordinates(x, y);
}

void helpMenuOption() {
	std::cout << "\nYou can only add cards in proximity of other cards. \n";
	std::cout << "Such the board will extend to a maximum of 3 collumns and rows(3x3) in any directoin. \n";
	std::cout << "The card uses format X position in the board, Y position in the board(with the top right corner AWLWAYS in{0, 0}, x refering to rows and y to collumns) and value to add which will check if a card of that value is available in hand. \n";
	std::cout << "If the selected card is valid, it will be removed from the hand and placed on the board if the space is beyond valid empty or a card of lower value is placed there. \n";
	std::cout << "The first to have a full line(row, collumn or diagonal of size 3) with cards of his color wins. Like checkmate in chess, the other player will be given a chance to ruin your chance of checking/crossing. \n";
	std::cout << " \n";

	system("pause");
}

void printOptionsForPlayer()
{
	std::cout << "\nOPTIONS:\n1. Place a card\n2. Show Hand\n3. Show Covered\n4. Check Stack\n";
}

void printMenu()
{
	printOptionsForPlayer();
	std::cout << "5. Use Elemental Power\n6. Test Isolated Spaces in Board\n7. Help\n8. Use explosion card\n9. Use Mage Card\n";
}

void awaitCoordinates(uint16_t& x, uint16_t& y)
{
	std::cout << "Row: "; std::cin >> x;
	std::cout << "\nColumn"; std::cin >> y;
}

void printOptionsForCards(uint16_t& option)
{
	std::cout << "\nOptions:\n1. Place eter card\n2. Play a minion card as an illusion\n3. Play a minion card\n";
	std::cin >> option;
}

void printOptionsForExplostion()
{
	std::cout << "0. Don't use the explosion\n1. Use the explosion\n2. Rotate the explosion\n";
}
//----------------------------------------------

void PrintStandardMenu(int16_t& option, GameOptions enabledElemental, bool usedElemental, GameOptions enabledMages, bool usedMage)
{
	std::cout << "Options:\n1. Place A Card\n2. View Your Hand\n3. View s Stack on Board\n4. Check Your Covered Cards\n5. Check Your Removed Cards\n";
	if (enabledElemental == GameOptions::EnabledElemental && !usedElemental && (enabledMages == GameOptions::DisabledMage || usedMage))
		std::cout << "6. Use An Elemental Card\n";
	else if (enabledMages == GameOptions::EnabledMage && !usedMage && (enabledElemental == GameOptions::DisabledElemental || usedElemental))
		std::cout << "6. Use Your Mage Card\n";
	else if (enabledElemental == GameOptions::EnabledElemental && !usedElemental && enabledMages == GameOptions::EnabledMage && !usedMage) {
		std::cout << "6. Use An Elemental Card\n";
		std::cout << "7. Use Your Mage Card\n";
	}

	std::cin >> option;
}

///---------------------------------------------
void printHand(const Hand& currHand)
{
	std::cout << '\n';
	for (auto& i : currHand)
		std::cout << i.first.GetValue() << ": " << i.second << "\n";
}

void printCovered(const CoveredSet& covered, const ResizeableMatrix& matrix)
{

}