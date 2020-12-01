#include "MotionSimpleChecker.h"
namespace
{
	const size_t BoardSize = 7;
	const size_t NeighbourConst = 1;
	
	
	bool CheckLeftBoarder(const Position& checker_pos)
	{
		return checker_pos.first == 0;
	}
	bool CheckRightBoarder(const Position& checker_pos)
	{
		return checker_pos.first == BoardSize;
	}
	bool CheckUpBoarder(const Position& checker_pos)
	{
		return checker_pos.second == 0;
	}
	bool CheckDownBoarder(const Position& checker_pos)
	{
		return checker_pos.second == BoardSize;
	}
	bool CheckBoarders(const Position& checker_pos)
	{
		return CheckRightBoarder(checker_pos)|| CheckLeftBoarder(checker_pos) ||
			CheckDownBoarder(checker_pos)||CheckUpBoarder(checker_pos);
	}
	bool CheckQueen(const Position& checker_pos, Cell::State cur_state)
	{
		return cur_state == Cell::State::WHITE && CheckDownBoarder(checker_pos) ||
			cur_state == Cell::State::BLACK && CheckUpBoarder(checker_pos);
	}
}
MotionSimpleChecker::MoveResult MotionSimpleChecker::MoveSimpleChecker(const Position& new_pos)
{
	const Position& old_pos = BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)];
	Cell& old_cell = mCells[old_pos];
	ChangeCellParameters(new_pos, old_cell.GetQueen(), old_cell.GetState());
	ChangeCellParameters(old_pos, false, Cell::State::BLANK);
	if (CheckQueen(new_pos,mCells[new_pos].GetState())) mCells[new_pos].SetQueen(true);
	return MoveResult::Successful;
}
MotionSimpleChecker::MotionSimpleChecker(std::map<Position, Cell>& _mCells, std::vector<Position>& _BorderIlluminationCells):mCells(_mCells),
BorderIlluminationCells(_BorderIlluminationCells)
{
}
void MotionSimpleChecker::ChangeCellParameters(const Position& pos_cell, bool queen, Cell::State state)
{
	Cell& cell = mCells[pos_cell];
	cell.SetQueen(queen);
	cell.SetState(state);
	cell.SetHitting(std::vector<Cell::Direction>());
}
MotionSimpleChecker::MoveResult MotionSimpleChecker::HitChecker(const Position& new_pos)
{
	const auto& [hitting_x, hitting_y] = BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)];
	const auto& [new_x, new_y] = new_pos;
	const Position victim_pos((hitting_x + new_x) / 2, (hitting_y + new_y) / 2);
	MoveSimpleChecker(new_pos);
	ChangeCellParameters(victim_pos, false, Cell::State::BLANK);
	const std::vector<Cell::Direction>  direction = CheckHitting(new_pos);
	if (direction.empty()) {
		return MotionSimpleChecker::MoveResult::Successful;
	}
	mCells[new_pos].SetHitting(direction);
	BorderIlluminationCells.push_back(new_pos);
	return  MotionSimpleChecker::MoveResult::ContinueHitting;
}
std::vector<Cell::Direction> MotionSimpleChecker::CheckHitting(const Position& new_pos) const
{
	if (CheckLeftBoarder(new_pos))
	{
		return CheckHittingRightNeighbours(new_pos);
	} if (CheckRightBoarder(new_pos))
	{
		return CheckHittingLeftNeighbours(new_pos);
	}
	std::vector<Cell::Direction> result = CheckHittingRightNeighbours(new_pos);
	std::vector<Cell::Direction> temp = CheckHittingLeftNeighbours(new_pos);
	result.insert(result.end(), temp.begin(), temp.end());
	return result;
}
std::vector<Cell::Direction> MotionSimpleChecker::CheckHittingRightNeighbours(const Position& new_pos) const
{
	std::vector<Cell::Direction> result;
	if (CheckHittingRightBackNeighbour(new_pos))
		result.push_back(Cell::Direction::Back_Right);
	if (CheckHittingRightForwardNeighbour(new_pos))
		result.push_back(Cell::Direction::Forward_Right);
	return  result;
}

std::vector<Cell::Direction> MotionSimpleChecker::CheckHittingLeftNeighbours(const Position& new_pos) const
{
	std::vector<Cell::Direction> result;
	if (CheckHittingLeftBackNeighbour(new_pos))
		result.push_back(Cell::Direction::Back_Left);
	if (CheckHittingLeftForwardNeighbour(new_pos))
		result.push_back(Cell::Direction::Forward_Left);
	return  result;
}
bool MotionSimpleChecker::CheckHittingRightForwardNeighbour(const Position& cur_pos) const
{
	const auto& [cur_x, cur_y] = cur_pos;
	const Position neigh_pos(std::make_pair(cur_x + NeighbourConst, cur_y + NeighbourConst));
	if (CheckStateNeighbour(cur_pos, neigh_pos)) {
		return false;
	}
	const Position neigh_neigh_pos(std::make_pair(cur_x + 2 * NeighbourConst, cur_y + 2 * NeighbourConst));
	return  CheckNeighbourNeighbour(neigh_neigh_pos);
}

bool MotionSimpleChecker::CheckHittingRightBackNeighbour(const Position& cur_pos) const
{
	const auto& [cur_x, cur_y] = cur_pos;
	const Position neigh_pos(std::make_pair(cur_x + NeighbourConst, cur_y - NeighbourConst));
	if (CheckStateNeighbour(cur_pos, neigh_pos)) {
		return false;
	}
	const Position neigh_neigh_pos(std::make_pair(cur_x + 2 * NeighbourConst, cur_y - 2 * NeighbourConst));
	return  CheckNeighbourNeighbour(neigh_neigh_pos);
}

bool MotionSimpleChecker::CheckHittingLeftForwardNeighbour(const Position& cur_pos) const
{

	const auto& [cur_x, cur_y] = cur_pos;
	const Position neigh_pos(std::make_pair(cur_x - NeighbourConst, cur_y + NeighbourConst));
	if (CheckStateNeighbour(cur_pos, neigh_pos)) {
		return false;
	}
	const Position neigh_neigh_pos(std::make_pair(cur_x - 2 * NeighbourConst, cur_y + 2 * NeighbourConst));
	return  CheckNeighbourNeighbour(neigh_neigh_pos);
}

bool MotionSimpleChecker::CheckHittingLeftBackNeighbour(const Position& cur_pos) const
{

	const auto& [cur_x, cur_y] = cur_pos;
	const Position neigh_pos(std::make_pair(cur_x - NeighbourConst, cur_y - NeighbourConst));
	if (CheckStateNeighbour(cur_pos, neigh_pos)) {
		return false;
	}
	const Position neigh_neigh_pos(std::make_pair(cur_x - 2 * NeighbourConst, cur_y - 2 * NeighbourConst));
	return  CheckNeighbourNeighbour(neigh_neigh_pos);

}
bool MotionSimpleChecker::CheckStateNeighbour(const Position& cur_pos, const Position& neighbour_pos) const
{
	return CheckBoarders(neighbour_pos) 
		|| mCells[neighbour_pos].GetState() == mCells[cur_pos].GetState() || mCells[neighbour_pos].GetState() == Cell::State::BLANK;
}

bool MotionSimpleChecker::CheckNeighbourNeighbour(const Position& neighbour_neighbour_pos) const
{
	if (mCells[neighbour_neighbour_pos].GetState() == Cell::State::BLANK) return true;
	return false;
}