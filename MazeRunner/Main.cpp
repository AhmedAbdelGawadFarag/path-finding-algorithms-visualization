#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Maze.h"
using namespace std;
using namespace sf;

int main() {

	// Create Window
	RenderWindow window(VideoMode(1366, 768), "Maze Runner!",Style::Default);
	window.setFramerateLimit(80);
	
	Maze maze(Vector2f(window.getSize().x , window.getSize().y ), 0.50, Vector2i(45, 30), Color::White , Color::Black);
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		maze.update();
		maze.draw(&window);
		window.display();
	}

	return 0;
}