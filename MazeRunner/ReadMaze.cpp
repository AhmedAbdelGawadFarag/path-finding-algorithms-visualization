#include "ReadMaze.h"

ReadMaze::ReadMaze(string FileName, Vector2u WindowSize, float wallWidth, Color backgroundColor, Color wallColor)
{
	
	string s;

	cin >> width>>height;
	cellnum.x = width;
	cellnum.y = height;
	
	ifstream inputfile(FileName);
	int cnt = 0;
	while (getline(inputfile, s)) {
		
			MazeVector.push_back(vector<char>());
		
			for (int j = 0; j <s.size(); j++) 
				MazeVector[cnt].push_back( s[ j ] );

			cnt++;
	}



	Vector2f cellsize(WindowSize.x/cellnum.x,WindowSize.y/cellnum.y);

	
	for (int i = 0; i < height; i++) {
		cells.push_back(vector<MazeCell*>());
		for (int j = 0; j < width; j++) 
		cells[i].push_back(new MazeCell(Vector2f(j * cellsize.x, i * cellsize.y), Vector2f(cellsize.x, cellsize.y), j, i, wallWidth, backgroundColor, wallColor));
	}
	
	
	inputfile.close();	
}

void ReadMaze::draw(RenderWindow* window)
{
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cells[i][j]->draw(window,cells[i][j]);
		}
	}

}

void ReadMaze::CheckRight(int row, int colm, int CellRow, int CellColm)
{
	if (MazeVector[row][colm+1] == ' ')cells[CellRow][CellColm]->removeWalls(East);
}

void ReadMaze::CheckLeft(int row, int colm, int CellRow, int CellColm)
{
	if (MazeVector[row][colm - 1] == ' ')cells[CellRow][CellColm]->removeWalls(West);
}

void ReadMaze::CheckUp(int row, int colm,int CellRow,int CellColm)
{
	if (MazeVector[row - 1][colm] == ' ')cells[CellRow][CellColm]->removeWalls(North);
}

void ReadMaze::CheckDown(int row, int colm, int CellRow, int CellColm)
{
	if (MazeVector[row + 1][colm] == ' ')cells[CellRow][CellColm]->removeWalls(South);

}

void ReadMaze::update()
{
	for (int i = 1, CellRow=0; i < MazeVector.size(); i+=2, CellRow++) {
		for (int j = 1, CellColm=0; j <MazeVector[i].size() ; j+=2, CellColm++) {
			CheckDown(i, j, CellRow, CellColm);
			CheckRight(i, j, CellRow, CellColm);
			CheckUp(i, j, CellRow, CellColm);
			CheckLeft(i, j, CellRow, CellColm);

		}
		
	}

}
