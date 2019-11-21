#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

#define MenuMaxElements 3

enum MenuElement
{
	Options, Exit
};

class Menu
{
public:
	Menu(float width , float height);
	~Menu();
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
	bool isOpen();
	void open();
	void close();

private:
	bool currentState = false;
	int currentItem;
	std::vector<Text*> menu;
	Font font;
};
