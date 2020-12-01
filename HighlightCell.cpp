#include "HighlightCell.h"
namespace
{

	const size_t NeighbourConst = 1;
	const size_t BoardSize = 7;
	bool CheckExitFromBoarders(const Position& checker_pos)
	{
		const auto& [ch_x, ch_y] = checker_pos;
		return ch_x<0 || ch_x>BoardSize || ch_y<0 || ch_y>BoardSize;
	}
}

HighlightCell::HighlightCell(std::map<Position, Cell>& _mCells,Cell::State _mState):mCells(_mCells),mState(_mState)
{
}

void HighlightCell::SetCells(std::map<Position, Cell>& _mCells)
{
	mCells = _mCells;
}
void HighlightCell::SetState(Cell::State m_state)
{
	mState = m_state;
}
std::vector<Position>& HighlightCell::GetBorderIlluminationCells()
{
	return BorderIlluminationCells;
}
void HighlightCell::HighlightCells(const Position& checker_pos)
{
	if (!BorderIlluminationCells.empty())
	{
		ClearBorderIlluminationCells();
	}
	Cell& cur_checker = mCells[checker_pos];
	if (cur_checker.GetState() != mState) return;
	cur_checker.SetBorderIllumination(true);
	BorderIlluminationCells.push_back(checker_pos);
	if (cur_checker.GetQueen())
	{
		HighlightQueen(checker_pos);
		return;
	}
	if (!cur_checker.GetHitting().empty())
	{
		HighlightCellCheckerHitting(checker_pos);
		return;
	}
	switch (cur_checker.GetState()) {
	case Cell::State::BLACK:
		HighlightCellBlackChecker(checker_pos);
		break;
	case Cell::State::WHITE:
	
		HighlightCellWhiteChecker(checker_pos);
		break;
	}
}
void HighlightCell::ClearBorderIlluminationCells()
{
	for (const auto& it : BorderIlluminationCells)
	{
		mCells[it].SetBorderIllumination(false);
	}
	BorderIlluminationCells.clear();
}
void HighlightCell::HighlightCellBlackChecker(const Position& checker_pos)
{
	const auto& [ch_x, ch_y] = checker_pos;
	AddPossibleMoves(std::make_pair(ch_x - NeighbourConst, ch_y - NeighbourConst));
	AddPossibleMoves(std::make_pair(ch_x + NeighbourConst, ch_y - NeighbourConst));
}
void HighlightCell::HighlightCellWhiteChecker(const Position& checker_pos)
{
	const auto& [ch_x, ch_y] = checker_pos;
	AddPossibleMoves(std::make_pair(ch_x - NeighbourConst, ch_y + NeighbourConst));
	AddPossibleMoves(std::make_pair(ch_x + NeighbourConst, ch_y + NeighbourConst));
}
void HighlightCell::HighlightCellCheckerHitting(const Position& checker_pos)
{
	const Cell cur_checker = mCells[checker_pos];

	auto& [ch_x, ch_y] = checker_pos;
	std::vector<Cell::Direction> hitting_directions = cur_checker.GetHitting();
	for (auto& h_d : hitting_directions) {
		Position new_pos;
		auto& [x, y] = new_pos;
		switch (h_d)
		{
		case Cell::Direction::Back_Left:
			x = ch_x - NeighbourConst * 2;
			y = ch_y - NeighbourConst * 2;
			break;
		case Cell::Direction::Forward_Left:
			x = ch_x - NeighbourConst * 2;
			y = ch_y + NeighbourConst * 2;
			break;
		case Cell::Direction::Back_Right:
			x = ch_x + NeighbourConst * 2;
			y = ch_y - NeighbourConst * 2;
			break;
		case Cell::Direction::Forward_Right:
			x = ch_x + NeighbourConst * 2;
			y = ch_y + NeighbourConst * 2;
			break;
		}
		mCells[new_pos].SetBorderIllumination(true);
		BorderIlluminationCells.push_back(new_pos);
	}
}

