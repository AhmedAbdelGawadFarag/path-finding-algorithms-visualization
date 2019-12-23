#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Menu.h"
#include "Maze.h"
#include <string>
#include <filesystem>


using namespace std;
using namespace sf;


int main() {

	RenderWindow window(VideoMode(1366, 768), "Maze Runner!", Style::Default);	
	//window.setFramerateLimit(10);
	
	Maze maze(&window, 1.5, sf::Vector2i(45, 30), sf::Color::White , sf::Color::Black);
	Menu menu(&window, &maze);

    sf::Event event;
	menu.open();
	while (window.isOpen())
	{	
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				menu.eventHandler(event);
				break;

			case sf::Event::Closed:
				window.close();
				break;

			}
			if (Mouse::isButtonPressed(Mouse::Button::Left)) 
				maze.onButtonClick(Mouse::getPosition(window));
			
		}
		window.clear();
		if (menu.isOpen())
			menu.draw();
		else if (!maze.isFile())
		{
			maze.update();
			maze.draw();
		}
		else
		{
			maze.draw();
		}
			
		window.display();
	}

	return 0;
}