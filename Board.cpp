#include "Board.h"

namespace 
{
	const size_t BoardSize = 7;
	const size_t FirstRowWhite = 0;
	const size_t SecondRowWhite = 1;
	const size_t ThirdRowWhite = 2;
	const size_t FirstRowBlack = 7;
	const size_t SecondRowBlack = 6;
	const size_t ThirdRowBlack = 5;
	const size_t NeighbourConst = 1;
	std::map<Position, Cell> CreateMap()
	{
		std::map<Position, Cell>  cells;
		for (size_t i = 0; i <= BoardSize; ++i)
		{
			for (size_t j = 0; j <= BoardSize; ++j)
			{
				const Position cur_pos(i, j);
				Cell cur_cell;
				cells.insert(std::make_pair(cur_pos, cur_cell));
			}
		}
		return cells;
	}
	bool CheckParity(const size_t number)
	{
		return number % 2;
	}
	bool CheckWhite(const Position& cur_pos)
	{

		const auto& [X, Y] = cur_pos;
		return	(Y == FirstRowWhite && CheckParity(X)) || 
				(Y == SecondRowWhite && !CheckParity(X)) ||
				(Y == ThirdRowWhite && CheckParity(X));
	}
	bool CheckBlack(const Position& cur_pos)
	{

		const auto& [X, Y] = cur_pos;
		return  (Y == FirstRowBlack && !CheckParity(X)) ||
				(Y == SecondRowBlack && CheckParity(X)) ||
				(Y == ThirdRowBlack && !CheckParity(X));
	}
	bool CheckExitFromBoard(const Position& cur_pos)
	{

		const auto& [X, Y] = cur_pos;
		return  X<0 || X>BoardSize || Y<0 || Y>BoardSize;
	}
	Cell::State CheckState(const Position& cur_pos)
	{
		if (CheckWhite(cur_pos))return Cell::State::WHITE;
		if (CheckBlack(cur_pos))return Cell::State::BLACK;
		return Cell::State::BLANK;
	}
	Cell::State ChangeState(Cell::State cur_state)
	{
		if (cur_state == Cell::State::WHITE)
			return Cell::State::BLACK;
		return Cell::State::WHITE;
	}
}
std::map<Position, Cell> Board::mCells = CreateMap();



bool Board::CheckNeededHeating(const Position& checker_pos)
{
	if (NeededHitting.empty()) return true;
	for(const auto &it:NeededHitting)
	{
		if (it == checker_pos)
			return true;
	}
	return false;
}

bool Board::CheckPosition(const Position& checker_pos)
{
	if (BorderIlluminationCells.size()== size_t(HighlightCell::BorderIlluminationCellsStruct::min_size)||BorderIlluminationCells.empty())return false;
	if(checker_pos!=BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)]
		&&mCells[checker_pos].GetState()==mState)
	{
		highlight_cell.HighlightCells(checker_pos);
		return false;
	}
	if(mCells[checker_pos].GetState() == Cell::State::BLANK)return true;
	return false;
}

void Board::ChangeCurState(MotionSimpleChecker::MoveResult result)
{
	if (result != MotionSimpleChecker::MoveResult::Successful)return;
	mState = ChangeState(mState);
}


void Board::CheckHittingNextMoveAllCheckers()
{
	NeededHitting.clear();
		for(size_t i=0;i<= BoardSize;++i)
	{
		for(size_t j=0;j<= BoardSize;++j)
		{
			const Position cur_pos(i, j);
			std::vector<Cell::Direction> hitting_directions;
			auto& cur_cell = mCells[cur_pos];
			if (cur_cell.GetState() == Cell::State::BLANK) continue;
			if(cur_cell.GetQueen())
			{
				hitting_directions=motion_queen.CheckHittingQueen(cur_pos);
			}
			else {
				hitting_directions=motion_simple_checker.CheckHitting(cur_pos);
			}
			cur_cell.SetHitting(hitting_directions);
			if(!hitting_directions.empty()&&cur_cell.GetState()==mState)
			{
				NeededHitting.push_back(cur_pos);
			}
		}
	}
}

bool Board::CheckMoves(const Position& new_pos) const
{
	if (BorderIlluminationCells.size() == size_t(HighlightCell::BorderIlluminationCellsStruct::hitting_size) &&
		BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::first_possible_moves)] == new_pos) return true;
	else if (BorderIlluminationCells.size()> size_t(HighlightCell::BorderIlluminationCellsStruct::hitting_size)&&
		(BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::first_possible_moves)] == new_pos||
		BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::second_possible_moves)] == new_pos) )return true;
	return false;
}


Board::Board():mState(Cell::State::WHITE),
highlight_cell(HighlightCell(mCells,mState)),BorderIlluminationCells(highlight_cell.GetBorderIlluminationCells()),
motion_simple_checker(MotionSimpleChecker(mCells, highlight_cell.GetBorderIlluminationCells())),
motion_queen(MotionQueen(mCells, highlight_cell.GetBorderIlluminationCells()))
{
	ResetMap();
}
void Board::ResetMap()
{
	mState = Cell::State::WHITE;
	for(size_t i=0;i<= BoardSize;++i)
	{
		for(size_t j=0;j<= BoardSize;++j)
		{
			const Position cur_pos(i, j);
			mCells[cur_pos].SetQueen(false);
			mCells[cur_pos].SetState(CheckState(cur_pos));
		}
	}
}

void Board::HighlightCells(const Position& checker_pos)
{
	if(!BorderIlluminationCells.empty())
	{
		highlight_cell.ClearBorderIlluminationCells();
	}
	if (!CheckNeededHeating(checker_pos))return;
	highlight_cell.SetState(mState);
	highlight_cell.HighlightCells(checker_pos);
	BorderIlluminationCells = highlight_cell.GetBorderIlluminationCells();
}



std::map<Position, Cell>& Board::GetCells()
{
	return mCells;
}

MotionSimpleChecker::MoveResult Board::MoveChecker(const Position& new_pos)
{
	if (CheckExitFromBoard(new_pos)) return MotionSimpleChecker::MoveResult::Prohibited;
	Cell&  new_cell= mCells[new_pos];
	MotionSimpleChecker::MoveResult result;
	if(!CheckPosition(new_pos))return MotionSimpleChecker::MoveResult::Prohibited;
	const Position cur_pos = BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)];
	Cell& cur_cell = mCells[cur_pos];
	if(cur_cell.GetQueen())
	{
		result =motion_queen.MoveQueenChecker(new_pos);
		cur_cell.SetBorderIllumination(false);
	}
	else if (!CheckMoves(new_pos))result= MotionSimpleChecker::MoveResult::Prohibited;
	else if(!cur_cell.GetHitting().empty())
	{
		result = motion_simple_checker.HitChecker(new_pos);
	}
	else {
		result = motion_simple_checker.MoveSimpleChecker(new_pos);
	}
	highlight_cell.ClearBorderIlluminationCells();
	ChangeCurState(result);
	CheckHittingNextMoveAllCheckers();
	return result;
}

