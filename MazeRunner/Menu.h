#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Maze.h"
#include "enums.h"
#include <string>
#include <filesystem>
using namespace sf;

#define MainMenuMaxElements 6
#define OptionsMenuMaxElements 6
#define SolveMenuMaxElements 5
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
	void eventHandler(Event&);
	void onAction();
	void fileNames();
	void reSize();
private:
	

	std::vector<Text*> mainMenu;
	std::vector<Text*> optionsMenu;
	std::vector<Text*> solveMenu;
	std::vector<VideoMode> videoModes = sf::VideoMode::getFullscreenModes();
	std::vector<std::string> files;
	Font font;

	MenuElement currentMenu = MenuElement::MainMenu;

	int mainMenuCurrentIndex = -1,
		optionsMenuCurrentIndex = -1,
		solveMenuCurrentIndex = -1,
		videoModeIndex = 9,
		filesIndex = 0;	
	
	RenderWindow* window;
	Maze* maze;
	ScreenMode screenMode = ScreenMode::Default;
	Animation animation = Animation::ON;
	Vector2i cellCount = Vector2i(45, 30);

	bool mainState = false,
		optionsState = false,
		videoModeSelected = false,
		rowSelected = false,
		columnSelected = false,
		filesSelected = false;

	float width, height;
	
};

