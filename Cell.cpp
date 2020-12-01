#include "Cell.h"
namespace
{
	const float CONST_TEXTURE = 6;
}
Cell::Cell() :CurState(State::BLANK), Queen(false), BorderIllumination(false),
Square(sf::RectangleShape(sf::Vector2f(50, 50))), Checker(sf::CircleShape(18))
{
	Checker.setOutlineThickness(3);
	Checker.setOutlineColor(sf::Color(0, 0, 0));
}

Cell::State Cell::GetState() const
{
	return CurState;
}

void Cell::SetState(State nState)
{
	CurState = nState;
}

bool Cell::GetBorderIllumination() const
{
	return BorderIllumination;
}

void Cell::SetBorderIllumination(bool nState)
{
	BorderIllumination = nState;
}

bool Cell::GetQueen() const
{
	return Queen;
}

void Cell::SetQueen(bool nState)
{
	Queen = nState;
}


std::vector<Cell::Direction> Cell::GetHitting() const
{
	return Directions;
}

void Cell::SetHitting(std::vector<Cell::Direction> nHitting)
{
	Directions = nHitting;
}

sf::RectangleShape& Cell::GetSquare() {
	return Square;
}
void Cell::SetColorSquare(sf::Color _color) {
	Square.setFillColor(_color);
}
void Cell::SetPositionSquare(float _x, float _y) {
	Square.setPosition(_x, _y);
}
void Cell::SetColorChecker(sf::Color _color) {
	Checker.setFillColor(_color);
}
void Cell::SetPositionChecker(float _x, float _y)
{
	Checker.setPosition(_x, _y);
}

sf::CircleShape& Cell::GetChecker()
{
	return Checker;
}


