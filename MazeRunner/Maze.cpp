#include "Maze.h"

Maze::Maze( RenderWindow* window, float wallWidth, Vector2i cells, Color backgroundColor, Color wallColor)
{
	std::srand(std::time(0));
	startMaze = NULL;
	endMaze = NULL;

	this->currentCell = 0;
	this->window = window;
	this->windowSize = window->getSize();
	this->cellCount = cells;
	this->cellSize.x = windowSize.x / cells.x;
	this->cellSize.y = windowSize.y / cells.y;
	this->wallWidth = wallWidth;
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

void Maze::fileUpdate()
{
	for (int i = 1, CellRow = 0; i < charVector.size(); i += 2, CellRow++) {
		for (int j = 1, CellColm = 0; j < charVector[i].size(); j += 2, CellColm++) {
			if (charVector[i][j] == '*') {
				cells[CellRow][CellColm]->getBackGround()->setFillColor(Color::Blue);
				setSart(cells[CellRow][CellColm]);
			}
			if (charVector[i][j] == 'O') {
				cells[CellRow][CellColm]->getBackGround()->setFillColor(Color::Magenta);
				SetEnd(cells[CellRow][CellColm]);
			}

			charConverter(i, j, CellRow, CellColm);
		}
	}
}

void Maze::draw()
{
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			cells[y][x]->draw(window, currentCell);
}

void Maze::generate(Vector2i cellCount)
{
	clear();
	fileOpen = false;

	this->cellCount = cellCount;
	this->cellSize = Vector2f(windowSize.x / cellCount.x, windowSize.y / cellCount.y);

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

void Maze::readFile(const std::string& FileName)
{
	clear();
	fileOpen = true;

	std::string s;
	std::ifstream inputfile(FileName);
	std::string row, column;

	inputfile >> column >> row;
	inputfile.close();

	inputfile.open(FileName);

	getline(inputfile, s);
	cellCount.y = stoi(row);
	cellCount.x = stoi(column);

	int y = 0;

	while (getline(inputfile, s)) {

		charVector.push_back(std::vector<char>());

		for (int x = 0; x < s.size(); x++)
		{
			charVector[y].push_back(s[x]);
		}
		y++;
	}
	
	cellSize = Vector2f(windowSize.x / cellCount.x, windowSize.y / cellCount.y);


	for (int y = 0; y < cellCount.y; y++) {
		cells.push_back(std::vector<MazeCell*>());
		for (int x = 0; x < cellCount.x; x++)
			cells[y].push_back(new MazeCell(Vector2f(x * cellSize.x, y * cellSize.y), Vector2f(cellSize.x, cellSize.y), x, y, wallWidth, backGroundColor, wallColor));
	}


	inputfile.close();
	fileUpdate();
}

void Maze::saveFile()
{
}

bool Maze::isFile()
{
	return fileOpen;
}

MazeCell* Maze::onButtonClick(Vector2i MousePosition)
{
	if (startMaze == NULL||endMaze == NULL) {
		for (int y = 0; y < cellCount.y; ++y) {

			for (int x = 0; x < cellCount.x; ++x) {

				Vector2f UpperLeftPoint, UpperRightPoint, LowerLeftPoint, LowerRightPoint;
				Vector2f BGsize = cells[y][x]->getBackGround()->getSize();
				//std::cout << "size" << BGsize.x << " " << BGsize.y << std::endl;
				UpperLeftPoint = cells[y][x]->getBackGround()->getPosition();
				//std:: cout << UpperLeftPoint.x << " " << UpperLeftPoint.y << std::endl;

				UpperRightPoint = Vector2f(UpperLeftPoint.x + BGsize.x, UpperLeftPoint.y);
				//std::cout << UpperRightPoint.x << " " << UpperRightPoint.y << std::endl;

				LowerLeftPoint = Vector2f(UpperLeftPoint.x, UpperLeftPoint.y + BGsize.y);
				//std::cout << LowerLeftPoint.x << " " << LowerLeftPoint.y << std::endl;

				LowerRightPoint = Vector2f(UpperLeftPoint.x + BGsize.x, UpperLeftPoint.y + BGsize.y);
				//std::cout << LowerRightPoint.x << " " << LowerRightPoint.y << std::endl;

				if (MousePosition.x >= UpperLeftPoint.x && MousePosition.x <= UpperRightPoint.x && MousePosition.y >= UpperLeftPoint.y && MousePosition.y <= LowerLeftPoint.y) {
					//std::cout << "yessss" << std::endl;
					if (startMaze == NULL) {
						setSart(cells[y][x]);
						cells[y][x]->getBackGround()->setFillColor(Color::Magenta);
					}
					else {
						SetEnd(cells[y][x]);
						cells[y][x]->getBackGround()->setFillColor(Color::Cyan);
					}
					return cells[y][x];
				}
				//system("pause");

			}

		}
	}
}

MazeCell* Maze::getCell(Vector2i position)
{
	if (position.x < 0 || position.y < 0 || position.x >= this->cellCount.x || position.y >= this->cellCount.y)
	{
		return nullptr;
	}
	return this->cells[position.y][position.x ];
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

void Maze::charConverter(int row, int colm, int CellRow, int CellColm)
{
	if (charVector[row][colm + 1] == ' ')cells[CellRow][CellColm]->removeWalls(East);
	if (charVector[row][colm - 1] == ' ')cells[CellRow][CellColm]->removeWalls(West);
	if (charVector[row - 1][colm] == ' ')cells[CellRow][CellColm]->removeWalls(North);
	if (charVector[row + 1][colm] == ' ')cells[CellRow][CellColm]->removeWalls(South);

	cells[CellRow][CellColm]->isVisited = true;

}

void Maze::clear()
{
	startMaze = NULL;
	endMaze = NULL;
	for (int y = 0; y < cellCount.y; ++y)
		for (int x = 0; x < cellCount.x; ++x)
			delete cells[y][x];
	
	charVector.clear();
	cells.clear();
	while (stack.size() != 0)
	{
		stack.pop();
	}
}
void Maze::setSart(MazeCell *cell)
{
	this->startMaze = cell;
	std::cout<<"start cell row is : "<<startMaze->getRow()<<" start colom is : "<<startMaze->getColumn()<<std::endl;
}

void Maze::SetEnd(MazeCell* cell)
{
	this->endMaze = cell;
	std::cout << "end cell row is : " << endMaze->getRow() << " end colom is : " << endMaze->getColumn() << std::endl;

}

MazeCell* Maze::getStart()
{
	return this->startMaze;
}

MazeCell* Maze::getEnd()
{
	return this->endMaze;
}

