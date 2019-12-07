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

	int cnt = 0;

	RenderWindow window(VideoMode(1366, 768), "Maze Runner!", Style::Default);	

	window.setFramerateLimit(30);
	
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
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				//cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;;
				if (cnt==0) {
				maze.setSart(maze.onButtonClick(Mouse::getPosition(window),Color::Blue));

				}
				else if (cnt == 1) {
					maze.SetEnd(maze.onButtonClick(Mouse::getPosition(window), Color::Cyan));
				}
				//cout << cnt << endl;
				cnt++;
				
			}

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