#pragma once
#include <map>
#include "HighlightCell.h"

class MotionSimpleChecker
{
public:

	enum class MoveResult { Successful, Prohibited, ContinueHitting };
private:
	std::map<Position, Cell> &mCells;
	std::vector<Position>& BorderIlluminationCells;
protected:
	void ChangeCellParameters(const Position& pos_cell, bool queen, Cell::State state);

	std::vector<Cell::Direction> CheckHittingRightNeighbours(const Position& new_pos) const;
	std::vector<Cell::Direction> CheckHittingLeftNeighbours(const Position& new_pos) const;

	bool CheckHittingRightForwardNeighbour(const Position& cur_pos) const;
	bool CheckHittingRightBackNeighbour(const Position& cur_pos) const;
	bool CheckHittingLeftForwardNeighbour(const Position& cur_pos) const;
	bool CheckHittingLeftBackNeighbour(const Position& cur_pos) const;

	bool CheckStateNeighbour(const Position& cur_pos, const Position& neighbour_pos) const;
	bool CheckNeighbourNeighbour(const Position& neighbour_neighbour_pos) const;
public:
	MotionSimpleChecker(std::map<Position, Cell>& _mCells,
		std::vector<Position>& _BorderIlluminationCells);
	virtual ~MotionSimpleChecker()=default;
	MoveResult HitChecker(const Position& new_pos);
	MoveResult MoveSimpleChecker(const Position& new_pos);
	std::vector<Cell::Direction> CheckHitting(const Position& new_pos) const;
};

