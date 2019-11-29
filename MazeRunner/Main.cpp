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
int main() {

	RenderWindow window(VideoMode(1366, 768), "Maze Runner!", Style::Default);

	ReadMaze readmaze("maze1.txt", window.getSize(), 0.5, Color::Red, Color::Blue);
	

	window.setFramerateLimit(60);
	
	Maze maze(sf::Vector2f(window.getSize().x , window.getSize().y ), 1.5, sf::Vector2i(45, 30), sf::Color::Blue , sf::Color::Black);
	Menu menu(&window, &maze);

	sf::Event event;
	menu.open();
	while (window.isOpen())
	{	
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				menu.eventHandler(event);
				break;

			case sf::Event::Closed:
				window.close();
				break;
			}

		}
		window.clear();
		if (menu.isOpen())
			menu.draw();
		else
		{
			maze.update();
			maze.draw(&window);
		}
			
		window.display();
	}

	return 0;
}