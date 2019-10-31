#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include "MazeCell.h"
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
private:
	Vector2i cellCount;
	std::stack<MazeCell*> stack;
	MazeCell* currentCell;
	std::vector<std::vector<MazeCell*>> cells;
	int row, column;

};

