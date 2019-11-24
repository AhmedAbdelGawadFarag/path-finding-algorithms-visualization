#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include"MazeCell.h"
#include<SFML/Graphics.hpp>
using namespace std;
class ReadMaze
{
private:
	int width;
	int height;
	
	vector<vector<char>> MazeVector;
	vector<vector<MazeCell*>> cells;
	Vector2i cellnum;
	
	
public:
	ReadMaze(string FileName, Vector2u WindowSize,float wallWidth, Color backgroundColor, Color wallColor);
	void draw(RenderWindow *window);
	void CheckRight(int row,int colm, int CellRow, int CellColm);
	void CheckLeft(int row,int colm, int CellRow, int CellColm);
	void CheckUp(int row,int colm, int CellRow, int CellColm);
	void CheckDown(int row,int colm, int CellRow, int CellColm);
	void update();
};

