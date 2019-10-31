#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Maze.h"
using namespace std;
using namespace sf;

int main() {

	// Create Window
	RenderWindow window(VideoMode(640, 400), "Maze Runner!");
	
	Maze maze(Vector2f(window.getSize().x, window.getSize().y), 3, Vector2i(45, 30), Color(220,100,25,10) , Color::White);
	
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