#pragma once
#include "SFML/Graphics.hpp"
#include <sstream>
using namespace sf;

#define LIMIT 4
#define DELETE 8

class TextBox
{
public:
	
	TextBox(Vector2f pos);

	void input(Event evnt);
	void draw(RenderWindow& window);
	Text getText();
	void setPos(Vector2f);
private:
	
	Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	
	void deleteLastChar();
	void type(int charTyped);
	
};