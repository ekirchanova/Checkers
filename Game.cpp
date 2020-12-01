#include "Game.h"
#include "GUI.h"
#include "Board.h"
using  namespace sf;

namespace 
{
	const size_t BoardSize = 7;
}
Position Game::CentreOnSquare()
{
	for (int i = 0; i <=BoardSize; i++) {
		for (int j = 0; j <= BoardSize; j++) {
			if (mouse_position.x <= i * 50 + 100 && mouse_position.x <= (i + 1) * 50 + 100 &&
				mouse_position.y <= j * 50 + 100 && mouse_position.y <= (j + 1) * 50 + 100) {
				return std::make_pair(i,j);
			}
		}
	}
}

void Game::SetMousePosition(sf::RenderWindow& _window)
{
	mouse_position= Mouse::getPosition(_window);
}

Game::Game():mBoard(Board()),score(Score(mBoard.GetCells()))
{
}

void Game::MakeMove(sf::RenderWindow& _window, sf::Event _event)
{
	if (_event.type == sf::Event::MouseButtonPressed) {
		if (_event.key.code == Mouse::Left) {
			SetMousePosition(_window);
			const Position checker_pos = CentreOnSquare();
			mBoard.HighlightCells(checker_pos);
		}
		else if (_event.key.code == Mouse::Right) {
			SetMousePosition(_window);
			const Position checker_pos = CentreOnSquare();
			mBoard.MoveChecker(checker_pos);
		}
	}
	score.EndGame();
}

void Game::DrawAllBoard(sf::RenderWindow& _window)
{
	GUI::DrawBoard(mBoard.GetCells(), _window);
	GUI::DrawCheckers(mBoard.GetCells(), _window);
}
void Game::RestartGame(sf::RenderWindow& _window, Event _event)
{
	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");
	Text t[5];
	t[0] = Text("", font, 35);
	t[0].setPosition(55, 90);
	t[0].setStyle(Text::Bold);
	t[0].setString(L"Хотите еще сыграть?");
	t[1] = Text("", font, 14);
	t[1].setPosition(82, 290);
	t[1].setString(L"нажмите любую клавишу чтобы продолжить");
	for (int i = 0; i < 2; i++) {
		t[i].setFillColor(Color::Black);
	}
	while (1) {
		_window.clear(Color(245, 210, 175));
		for (int i = 0; i < 2; i++) {
			_window.draw(t[i]);
		}
		_window.display();
		while (_window.pollEvent(_event)) {
			if (_event.type == Event::Closed)
				_window.close();
			if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::KeyPressed) {
				mBoard.ResetMap();
				return;
			}
		}
	}
}
void Game::PlayGame()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Checker");
	bool start = 1;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			MakeMove(window, event);

		}

		if (start) {
			StartGame(window, event);
			start = false;
		}
		WriteScore(window, event);
		DrawAllBoard(window);
		window.display();
		window.clear(Color(245, 210, 175));
	}
}
void Game::StartGame(RenderWindow& _window, Event _event) {
	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");
	Text t[5];
	t[0] = Text("", font, 100);
	t[0].setPosition(82, 150);
	t[0].setStyle(Text::Bold);
	t[0].setString(L"Шашки");
	t[1] = Text("", font, 25);
	t[1].setPosition(82, 260);
	t[1].setString(L"левый щелчёк - выбор шашки");
	t[2] = Text("", font, 25);
	t[2].setPosition(82, 260 + 25);
	t[2].setString(L"правый щелчёк - сделать ход");
	t[3] = Text("", font, 14);
	t[3].setFillColor(Color::Black);
	t[3].setPosition(225, 484);
	t[3].setString(L"нажмите любую клавишу чтобы продолжить");
	for (int i = 0; i < 5; i++) {
		t[i].setFillColor(Color::Black);
	}
	while (1) {
		_window.clear(Color(245, 210, 175));
		for (int i = 0; i < 5; i++) {
			_window.draw(t[i]);
		}
		_window.display();
		while (_window.pollEvent(_event)) {
			if (_event.type == Event::Closed)
				_window.close();
			if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::KeyPressed) {
				return;
			}
		}
	}
}
bool Game::WriteScore(RenderWindow& _window, Event _event) {
	if (!score.EndGame()) return false;
	while (1) {

		_window.clear(Color(245, 210, 175));
		while (_window.pollEvent(_event)) {
			if (_event.type == Event::Closed)
				_window.close();
			if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::KeyPressed) {
				RestartGame(_window,_event);
				return true;
			}
		}
		switch (score.FindWinner()) {
		case Cell::State::BLACK:
		{
			GUI::DrawWinner(_window, "Black win");
		}
		case Cell::State::WHITE:
		{
			GUI::DrawWinner(_window, "White win");
		}
		}
		_window.display();
		
	}
}