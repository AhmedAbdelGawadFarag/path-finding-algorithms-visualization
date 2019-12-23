#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include "MazeCell.h"
#include "enums.h"
#include <string>
#include <fstream>
#include<iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <functional>

#define PathColor Color::Cyan
#define VisitedCellColor Color::Yellow
#define RouteColor Color::Green

using namespace sf;
class Maze
{
public:
	Maze( RenderWindow* window, float wallWidth, Vector2i cellSize, Color backgroundColor, Color wallColor);
	~Maze();

	void update();
	void draw();
	void generate(Vector2i cellSize);
	void readFile(const std::string &FileName);
	void saveFile();
	bool isFile();
	MazeCell* onButtonClick(Vector2i MousePosition);
	
	void setStart(MazeCell* cell);
	void SetEnd(MazeCell* cell);
	MazeCell* getStart();
	MazeCell* getEnd();
	void BFS();
	void DFS();
	void BestFirst();
private:
	MazeCell* getCell(Vector2i position);
	MazeCell* randomCell(MazeCell* cell);
	void removeWalls(MazeCell*, MazeCell*);
	void charConverter(int row, int colm, int CellRow, int CellColm);
	void fileUpdate();
	void clear();
	void getNeighbors(Vector2i current, std::vector<Vector2i>& neighbors);
	void getUnVisitedNeighbor(Vector2i current, Vector2i &neighbor, const std::vector<std::vector<bool>>& visited);
	void colorPath(std::vector<Vector2i>& path);
	void clearColor();
public:
	bool animation = true;
	static inline Vector2i startCell, endCell;
private:
	MazeCell* currentCell;
	RenderWindow* window;

	std::vector<std::vector<MazeCell*>> cells;
	std::stack<MazeCell*> stack;

	
	Vector2i cellCount;
	Vector2f cellSize;
	Vector2f windowSize;
	Color backGroundColor, wallColor;

	std::vector<std::vector<char>> charVector;

	int row = 0, column = 0;
	float wallWidth = 0;

	int fileWidth = 0;
	int fileHeight = 0;
	bool fileOpen = false;
	MazeCell* startMaze = NULL;
	MazeCell* endMaze = NULL;
};

struct compare
{
	bool operator()(Vector2i first, Vector2i second)
	{
		return sqrt(pow(first.x - Maze::endCell.x, 2) + pow(first.y - Maze::endCell.y, 2)) > sqrt(pow(second.x - Maze::endCell.x, 2) + pow(second.y - Maze::endCell.y, 2));
	}
};