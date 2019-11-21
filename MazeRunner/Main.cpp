#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Menu.h"
#include "Maze.h"
using namespace std;


int main() {

	// Create Window
	RenderWindow window(VideoMode(1366, 768), "Maze Runner!",Style::Default);
	window.setFramerateLimit(80);
	Menu menu(window.getSize().x, window.getSize().y);

	Maze maze(sf::Vector2f(window.getSize().x , window.getSize().y ), 1.5, sf::Vector2i(45, 30), sf::Color::White , sf::Color::Black);
	
	sf::Event event;
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:

					switch (event.key.code)
					{
					case sf::Keyboard::Key::Escape:
						if (menu.isOpen())
							menu.close();
						else
							menu.open();
							break;
					case sf::Keyboard::Key::Up:
						menu.moveUp();
						break;

					case sf::Keyboard::Key::Down:
						menu.moveDown();
						break;

					}
				
				break;
			
			case sf::Event::Closed :
				window.close();
				break;
			}
			
		}

		window.clear();
		if (menu.isOpen())
			menu.draw(window);
		else
		{
			maze.update();
			maze.draw(&window);
		}
		
		window.display();
	}

	return 0;
}