#pragma once
#include"Cell.h"
#include "MotionSimpleChecker.h"
#include<map>
#include<utility>
#include <vector>
#include "MotionQueen.h"

class Board final
{
	static std::map<Position, Cell> mCells;
	std::vector<Position>& BorderIlluminationCells;
	Cell::State mState;
	std::vector<Position> NeededHitting;
	HighlightCell highlight_cell;
	MotionSimpleChecker motion_simple_checker;
	MotionQueen motion_queen;
	
	bool CheckNeededHeating(const Position& checker_pos);
	bool CheckPosition(const Position& checker_pos);
	void ChangeCurState(MotionSimpleChecker::MoveResult result);
	void CheckHittingNextMoveAllCheckers();
	bool CheckMoves(const Position& new_pos) const;

public:
	Board();
	void ResetMap();
	void HighlightCells(const Position& checker_pos);
	static std::map<Position, Cell>& GetCells();
	MotionSimpleChecker::MoveResult MoveChecker(const Position& new_pos);
	
};

