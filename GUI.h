#pragma once
#include "Board.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class GUI final
{
	static void DrawChecker(Cell& cur_cell, sf::RenderWindow& _window);
	static void DrawBoarderBoard(sf::RenderWindow& _window);
	static void DrawCells(std::map<Position, Cell>& Cells, sf::RenderWindow& _window);
	static void DrawQueen(sf::RenderWindow& _window, const Position& cur_pos);
public:
	static void DrawWinner(sf::RenderWindow& _window, const std::string& winner_name);
	static void DrawBoard(std::map<Position, Cell>& Cells, sf::RenderWindow& _window);
	static void DrawCheckers(std::map<Position, Cell>& Cells, sf::RenderWindow& _window);
};
