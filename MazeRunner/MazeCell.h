#pragma once
#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;

enum Path
{
	East, South
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

private:
	int column = 0;
	int row = 0;
	RectangleShape backGround;
	RectangleShape walls[2];
	bool activeWalls[2]{false,false};
	
};

