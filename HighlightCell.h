#pragma once
#include"Cell.h"
#include<utility>
#include<map>
using Position = std::pair<int,int>;
class HighlightCell final 
{
public:
	enum class BorderIlluminationCellsStruct { Checker = 0, first_possible_moves = 1, second_possible_moves = 2, min_size = 1, max_size = 3, hitting_size=2 };
private:
	std::vector<Position> BorderIlluminationCells;
	std::map<Position, Cell>& mCells;
	Cell::State mState;
	
	void HighlightCellBlackChecker(const Position& checker_pos);
	void HighlightCellWhiteChecker(const Position& checker_pos);
	void HighlightCellCheckerHitting(const Position& checker_pos);

	void HighlightQueenForwardLeft(const Position& checker_pos);
	void HighlightQueenForwardRight(const Position& checker_pos);
	
	void HighlightQueenBackLeft(const Position& checker_pos);
	void HighlightQueenBackRight(const Position& checker_pos);
	void HighlightQueen(const Position& checker_pos);
	
	void AddPossibleMoves(const Position& new_pos);
	static bool CheckPossibleMoves(const Position& cur_pos);
	
public:
	HighlightCell(std::map<Position, Cell>& _mCells,Cell::State _mState);
	void SetCells(std::map<Position, Cell>& _mCells);
	void SetState(Cell::State m_state);
	std::vector<Position>& GetBorderIlluminationCells();
	void HighlightCells(const Position& checker_pos);
	void ClearBorderIlluminationCells();
};

