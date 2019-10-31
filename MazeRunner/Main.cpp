#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {

	// Create Window
	RenderWindow window(VideoMode(1920, 1080), "Maze Runner!");
	
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		
		window.display();
	}

	return 0;
}