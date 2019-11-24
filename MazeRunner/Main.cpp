#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Menu.h"
#include "Maze.h"
#include"ReadMaze.h"
#include <string>
using namespace std;
using namespace sf;
bool MenuFile = true, MazeGenerator = false, MazeFile = false;

void CheckEvent(RenderWindow *window,Menu *menu) {
	Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:

			switch (event.key.code)
			{
			case sf::Keyboard::Key::Escape:
				MazeGenerator = false;
				MazeFile = false;
				MenuFile = true;
				break;
			case sf::Keyboard::Key::Up:
				if(MenuFile)
				menu->moveUp();
				break;

			case sf::Keyboard::Key::Down:
				if(MenuFile)
				menu->moveDown();
				break;
			case Keyboard::Key::Enter:
				if (MenuFile) {
					if (menu->checked() == 0) {
						MazeGenerator = true;
						MazeFile = false;
						MenuFile = false;
					}
					else if (menu->checked() == 1) {
							MazeGenerator = false;
							MazeFile = true;
							MenuFile = false;
						}
					

				}

				break;

			}

		break;

	case sf::Event::Closed :
		window->close();
		break;
	}

}

}

int main() {

	RenderWindow window(VideoMode(1366, 768), "Maze Runner!", Style::Default);

	ReadMaze readmaze("maze2.txt", window.getSize(), 0.5, Color::Red, Color::Blue);
	
	

	window.setFramerateLimit(60);
	Menu menu(window.getSize().x, window.getSize().y);

	Maze maze(sf::Vector2f(window.getSize().x , window.getSize().y ), 0.5, sf::Vector2i(45, 30), sf::Color::Red , sf::Color::Black);

	sf::Event event;
	menu.open();
	while (window.isOpen())
	{	
		CheckEvent(&window,&menu);

		window.clear();

		if (MenuFile)
			menu.draw(window);
		else if(MazeGenerator)
		{
			maze.update();
			maze.draw(&window);
		}
		else if (MazeFile) {
			readmaze.update();
			readmaze.draw(&window);
		}
		
		window.display();
	}

	return 0;
}