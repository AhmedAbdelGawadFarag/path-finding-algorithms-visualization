#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include "MazeCell.h"
#include "enums.h"

using namespace sf;
class Maze
{
public:
	Maze( Vector2f WindowSize, float wallWidth, Vector2i cellSize, Color backgroundColor, Color wallColor);
	~Maze();

	MazeCell* getCell(Vector2i position);
	void update();
	void draw(RenderWindow* window);
	MazeCell* randomCell(MazeCell * cell);
	void removeWalls(MazeCell*,MazeCell*);
	void clear();
	void generate(Vector2f WindowSize, Vector2i cellSize);

	bool animation = true;
private:
	Vector2i cellCount;
	std::stack<MazeCell*> stack;
	MazeCell* currentCell;
	std::vector<std::vector<MazeCell*>> cells;
	int row = 0, column = 0;
	Vector2f cellSize;
	float wallWidth = 0;
	Color backGroundColor, wallColor;
	

};

