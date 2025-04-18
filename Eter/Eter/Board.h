#pragma once
//bound=boundary
#define TOP_BOUND -1
#define LEFT_BOUND -1
#define BOTTOM_BOUND 1
#define RIGHT_BOUND 1
#define INSIDE_BOUND 0
#define OUTSIDE_BOUND 2
#define RED_ADD 1
#define BLUE_ADD 2
#define RED_ADD_BLUE_DEC 3
#define BLUE_ADD_RED_DEC 4
#define RED_DEC 5
#define BLUE_DEC 6
#define ZERO 7

#include "Player.h"
#include "ExplosionCard.h"
#include "Includes.h"
#include "json.hpp"

using json = nlohmann::json;

enum class BoardErrors : int16_t {
	_OUTSIDE_BOUND,
	_INSIDE_BOUND,
	_EXTEND_BOUND,
	_EMPTY_BOARD,

	_INVALID_VAL,
	_NONE_LEFT_OF_VAL, 
	
	_HOLE_PROPERTY,
	_ETER_PROPERTY,
	ILLUSION_PROPERTY,
	_NO_ERRORS,
};

enum class MarginType : int16_t {
	MARGIN_TOP,
	MARGIN_BOT,
	MARGIN_LEFT,
	MARGIN_RIGHT,

	INVALID_MARGIN
};

MarginType GetMargin(char _type);

enum class BoardChanges : int16_t {
	_TOP_BOUND,
	_BOT_BOUND,
	_LEFT_BOUND,
	_RIGHT_BOUND,
	_TOP_LEFT_BOUND,
	_TOP_RIGHT_BOUND,
	_BOT_LEFT_BOUND,
	_BOT_RIGHT_BOUND,
	_EMPTY_BOARD,
	_NO_CHANGES
};

enum class StackConditions : int16_t {
	POPULATED,
	EMPTY,
	HOLE,
	ETER
};

enum class OrientationType : int16_t {
	HORIZONTAL,
	VERTICAL
};

enum class AdjacentType : int16_t {
	NEIGHBOURING,
	CORNERING,
	NOT_ADJACENT,
	SAME_STACK
};

class Board
{
private:
	ResizeableMatrix m_matrix;
	
	//score by color management
	LineChecker m_rowChecker;
	LineChecker m_colChecker;
	Score m_firstDiag;
	Score m_seconDiag;

	//for explosions, keep check either here or in game
	uint16_t m_lineCnt;

	//matrix size management
	uint16_t m_max_size;
	bool m_reachedMaxSize;

	//score counter on each line
	void increaseOnColorColumn(uint16_t x, uint16_t y, Colours col);
	void increaseOnColorRow(uint16_t x, uint16_t y, Colours col);
	void increaseOnColorDiagonal(uint16_t x, uint16_t y, Colours col);
	void increaseOnColorDiagonalNoResize(uint16_t x, uint16_t y, Colours col);

	//check position to board bounds
	int16_t XBoundTest(int16_t x);
	int16_t YBoundTest(int16_t y);

	//other check
	bool posPlaceTest(int16_t x, int16_t y, const MinionCard& card);

	//will be changed if you can remove from middle
	void removeLeftMargin();
	void removeRightMargin();
	void removeTopMargin();
	void removeBottomMargin();

	//other interactions

public:

	Board(uint16_t size);
	Board();
	~Board() = default;

	//Update board
	//only checks it. to modify it it needs to return a reference. do the check somewhere beforehand to get modifyable card

#pragma region new_code
	//moves and other tricky thigs camn be modifyed to bools to check if they executed properly

