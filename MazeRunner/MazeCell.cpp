#include "MazeCell.h"

MazeCell::MazeCell(Vector2f position, Vector2f size, int column, int row, float wallWidth, Color backgroundColor, Color wallColor)
{
	bgColor = backgroundColor;

	this->row = row;
	this->column = column;
	
	this->backGround.setSize(size);
	this->backGround.setPosition(position);
	this->backGround.setFillColor(backgroundColor);

	this->walls[North] = RectangleShape( Vector2f(size.x, wallWidth) );
	this->walls[North].setPosition( Vector2f(position.x, position.y) );
	this->walls[North].setFillColor(wallColor);

	this->walls[East] = RectangleShape( Vector2f(wallWidth, size.y) );
	this->walls[East].setPosition( Vector2f(position.x + size.x - wallWidth, position.y) );
	this->walls[East].setFillColor(wallColor);

	this->walls[South] = RectangleShape( Vector2f(size.x, wallWidth) );
	this->walls[South].setPosition(Vector2f(position.x, position.y + size.y - wallWidth));
	this->walls[South].setFillColor(wallColor);

	this->walls[West] = RectangleShape( Vector2f(wallWidth, size.y) );
	this->walls[West].setPosition( Vector2f(position.x, position.y) );
	this->walls[West].setFillColor(wallColor);
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
	  if (this->activeWalls[North])
		  window->draw(this->walls[North]);
	  if (this->activeWalls[West])
		  window->draw(this->walls[West]);
	  

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

void MazeCell::setBGColor(Color color)
{
	backGround.setFillColor(color);
}

RectangleShape * MazeCell::getBackGround()
{
	return &backGround;
}

