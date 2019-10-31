#include "MazeCell.h"

MazeCell::MazeCell(Vector2f position, Vector2f size, int column, int row, float wallWidth, Color backgroundColor, Color wallColor)
{
	this->backGround.setSize(size);
	this->backGround.setPosition(position);
	this->backGround.setFillColor(backgroundColor);

	this->walls[East].setSize(Vector2f(wallWidth, size.y));
	this->walls[East].setPosition(Vector2f(position.x + size.x , position.y));
	this->walls[East].setFillColor(wallColor);

	this->walls[South].setSize(Vector2f(size.x, wallWidth));
	this->walls[South].setPosition(Vector2f(position.x, position.y + size.y));
	this->walls[South].setFillColor(wallColor);

	this->setActiveWalls(East);
	this->setActiveWalls(South);

	this->row = row;
	this->column = column;
}

MazeCell::~MazeCell()
{
}

void MazeCell::draw(RenderWindow* window)
{
      if(this->isVisited)
		  window->draw(this->backGround);
	  if (this->activeWalls[East]) 
		  window->draw(this->walls[East]);
	  if (this->activeWalls[South])
		  window->draw(this->walls[South]);
}

void MazeCell::setActiveWalls(Path dir)
{
	this->activeWalls[dir] = true;

}

void MazeCell::removeWalls(Path dir)
{
	this->activeWalls[dir] = false;
}

int MazeCell::getColumn()
{
	return this->column;
}

int MazeCell::getRow()
{
	return this->row;
}
