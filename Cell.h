#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Cell final
{
public:
	enum class State { BLACK, WHITE, BLANK };

	enum class Direction{Forward_Left,Forward_Right,Back_Left,Back_Right  };
	
private:
	State CurState;
	bool Queen;
	bool BorderIllumination;
	std::vector<Cell::Direction> Directions;
	
	sf::RectangleShape Square;
	sf::CircleShape Checker;
public:
	Cell();
	State GetState() const ;
	void SetState(State nState);

	bool GetBorderIllumination() const;
	void SetBorderIllumination(bool nState);
	
	bool GetQueen() const;
	void SetQueen(bool nState);
	
	std::vector<Direction> GetHitting()const;
	void SetHitting(std::vector<Direction>);

	sf::RectangleShape& GetSquare();
	void SetColorSquare(sf::Color _color);
	void SetPositionSquare(float _x, float _y);
	
	void SetColorChecker(sf::Color _color);
	void SetPositionChecker(float _x, float _y);
	
	sf::CircleShape& GetChecker();
};


