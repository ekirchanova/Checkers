#include "Score.h"

namespace 
{
	const size_t BoardSize = 7;
}
void Score::CalculateCount()
{
	count_black = 0;
	count_white = 0;
	for (size_t i = 0; i <= BoardSize; ++i)
	{
		for (size_t j = 0; j <= BoardSize; ++j)
		{
			const Position cur_pos(i, j);
			auto& cur_cell = mCells[cur_pos];
			if(cur_cell.GetState()==Cell::State::BLACK)
			{
				++count_black;
				continue;
			}
			if (cur_cell.GetState() == Cell::State::WHITE)
			{
				++count_white;
				continue;
			}
		}
	}
}

Score::Score(std::map<Position, Cell>& _mCells):mCells(_mCells),count_white(0),count_black(0)
{
}

bool Score::EndGame() 
{
	CalculateCount();
	return count_black==0||count_white==0;
}

Cell::State Score::FindWinner() const
{
	return count_black==0?Cell::State::WHITE: Cell::State::BLACK;
}

