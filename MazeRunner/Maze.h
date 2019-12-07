#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include "MazeCell.h"
#include "enums.h"
#include <string>
#include <fstream>
#include<iostream>

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
	MazeCell* onButtonClick(Vector2i MousePosition,Color color);
	
	void setSart(MazeCell* cell);
	void SetEnd(MazeCell* cell);
	MazeCell* getStart();
	MazeCell* getEnd();

private:
	MazeCell* getCell(Vector2i position);
	MazeCell* randomCell(MazeCell* cell);
	void removeWalls(MazeCell*, MazeCell*);
	void charConverter(int row, int colm, int CellRow, int CellColm);
	void fileUpdate();
	void clear();

public:
	bool animation = true;

private:
	MazeCell* currentCell;
	RenderWindow* window;

	std::vector<std::vector<MazeCell*>> cells;
	std::stack<MazeCell*> stack;

	
	Vector2i cellCount;
	Vector2f cellSize;
	Vector2u windowSize;
	Color backGroundColor, wallColor;

	std::vector<std::vector<char>> charVector;

	int row = 0, column = 0;
	float wallWidth = 0;

	int fileWidth = 0;
	int fileHeight = 0;
	bool fileOpen = false;
	MazeCell* startMaze;
	MazeCell* endMaze;
	

};

