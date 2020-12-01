#include "MotionQueen.h"
namespace
{
	const size_t BoardSize = 7;

	bool CheckQueen(const Position& checker_pos)
	{
		const auto& [x, y] = checker_pos;
		return  y == 0 || y == BoardSize;
	}
	bool CheckLeftBoarder(const Position& checker_pos)
	{
		return checker_pos.first == 0;
	}
	bool CheckRightBoarder(const Position& checker_pos)
	{
		return checker_pos.first == BoardSize;
	}
	bool CheckBoarders(const Position& checker_pos)
	{
		return CheckLeftBoarder(checker_pos) || CheckRightBoarder(checker_pos);
	}
}
MotionQueen::MotionQueen(std::map<Position, Cell>& _mCells, std::vector<Position>& _BorderIlluminationCells):MotionSimpleChecker(_mCells,_BorderIlluminationCells),
	mCells(_mCells),
	BorderIlluminationCells(_BorderIlluminationCells)
{
}
std::vector<Cell::Direction> MotionQueen::CheckHittingQueen(const Position& new_pos)
{
	if (CheckLeftBoarder(new_pos))
	{
		return CheckHittingQueenRightNeighbours(new_pos);
	} if (CheckRightBoarder(new_pos))
	{
		return CheckHittingQueenLeftNeighbours(new_pos);
	}
	std::vector<Cell::Direction> result = CheckHittingQueenRightNeighbours(new_pos);
	std::vector<Cell::Direction> temp = CheckHittingQueenLeftNeighbours(new_pos);
	result.insert(result.end(), temp.begin(), temp.end());
	return result;
}

std::vector<Cell::Direction> MotionQueen::CheckHittingQueenRightNeighbours(const Position& new_pos)
{
	std::vector<Cell::Direction> result;
	if (CheckHittingQueenRightBackNeighbour(new_pos))
		result.push_back(Cell::Direction::Back_Right);
	if (CheckHittingQueenRightForwardNeighbour(new_pos))
		result.push_back(Cell::Direction::Forward_Right);
	return  result;
}

std::vector<Cell::Direction> MotionQueen::CheckHittingQueenLeftNeighbours(const Position& new_pos)
{
	std::vector<Cell::Direction> result;
	if (CheckHittingQueenLeftBackNeighbour(new_pos))
		result.push_back(Cell::Direction::Back_Left);
	if (CheckHittingQueenLeftForwardNeighbour(new_pos))
		result.push_back(Cell::Direction::Forward_Left);
	return  result;
}

bool MotionQueen::CheckHittingQueenRightForwardNeighbour(const Position& cur_pos)
{
	for (Position temp_pos = cur_pos; CheckBoarders(temp_pos) || CheckQueen(temp_pos); temp_pos = Position(--temp_pos.first, ++temp_pos.second))
	{
		if (CheckHittingRightForwardNeighbour(temp_pos)) {
			return true;
		}
	}
	return false;
}

bool MotionQueen::CheckHittingQueenRightBackNeighbour(const Position& cur_pos)
{
	for (Position temp_pos = cur_pos; CheckBoarders(temp_pos) || CheckQueen(temp_pos); temp_pos = Position(--temp_pos.first, --temp_pos.second))
	{
		if (CheckHittingRightBackNeighbour(temp_pos)) {
			return true;
		}
	}
	return false;
}

bool MotionQueen::CheckHittingQueenLeftForwardNeighbour(const Position& cur_pos)
{
	for (Position temp_pos = cur_pos; CheckBoarders(temp_pos) || CheckQueen(temp_pos); temp_pos = Position(++temp_pos.first, ++temp_pos.second))
	{
		if (CheckHittingLeftForwardNeighbour(temp_pos)) {
			return true;
		}
	}
	return false;
}

