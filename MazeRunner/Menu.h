#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Maze.h"
#include "enums.h"
#include <string>
using namespace sf;

#define MainMenuMaxElements 5
#define OptionsMenuMaxElements 6

class Menu
{
public:
	Menu(RenderWindow *,Maze *);
	~Menu();
	void draw();
	void moveUp();
	void moveDown();
	bool isOpen();
	void open();
	void close();
	void update();
	void updateText();
	int checked();
	void eventHandler(Event&);
	void onAction();
private:
	

	std::vector<Text*> mainMenu;
	std::vector<Text*> filesMenu;
	std::vector<Text*> optionsMenu;
	std::vector<VideoMode> videoModes = sf::VideoMode::getFullscreenModes();

	Font font;

	MenuElement currentMenu = MenuElement::MainMenu;

	int mainMenuCurrentIndex = -1,
		optionsMenuCurrentIndex = -1,
		filesMenuCurrentIndex = -1,
		videoModeIndex = 9;	
	int fileMenuSize = 1;
	
	
	RenderWindow* window;
	Maze* maze;
	ScreenMode screenMode = ScreenMode::Default;
	Animation animation = Animation::ON;
	Vector2i cellCount = Vector2i(45, 30);

	bool mainState = false,
		optionsState = false,
		filesState = false,
		videoModeSelected = false,
		rowSelected = false,
		columnSelected = false;
	
};