	StackConditions CheckStackCondition(int16_t _x, int16_t _y); 
	BoardErrors CheckPos(int16_t _x, int16_t _y); 
	BoardErrors CanPlace(int16_t _x, int16_t _y, int16_t _val);
	BoardChanges GetChangeFlag(int16_t _x, int16_t _y); 
	void UpdateOnColor(uint16_t _x, uint16_t _y, Colours _col, OrientationType _side, CardAction _action);
	void ExtendBoard(BoardChanges _flag); 
	void PlaceCard(MinionCard&& _toPlace, int16_t _x, int16_t _y); 
	MinionCard&& RemoveTop(int16_t _x, int16_t _y); 
	MinionCard&& RemoveCard(int16_t _x, int16_t _y, int16_t _pos); 
	void CreateHole(int16_t _x, int16_t _y); 
	void RemoveLine(int16_t _line, LineType _type); 
	void RemoveRow(int16_t _line); 
	void RemoveColumn(int16_t _line); 
	bool ShiftLine(int16_t _line, LineType _type, Directions _direction);
	bool LineContainsColour(int16_t _line, LineType _type, Colours _col); 
	int16_t GetNrOfCardsOnLine(int16_t _line, LineType _type); 
	void PlayCard(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD); //from top of stack (xs ys) to top of pos stacl (xd yd)
	void MoveStack(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD); //replaces the stack on destination
	void SwitchStacks(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);
	void MirrorEdge(BoardChanges _margin);
	bool CheckTopIsEter(int16_t _x, int16_t _y);
	void RemoveIllusionProperty(int16_t _x, int16_t _y);
	const MinionCard& ViewTop(int16_t _x, int16_t _y); //wierd??

	//checks if the coordonates of 2 stacks ar adjacent
	static AdjacentType CheckAdjacent(int16_t _xS, int16_t _yS, int16_t _xD, int16_t _yD);
	bool isEmptySpace(int16_t _x, int16_t _y);

	//add lines to border ///vezi ca ai ExtendBoard. foloseste-l in loc de astea :). Board changes impune ce cum vrei sa adaugi inii.
	void AddLineToLeft();
	void AddLineToRight();
	void AddLineOnTop();
	void AddLineOnBottom();
	void SetEmptyBoard(Colours color);

	bool isValidPosition(int16_t _x, int16_t _y);
	void PlaceIllusion(MinionCard&& _toPlace,int16_t _x,int16_t _y);//illusionCard
	bool CanCoverIllusion(uint16_t _x,uint16_t _y,uint16_t _val);
	void RevealIllusion(int16_t _x, int16_t _y);
	bool isIllusionOnPos(int16_t _x, int16_t _y);
#pragma endregion

	//use it only when placing cards
	Colours checkWin(int16_t x, int16_t y, Colours col);
	//use it after removing minions and/or using elemental/mage cards
	Colours checkWin();
	Colours checkWinFullBoard();
	Colours checkDiagWin();

	uint16_t getRowCount();
	uint16_t getColCount();
	uint16_t getMaxSize();
	bool isMatMaxSize();

#pragma region remove_later

	MinionCard& getCardOnPos(int16_t x, int16_t y);
	int16_t setPos(int16_t& x, int16_t& y, const MinionCard& card, Player& p);
	int16_t setPosWaterfall(int16_t x, int16_t y, const MinionCard& card);
	int16_t removePos(int16_t x, int16_t y);
	int16_t removeStack(int16_t x, int16_t y);

	LineChecker& getRowChecker();
	LineChecker& getColChecker();
	ResizeableMatrix& getMatrix();
	CardStack& getStackOnPos(uint16_t x, uint16_t y);
	uint16_t getLineCount();
	//false = valid, true = not good - sorry --change them later
	bool checkPosition(uint16_t x, uint16_t y);
	//false = valid, true = not good - sorry
	bool checkPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
	void printBoard(bool _debug);

	bool removeRow(uint16_t x);
	bool removeColumn(uint16_t y);

#pragma endregion

	void setMatrix(const ResizeableMatrix& matrix);
	
	void updateFirstDiagChecker(uint16_t option);
	void updateSeconDiagChecker(uint16_t option);
	void updateColChecker(uint16_t y, uint16_t option);
	void updateRowChecker(uint16_t x, uint16_t option);

	bool isBoardFilled();
	bool isBoardEmpty();

	std::vector<MarginType> checkForUpdates();

	static void cloneMatrix(const Board& from, Board& to);

	std::vector<MarginType> applyExplosionOnBoard(const ExplosionCard& explCard, Player& pl1, Player& p2,bool isForTest);
	bool tryApplyExplosionOnBoard(const ExplosionCard& explCard,Player& pl1,Player& pl2);
	bool canPlayExplosion();

	json SerialiseMatrix();
	std::string FormatPair(int integer1, int integer2);
	void DeserializeMatrix(const json& jsonMatrix);
	std::pair<int, int> ParsePair(const std::string& str);

	void updateRowCheckerDeserialize();
	void updateColCheckerDeserialize();
	void updateDiagsDeserialize();
};

