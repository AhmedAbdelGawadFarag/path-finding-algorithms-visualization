#include "Menu.h"
#include <iostream>
Menu::Menu(float width, float height)
{
	currentItem = -1;

	for (int i = 0; i < MenuMaxElements; i++)
		menu.push_back(new Text());

	
	font.loadFromFile("arial.ttf");
	
	
	menu[Options]->setFont(font);
	menu[Options]->setFillColor(Color::White);
	menu[Options]->setString("Resume");
	menu[Options]->setPosition(Vector2f(width / 3, height / (MenuMaxElements + 1) ));


	menu[Exit]->setFont(font);
	menu[Exit]->setFillColor(Color::White);
	menu[Exit]->setString("Options");
	menu[Exit]->setPosition(Vector2f(width / 3, height / (MenuMaxElements + 1) * 2 ));



	menu[2]->setFont(font);
	menu[2]->setFillColor(Color::White);
	menu[2]->setString("Test");
	menu[2]->setPosition(Vector2f(width / 3, height / (MenuMaxElements + 1) * 3));
	

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
	
	if (currentItem == -1 || currentItem == 0)
	{
		menu[0]->setFillColor(Color::White);
		currentItem = MenuMaxElements - 1;
		menu[currentItem]->setFillColor(Color::Red);
	}
	else
	{
		menu[currentItem]->setFillColor(Color::White);
		--currentItem;
		menu[currentItem]->setFillColor(Color::Red);

	}
		
}

void Menu::moveDown()
{
	if (currentItem != -1)
		menu[currentItem]->setFillColor(sf::Color::White);
	currentItem = (currentItem + 1) % MenuMaxElements;
	menu[currentItem]->setFillColor(Color::Red);

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
