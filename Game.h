#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Score.h"
#include "Board.h"

class Game final
{
	Board mBoard;
	Score score;
	sf::Vector2i mouse_position;

	Position CentreOnSquare();
	void SetMousePosition(sf::RenderWindow& _window);

	bool WriteScore(sf::RenderWindow& _window, sf::Event _event);
	void MakeMove(sf::RenderWindow& _window, sf::Event _event);
	static void StartGame(sf::RenderWindow& _window, sf::Event _event);
	void DrawAllBoard(sf::RenderWindow& _window);
	void RestartGame(sf::RenderWindow& _window, sf::Event _event);
public:
	Game();
	void PlayGame();
};

