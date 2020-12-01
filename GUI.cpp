#include <SFML/Graphics.hpp>
#include "GUI.h"
using namespace sf;
namespace 
{
	const size_t BoardSize = 7;
}
void GUI::DrawChecker(Cell& cur_cell, sf::RenderWindow& _window)
{

	switch (cur_cell.GetState()) {
	case Cell::State::WHITE:

		cur_cell.SetColorChecker(Color(180, 120, 55));
		break;
	case Cell::State::BLACK:
		cur_cell.SetColorChecker(Color(61, 25, 7));
		break;
	case Cell::State::BLANK:
		return;

	}
	_window.draw(cur_cell.GetChecker());
}

void GUI::DrawBoarderBoard(sf::RenderWindow& _window)
{
	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");
	Text* t[16];
	for (int i = 0; i < 16; i++) {
		t[i] = new Text("", font, 35);

	}
	t[0]->setString(L"1");
	t[1]->setString(L"2");
	t[2]->setString(L"3");
	t[3]->setString(L"4");
	t[4]->setString(L"5");
	t[5]->setString(L"6");
	t[6]->setString(L"7");
	t[7]->setString(L"8");
	t[8]->setString(L"À");
	t[9]->setString(L"B");
	t[10]->setString(L"C");
	t[11]->setString(L"D");
	t[12]->setString(L"E");
	t[13]->setString(L"F");
	t[14]->setString(L"G");
	t[15]->setString(L"H");
	for (int i = 0; i < 8; i++) {
		t[i]->setFillColor(Color::Black);
		t[i]->setPosition(15, i * 50 + 55);
		_window.draw(*t[i]);
		t[i]->setPosition(465, i * 50 + 55);
		_window.draw(*t[i]);
	}
	for (int i = 8; i < 16; i++) {
		t[i]->setFillColor(Color::Black);
		t[i]->setPosition((i - 8) * 50 + 60, 5);
		_window.draw(*t[i]);
		t[i]->setPosition((i - 8) * 50 + 60, 455);
		_window.draw(*t[i]);
	}
}

void GUI::DrawCells(std::map<Position, Cell>& Cells, sf::RenderWindow& _window)
{
	for (int i = 0; i <= BoardSize; ++i) {
		for (int j = 0; j <= BoardSize; ++j) {
			Position cur_pos(i, j);
			Cell& cur_cell = Cells.at(cur_pos);
			cur_cell.SetPositionSquare((i + 1) * 50.0, (j + 1) * 50);
			if ((i + j) % 2 == 1) cur_cell.SetColorSquare(Color(255, 178, 115));
			else cur_cell.SetColorSquare(Color(101, 61, 16));
			if (cur_cell.GetBorderIllumination()) {
				cur_cell.SetColorSquare(Color(150, 120, 90));
			}
			_window.draw(cur_cell.GetSquare());
		}
	}
}

void GUI::DrawQueen(sf::RenderWindow& _window, const Position& cur_pos)
{
	const auto& [x, y] = cur_pos;
	sf::Texture TextureQueen;
	sf::Sprite SpriteQueen;
	TextureQueen.loadFromFile("Images//Queen.png");
	SpriteQueen.setTexture(TextureQueen);
	SpriteQueen.setTextureRect(sf::IntRect(0, 0, 25, 25));
	SpriteQueen.setPosition((x+1)*50 + 6, (y+1)*50 + 6);
	_window.draw(SpriteQueen);
}

void GUI::DrawWinner(sf::RenderWindow& _window, const std::string& winner_name)
{
	RectangleShape back = RectangleShape(Vector2f(350, 150));
	back.setFillColor(Color(245, 210, 175));
	back.setPosition(75, 175);
	Font font;
	font.loadFromFile("Font//bahnschrift.ttf");
	Text t = Text("", font, 81);
	t.setString(winner_name);
	t.setFillColor(Color::Black);
	t.setPosition(78, 190);
	_window.draw(back);
	_window.draw(t);
}
void GUI::DrawBoard(std::map<Position, Cell>& Cells, RenderWindow& _window)
{
	if (Cells.empty()) return;
	{
		DrawCells(Cells, _window);
		DrawBoarderBoard(_window);
	}
}
void GUI::DrawCheckers(std::map<Position, Cell>& Cells, sf::RenderWindow& _window)
{
	if (Cells.empty()) return;
	for (int i = 0; i <= BoardSize; ++i) {
		for (int j = 0; j <= BoardSize; ++j) {
			Position cur_pos(i, j);
			Cell& cur_cell = Cells.at(cur_pos);
			cur_cell.SetPositionChecker((i + 1) * 50.0, (j + 1) * 50);
			DrawChecker(cur_cell, _window);
			if (cur_cell.GetQueen())
			{
				DrawQueen(_window, cur_pos);
			}
		}
	}
}
