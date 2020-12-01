#include "Game.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "GUI.h"
using namespace sf;
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(){
	Game game;
	game.PlayGame();
	Board a;
	/*a.HighlightCells(std::make_pair(5,2));
	a.MoveChecker(std::make_pair(6,3));
	a.HighlightCells(std::make_pair(6,5));
	a.MoveChecker(std::make_pair(7,4));
	a.HighlightCells(std::make_pair(1,2));
	a.MoveChecker(std::make_pair(0,3));
	a.HighlightCells(std::make_pair(7,4));
	a.MoveChecker(std::make_pair(5, 2));*/
	return 0;
}
