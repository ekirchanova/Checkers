#pragma once
#include "HighlightCell.h"

class Score
{
	std::map<Position, Cell>& mCells;
	size_t count_white;
	size_t count_black;
	void CalculateCount();
public:
	Score(std::map<Position, Cell>& _mCells);
	bool EndGame();
	Cell::State FindWinner()const;
};