void HighlightCell::HighlightQueenForwardLeft(const Position& checker_pos)
{
	Position next_pos_BL(checker_pos.first - 1, checker_pos.second + 1);
	for (Position temp_pos = next_pos_BL;! CheckExitFromBoarders(temp_pos); temp_pos = Position(--temp_pos.first, ++temp_pos.second))
	{
		if (mCells[temp_pos].GetState() == mState) break;
		if (mCells[temp_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(temp_pos);
			continue;
		}
		const Position neigh_neigh_pos(std::make_pair(temp_pos.first - 2 * NeighbourConst, temp_pos.second + 2 * NeighbourConst));
		if (mCells[neigh_neigh_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(neigh_neigh_pos);
			continue;
		}
		break;
	}
}
void HighlightCell::HighlightQueenForwardRight(const Position& checker_pos)
{
	Position next_pos_BL(checker_pos.first + 1, checker_pos.second + 1);
	for (Position temp_pos = next_pos_BL; !CheckExitFromBoarders(temp_pos); temp_pos = Position(++temp_pos.first, ++temp_pos.second))
	{
		if (mCells[temp_pos].GetState() == mState) break;
		if (mCells[temp_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(temp_pos);
			continue;
		}
		const Position neigh_neigh_pos(std::make_pair(temp_pos.first + 2 * NeighbourConst, temp_pos.second + 2 * NeighbourConst));
		if (mCells[neigh_neigh_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(neigh_neigh_pos);
			continue;
		}
		break;
	}
}

void HighlightCell::HighlightQueenBackLeft(const Position& checker_pos)
{
	Position next_pos_BL(checker_pos.first -1, checker_pos.second - 1);
	for (Position temp_pos = next_pos_BL;! CheckExitFromBoarders(temp_pos); temp_pos = Position(--temp_pos.first, --temp_pos.second))
	{
		if (mCells[temp_pos].GetState() == mState) break;
		if (mCells[temp_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(temp_pos);
			continue;
		}
		const Position neigh_neigh_pos(std::make_pair(temp_pos.first - 2 * NeighbourConst, temp_pos.second - 2 * NeighbourConst));
		if (mCells[neigh_neigh_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(neigh_neigh_pos);
			continue;
		}
		break;
	}
}
void HighlightCell::HighlightQueenBackRight(const Position& checker_pos)
{
	Position next_pos_BL(checker_pos.first + 1, checker_pos.second - 1);
	for (Position temp_pos = next_pos_BL; !CheckExitFromBoarders(temp_pos); temp_pos = Position(++temp_pos.first, --temp_pos.second))
	{
		if (mCells[temp_pos].GetState() == mState) break;
		if (mCells[temp_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(temp_pos);
			continue;
		}
		const Position neigh_neigh_pos(std::make_pair(temp_pos.first + 2 * NeighbourConst, temp_pos.second - 2 * NeighbourConst));
		if (mCells[neigh_neigh_pos].GetState() == Cell::State::BLANK)
		{
			AddPossibleMoves(neigh_neigh_pos);
			continue;
		}
		break;
	}
}
void HighlightCell::HighlightQueen(const Position& checker_pos)
{
	HighlightQueenBackLeft(checker_pos);
	HighlightQueenBackRight(checker_pos);
	HighlightQueenForwardLeft(checker_pos);
	HighlightQueenForwardRight(checker_pos);
}
void HighlightCell::AddPossibleMoves(const Position& new_pos)
{
	if (mCells[new_pos].GetState() != Cell::State::BLANK || !CheckPossibleMoves(new_pos))return;
	mCells[new_pos].SetBorderIllumination(true);
	BorderIlluminationCells.push_back(new_pos);
}
bool HighlightCell::CheckPossibleMoves(const Position& cur_pos)
{
	const auto& [ch_x, ch_y] = cur_pos;
	return ch_x >= 0 && ch_x <= BoardSize && ch_y >= 0 && ch_y <= BoardSize;
}