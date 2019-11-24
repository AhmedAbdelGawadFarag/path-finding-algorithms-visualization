#include "Menu.h"
#include <iostream>
Menu::Menu(float width, float height)
{
	currentItem = -1;

	for (int i = 0; i < MenuMaxElements; i++)
		menu.push_back(new Text());

	
	font.loadFromFile("arial.ttf");
	
	
	menu[Generate]->setFont(font);
	menu[Generate]->setFillColor(Color::White);
	menu[Generate]->setString("Generate maze");
	menu[Generate]->setPosition(Vector2f( (width - 40) / 2, height / (MenuMaxElements ) ));


	menu[Exit]->setFont(font);
	menu[Exit]->setFillColor(Color::White);
	menu[Exit]->setString("Options");
	menu[Exit]->setPosition(Vector2f((width - 17) / 2, (height / MenuMaxElements) + 170));
	


	menu[Files]->setFont(font);
	menu[Files]->setFillColor(Color::White);
	menu[Files]->setString("Maze From File");
	menu[Files]->setPosition(Vector2f((width - 40) / 2, (height / MenuMaxElements) + 85));

	
	

}

Menu::~Menu()
{
	for (int i = 0; i < MenuMaxElements; i++)
		delete 	menu[i];
}

void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < MenuMaxElements; i++)
		window.draw(*this->menu[i]);
}

void Menu::moveUp()
{
	
	currentItem--;
	if (currentItem < 0) {
		currentItem = MenuMaxElements - 1;
;
	}
	update();
	
}

void Menu::moveDown()
{
	currentItem++;
	if (currentItem >= MenuMaxElements)
		currentItem = 0;
	update();
}

bool Menu::isOpen()
{
	return currentState;
}

void Menu::open()
{
	currentState = true;
}

void Menu::close()
{
	currentState = false;
}

void Menu::update()
{
	for (int i = 0; i < MenuMaxElements; i++) menu[i]->setFillColor(Color::White);

	menu[currentItem]->setFillColor(Color::Red);
	
}

int Menu::checked()
{
	return currentItem;
}