bool MotionQueen::CheckHittingQueenLeftBackNeighbour(const Position& cur_pos)
{
	for (Position temp_pos = cur_pos; CheckBoarders(temp_pos) || CheckQueen(temp_pos); temp_pos = Position(++temp_pos.first, --temp_pos.second))
	{
		if (CheckHittingLeftBackNeighbour(temp_pos)) {
			return true;
		}
	}
	return false;
}
MotionSimpleChecker::MoveResult MotionQueen::MoveQueenChecker(const Position& new_pos)
{
	if (BorderIlluminationCells.size() == size_t(HighlightCell::BorderIlluminationCellsStruct::min_size)) return MotionSimpleChecker::MoveResult::Prohibited;
	Cell::Direction queen_dir = FindQueenDirection(new_pos);
	const Position cur_pos = BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)];
	switch (queen_dir)
	{
	case(Cell::Direction::Forward_Right):
		if (!MoveQueenRightForward(cur_pos, new_pos)) return MotionSimpleChecker::MoveResult::Prohibited;
		break;
	case(Cell::Direction::Back_Right):
		if (!MoveQueenRightBack(cur_pos, new_pos)) return MotionSimpleChecker::MoveResult::Prohibited;
		break;
	case(Cell::Direction::Back_Left):
		if (!MoveQueenLeftBack(cur_pos, new_pos)) return MotionSimpleChecker::MoveResult::Prohibited;
		break;
	case(Cell::Direction::Forward_Left):
		if (!MoveQueenLeftForward(cur_pos, new_pos)) return MotionSimpleChecker::MoveResult::Prohibited;
		break;
	}
	const std::vector<Cell::Direction>  direction = CheckHittingQueen(new_pos);
	if (direction.empty()) {
		return MotionSimpleChecker::MoveResult::Successful;
	}
	mCells[new_pos].SetHitting(direction);
	return  MotionSimpleChecker::MoveResult::ContinueHitting;
}
Cell::Direction MotionQueen::FindQueenDirection(const Position& new_pos)
{
	const auto& [cur_x, cur_y] = BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)];
	const auto& [new_x, new_y] = new_pos;
	if (new_x > cur_x&& new_y < cur_y) return Cell::Direction::Back_Right;
	if (new_x < cur_x && new_y < cur_y) return Cell::Direction::Back_Left;
	if (new_x > cur_x&& new_y > cur_y) return Cell::Direction::Forward_Right;
	if (new_x < cur_x && new_y > cur_y) return Cell::Direction::Forward_Left;
}
MotionQueen::QueenMove MotionQueen::MoveOneCellQueen(const Position& cur_pos, const Position& next_pos, const Position& last_pos)
{
	if (mCells[next_pos].GetState() == Cell::State::BLANK)
	{
		MoveSimpleChecker(next_pos);
		BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)] = next_pos;
		return QueenMove::SIMPLE_MOVE;
	}
	if (mCells[cur_pos].GetState() != mCells[next_pos].GetState())
	{
		const Position next_next_pos(next_pos.first * 2 - cur_pos.first, next_pos.second * 2 - cur_pos.second);
		if (next_pos == last_pos || mCells[next_next_pos].GetState() != Cell::State::BLANK)
		{
			return QueenMove::PROHIBITED;
		}
		HitChecker(next_next_pos);
		BorderIlluminationCells[size_t(HighlightCell::BorderIlluminationCellsStruct::Checker)] = next_next_pos;
		return QueenMove::HIT_MOVE;
	}
	return QueenMove::PROHIBITED;
}
bool MotionQueen::MoveQueenLeftForward(const Position& cur_pos, const Position& new_pos)
{
	for (Position temp_pos = cur_pos; temp_pos != new_pos; temp_pos = Position(--temp_pos.first, ++temp_pos.second))
	{
		const Position next_pos(temp_pos.first - 1, temp_pos.second + 1);
		const QueenMove cur_motion = MoveOneCellQueen(temp_pos, next_pos, new_pos);
		if (cur_motion == QueenMove::PROHIBITED)
			return false;
		if (cur_motion == QueenMove::HIT_MOVE)
		{
			temp_pos = next_pos;
		}
	}
	return true;
}
bool MotionQueen::MoveQueenRightForward(const Position& cur_pos, const Position& new_pos)
{
	for (Position temp_pos = cur_pos; temp_pos != new_pos; temp_pos = Position(++temp_pos.first, ++temp_pos.second))
	{
		const Position next_pos(temp_pos.first + 1, temp_pos.second + 1);
		const QueenMove cur_motion = MoveOneCellQueen(temp_pos, next_pos, new_pos);
		if (cur_motion == QueenMove::PROHIBITED)
			return false;
		if (cur_motion == QueenMove::HIT_MOVE)
		{
			temp_pos = next_pos;
		}

	}
	return true;
}
bool MotionQueen::MoveQueenLeftBack(const Position& cur_pos, const Position& new_pos)
{
	for (Position temp_pos = cur_pos; temp_pos != new_pos; temp_pos = Position(--temp_pos.first, --temp_pos.second))
	{
		const Position next_pos(temp_pos.first - 1, temp_pos.second - 1);
		const QueenMove cur_motion = MoveOneCellQueen(temp_pos, next_pos, new_pos);
		if (cur_motion == QueenMove::PROHIBITED)
			return false;
		if (cur_motion == QueenMove::HIT_MOVE)
		{
			temp_pos = next_pos;
		}
	}
	return true;
}
bool MotionQueen::MoveQueenRightBack(const Position& cur_pos, const Position& new_pos)
{
	for (Position temp_pos = cur_pos; temp_pos != new_pos; temp_pos = Position(++temp_pos.first, --temp_pos.second))
	{
		const Position next_pos(temp_pos.first + 1, temp_pos.second - 1);
		const QueenMove cur_motion = MoveOneCellQueen(temp_pos, next_pos, new_pos);
		if (cur_motion == QueenMove::PROHIBITED)
			return false;
		if (cur_motion == QueenMove::HIT_MOVE)
		{
			temp_pos = next_pos;
		}
	}
	return true;
}