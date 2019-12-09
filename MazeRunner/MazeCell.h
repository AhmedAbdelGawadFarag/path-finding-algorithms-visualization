#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <SFML\Window\Joystick.hpp>
using namespace sf;

enum Path
{
    North,East, South ,West
};

class MazeCell
{

public:
	MazeCell(Vector2f position, Vector2f size, int column, int row, float wallWidth, Color backgroundColor, Color wallColor);
	~MazeCell();

	void draw(RenderWindow* window);
	void setActiveWalls(Path dir);
	void removeWalls(Path dir);
	int getColumn();
	int getRow();
	bool isVisited = false;
	void setBGColor(Color color);
	RectangleShape * getBackGround();
	
	bool activeWalls[4]{ true,true,true,true };
private:
	int column = 0;
	int row = 0;
	RectangleShape backGround;
	RectangleShape walls[4];
	Color bgColor;
	
	
};

