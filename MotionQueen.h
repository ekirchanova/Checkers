#pragma once
#include "HighlightCell.h"
#include "MotionSimpleChecker.h"

class MotionQueen final : public MotionSimpleChecker
{
	std::map<Position, Cell>& mCells;
	std::vector<Position>& BorderIlluminationCells;
	
	std::vector<Cell::Direction> CheckHittingQueenRightNeighbours(const Position& new_pos);
	std::vector<Cell::Direction> CheckHittingQueenLeftNeighbours(const Position& new_pos);

	bool CheckHittingQueenRightForwardNeighbour(const Position& cur_pos);
	bool CheckHittingQueenRightBackNeighbour(const Position& cur_pos);
	bool CheckHittingQueenLeftForwardNeighbour(const Position& cur_pos);
	bool CheckHittingQueenLeftBackNeighbour(const Position& cur_pos);

	Cell::Direction  FindQueenDirection(const Position& new_pos);

	enum class QueenMove { SIMPLE_MOVE, HIT_MOVE, PROHIBITED };
	QueenMove MoveOneCellQueen(const Position& cur_pos, const Position& next_pos, const Position& last_pos);
	bool MoveQueenLeftForward(const Position& cur_pos, const Position& new_pos);
	bool MoveQueenRightForward(const Position& cur_pos, const Position& new_pos);
	bool MoveQueenLeftBack(const Position& cur_pos, const Position& new_pos);
	bool MoveQueenRightBack(const Position& cur_pos, const Position& new_pos);
public:
	MotionQueen(std::map<Position, Cell>& _mCells,
		std::vector<Position>& _BorderIlluminationCells);
	std::vector<Cell::Direction> CheckHittingQueen(const Position& new_pos);
	MotionSimpleChecker::MoveResult MoveQueenChecker(const Position& new_pos);
};

