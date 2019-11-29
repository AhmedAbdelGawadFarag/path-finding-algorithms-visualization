#include "Maze.h"
#include <vector>
#include <iostream>


Maze::Maze( Vector2f windowSize, float wallWidth, Vector2i cells, Color backgroundColor, Color wallColor)
{
	std::srand(std::time(0));

	this->currentCell = 0;
	this->cellCount = cells;
	this->wallWidth = wallWidth;
	this->cellSize.x = windowSize.x / cells.x;
	this->cellSize.y = windowSize.y / cells.y;
	this->backGroundColor = backgroundColor;
	this->wallColor = wallColor;

	for (int y = 0; y < cellCount.y; ++y) {
		this->cells.push_back( std::vector<MazeCell*> () );
		for (int x = 0; x < cellCount.x; ++x)
			this->cells[y].push_back(new MazeCell( Vector2f(x * cellSize.x , y * cellSize.y ), Vector2f(cellSize.x, cellSize.y), x, y, wallWidth, backgroundColor, wallColor) );
	}
	int y = std::rand() % cellCount.y;
	int x = std::rand() % cellCount.x;
	
	this->currentCell = this->cells[y][x];
	this->stack.push(this->currentCell);
}

Maze::~Maze()
{
	clear();
}

MazeCell* Maze::getCell(Vector2i position)
{
	if (position.x < 0 || position.y < 0 || position.x >= this->cellCount.x || position.y >= this->cellCount.y)
	{
		return nullptr;
	}
	return this->cells[position.y][position.x ];
}

void Maze::update()
{
	do {
		
		currentCell->isVisited = true;
		MazeCell* temp;
		temp = randomCell(currentCell);
		if (temp != nullptr) {

			this->removeWalls(currentCell, temp);
			currentCell = temp;
			stack.push(currentCell);
		}
		else
		{
			if (stack.size() > 1) {
				stack.pop();
				currentCell = stack.top();
			}
		}
	} while (!animation && stack.size() != 1);
}

void Maze::draw(RenderWindow* window)
{
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			cells[y][x]->draw(window,currentCell);
}

MazeCell* Maze::randomCell(MazeCell* cell)
{
	std::vector<MazeCell*> random;
	MazeCell* temp;
	int column = currentCell->getColumn();
	int row = currentCell->getRow();

	// check if can go up
	if ( row > 0 ) {
	    temp = getCell( Vector2i( column, row - 1 ));
        if(!temp->isVisited)	
			random.push_back(temp);
	}

	// check if can go down
	if (row < cellCount.y - 1) {
		temp = getCell(Vector2i( column, row + 1));
		if (!temp->isVisited)
			random.push_back(temp);
	}

	// check if can go left
	if (column > 0) {
		temp = getCell(Vector2i( column - 1, row));
		if (!temp->isVisited)
			random.push_back(temp);
	}

	// check if can go right
	if ( column < cellCount.x - 1 ) {
		temp = getCell( Vector2i(column + 1, row) );
		if (!temp->isVisited)
			random.push_back(temp);
	}
	
	if (random.size() == 0)
		return nullptr;
	else
		return random[std::rand() % random.size()];
}

void Maze::removeWalls(MazeCell* current, MazeCell* next)
{
	// South Side
	if (current->getRow() == next->getRow() - 1 ) {
		next->removeWalls(North);
		currentCell->removeWalls(South);
	}
	// North Side
	else if ( current->getRow() == next->getRow() + 1)
	{
		next->removeWalls(South);
		current->removeWalls(North);
	}
	// West Side
	else if (current->getColumn() == next->getColumn() + 1)
	{
		next->removeWalls(East);
		current->removeWalls(West);
	}
	// East Side
	else if (current->getColumn() == next->getColumn() - 1)
	{
		next->removeWalls(West);
		current->removeWalls(East);
	}
}


void Maze::clear()
{
	for (int y = 0; y < cellCount.y; ++y)
		for (int x = 0; x < cellCount.x; ++x)
			delete cells[y][x];

	cells.clear();

	while (stack.size() != 0)
	{
		stack.pop();
	}
}

void Maze::generate(Vector2f WindowSize, Vector2i cellCount)
{
	clear();

	this->cellCount = cellCount;
	this->cellSize = Vector2f(WindowSize.x / cellCount.x, WindowSize.y / cellCount.y);

	for (int y = 0; y < cellCount.y; ++y) {
		this->cells.push_back(std::vector<MazeCell*>());
		for (int x = 0; x < cellCount.x; ++x)
			this->cells[y].push_back(new MazeCell(Vector2f(x * cellSize.x, y * cellSize.y), Vector2f(cellSize.x, cellSize.y), x, y, wallWidth, backGroundColor, wallColor));
	}

	int y = std::rand() % cellCount.y;
	int x = std::rand() % cellCount.x;

	this->currentCell = this->cells[y][x];
	this->stack.push(this->currentCell);
}

