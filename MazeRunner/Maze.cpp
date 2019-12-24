#include "Maze.h"

Maze::Maze( RenderWindow* window, float wallWidth, Vector2i cells, Color backgroundColor, Color wallColor)
{
	std::srand(std::time(0));
	startMaze = NULL;
	endMaze = NULL;

	this->currentCell = 0;
	this->window = window;
	this->windowSize = Vector2f(window->getSize().x,window->getSize().y);
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
				cells[CellRow][CellColm]->getBackGround()->setFillColor(Color::Magenta);
				setStart(cells[CellRow][CellColm]);
			}
			if (charVector[i][j] == 'O') {
				cells[CellRow][CellColm]->getBackGround()->setFillColor(Color::Cyan);
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
			cells[y][x]->draw(window);
}

void Maze::generate(Vector2i cellCount)
{
	clear();
	fileOpen = false;

	this->windowSize = Vector2f(this->window->getSize().x,this->window->getSize().y);
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
					if (startMaze == NULL) 
						setStart(cells[y][x]);
					else 
						SetEnd(cells[y][x]);

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

void Maze::getNeighbors(Vector2i current, std::vector<Vector2i>& neighbors)
{
	neighbors.clear();
	if (!cells[current.y][current.x	]->activeWalls[North])
		neighbors.push_back(Vector2i(current.x, current.y - 1));
	if (!cells[current.y][current.x]->activeWalls[East])
		neighbors.push_back(Vector2i(current.x + 1, current.y));
	if (!cells[current.y][current.x]->activeWalls[South])
		neighbors.push_back(Vector2i(current.x, current.y + 1));
	if (!cells[current.y][current.x]->activeWalls[West])
		neighbors.push_back(Vector2i(current.x - 1, current.y));

}

void Maze::getUnVisitedNeighbor(Vector2i current, Vector2i &neighbor, const std::vector<std::vector<bool>>& visited)
{
	neighbor.y = -1;
	neighbor.x = -1;
	if (!cells[current.y][current.x]->activeWalls[East] && visited[current.y][current.x + 1] == false)
		neighbor = Vector2i(current.x + 1, current.y);
	else if (!cells[current.y][current.x]->activeWalls[South] && visited[current.y + 1][current.x] == false)
		neighbor = Vector2i(current.x, current.y + 1);
	else if (!cells[current.y][current.x]->activeWalls[West] && visited[current.y][current.x - 1] == false)
		neighbor = Vector2i(current.x - 1, current.y);
	else if (!cells[current.y][current.x]->activeWalls[North] && visited[current.y - 1][current.x] == false)
		neighbor = Vector2i(current.x, current.y - 1);
}

void Maze::colorPath(std::vector<Vector2i>& path)
{
	for (int i = 0; i < path.size(); i++)
		cells[path[i].y][path[i].x]->setBGColor(PathColor);
}

void Maze::clearColor()
{
	for (int y = 0; y < cellCount.y; ++y)
		for (int x = 0; x < cellCount.x; ++x)
			cells[y][x]->setBGColor(backGroundColor);
}

void Maze::setStart(MazeCell *cell)
{
	this->startMaze = cell;
	this->startMaze->setBGColor(Color::Green);
	startCell.x = cell->getColumn();
	startCell.y = cell->getRow();
	std::cout<<"start cell row is : "<< startMaze->getRow() <<" start colom is : "<< startMaze->getColumn() << std::endl;
}

void Maze::SetEnd(MazeCell* cell)
{
	this->endMaze = cell;
	this->endMaze->setBGColor(Color::Red);
	endCell.x = cell->getColumn();
	endCell.y = cell->getRow();
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

void Maze::BFS()
{
	// remove colors
	clearColor();

	// if start and end not selected set them to default
	if (startMaze == NULL || endMaze == NULL)
	{
		setStart(cells[0][0]);
		SetEnd(cells[cellCount.y - 1][cellCount.x - 1]);
	}
	// counter to visited cells 
	int visitedCounter = 0;
	// bool grid to check visited or not
	std::vector<std::vector<bool>> visited(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			visited[y].push_back(false);

	// BFS queue
	std::queue<Vector2i> queue;

	// put start cell to the queue
	queue.push(Vector2i(startMaze->getColumn(), startMaze->getRow()));

	// make first cell visited
	visited[queue.front().y][queue.front().x] = true;
	++visitedCounter;
	cells[queue.front().y][queue.front().x]->setBGColor(VisitedCellColor);

	// Root grid to find solution at the end
	std::vector<std::vector<Vector2i>> root(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			root[y].push_back(Vector2i(-1,-1));
		
	Vector2i node;
	std::vector<Vector2i> neighbors;
	bool end = false;
	while (!queue.empty() && !end)
	{
		// get the next node in the queue 
		node = queue.front();
		queue.pop();
		// get the neighbors of the node
		getNeighbors(node, neighbors);
		// iterate on each neighbor
		for (auto next : neighbors)
		{
			// check if the neighbor wasn't visited
			if (!visited[next.y][next.x])
			{
				// push each not visited neighbor and mark it as visited
				queue.push(next);
				visited[next.y][next.x] = true;
				++visitedCounter;

				// set the root of each of the neighbors to backtrack the path
				root[next.y][next.x] = node;

				// check if it was the end cell
				if (next.y == endMaze->getRow() && next.x == endMaze->getColumn())
					end = true;

				// Color visited cells
				cells[next.y][next.x]->setBGColor(VisitedCellColor);	
			}
		}
		window->clear();
		draw();
		window->display();
	}
 
	if (end)
	{
		// clear console screen
		system("cls");

		// get the path from the end until finding default (-1,-1) 
		std::vector<Vector2i> path;
		
		Vector2i at = Vector2i(endMaze->getColumn(), endMaze->getRow());

		for (at ; at.x != -1 , at.y != -1 ; at = root[at.y][at.x])
			path.push_back(at);

		// reverse the path to ouput it correctly
		std::reverse(path.begin(), path.end());

		std::cout << "Visited Cells Count : " << visitedCounter << "\nPath Cell Count : " << path.size() << "\n";

		int counter = 0;
		for (auto it : path)
		{
			std::cout << "(" << it.x << "," << it.y << ")" << " ";
			if (counter == 10)
			{
				std::cout << "\n";
				counter = 0;
			}
			++counter;
		}
		// Color the path
		colorPath(path);

	}

}

void Maze::DFS()
{
	// remove colors
	clearColor();

	// if start and end not selected set them to default
	if (startMaze == NULL )
	{
		setStart(cells[0][0]);
		SetEnd(cells[cellCount.y - 1][cellCount.x - 1]);
	}
	else if (endMaze == NULL&& startMaze != NULL)
	{

		SetEnd(cells[cellCount.y - 1][cellCount.x - 1]);
	}

	// counter to visited cells 
	int visitedCounter = 0;

	// bool grid to check visited or not
	std::vector<std::vector<bool>> visited(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			visited[y].push_back(false);

	// DFS Stack
	std::stack<Vector2i> stack;

	// put the first cell to the stack
	stack.push(Vector2i(startMaze->getColumn(), startMaze->getRow()));

	Vector2i node;
	Vector2i neighbor;
	Vector2i endCell = Vector2i(endMaze->getColumn(), endMaze->getRow());
	bool end = false;

	while (!stack.empty())
	{
		// get top of the stack	
		node = stack.top();

		// mark it as visited
		cells[node.y][node.x]->setBGColor(PathColor);
		visited[node.y][node.x] = true;
		++visitedCounter;

		// check if it was the end 
		if (node.x == endCell.x && node.y == endCell.y)
		{
			end = true;
			break;
		}
		
        // get node negibor
		getUnVisitedNeighbor(node, neighbor, visited);

		if (neighbor.y != -1)
		{
			stack.push(neighbor);
			
		}
		else
		{
			cells[stack.top().y][stack.top().x]->setBGColor(VisitedCellColor);
			stack.pop();
		}
		window->clear();
		draw();
		window->display();
	}
	if (end)
	{
		// clear console screen
		system("cls");

		// get the reversed path from the stack
		std::vector<Vector2i> path;

		while (stack.size() > 0)
		{
			path.push_back(stack.top());
			stack.pop();
		}

		// reverse the path
		std::reverse(path.begin(), path.end());

		std::cout << "Visited Cells Count : " << visitedCounter << "\nPath Cell Count : " << path.size() << "\n";

		int counter = 0;
		for (auto it : path)
		{
			std::cout << "(" << it.x << "," << it.y << ")" << " ";
			if (counter == 10)
			{
				std::cout << "\n";
				counter = 0;
			}
			++counter;
		}
	}
}

void Maze::BestFirst()
{
	clearColor();
	// if start and end not selected set them to default
	if (startMaze == NULL || endMaze == NULL)
	{
		setStart(cells[0][0]);
		SetEnd(cells[cellCount.y - 1][cellCount.x - 1]);
	}

	// counter to visited cells  & Examined
	int visitedCounter = 1, examinedCounter = 1;

	// bool grid to check visited or not
	std::vector<std::vector<bool>> visited(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			visited[y].push_back(false);

	// bool to show Examined
	std::vector<std::vector<bool>> examined(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			examined[y].push_back(false);

	// Root path
	std::vector<std::vector<Vector2i>> root(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			root[y].push_back(Vector2i(-1, -1));

	// Best First Search Priority Queue
	std::priority_queue <Vector2i, std::vector<Vector2i>, compare> pq;

	// put first cell 
	pq.push(startCell);
	// make first cell visited
	visited[pq.top().y][pq.top().x] = true;
	examined[pq.top().y][pq.top().x] = true;
	cells[pq.top().y][pq.top().x]->setBGColor(VisitedCellColor);

	bool end = false;
	std::vector<Vector2i> neighbors;

	do
	{
		Vector2i currentCell = pq.top();
		pq.pop();
		++examinedCounter;
		if (currentCell == this->endCell)
			end = true;
		else
		{
			getNeighbors(currentCell, neighbors);
			for (auto next : neighbors)
			{
				// check if the neighbor wasn't visited
				if (!visited[next.y][next.x])
				{
					// push each not visited neighbor and mark it as visited 
					visited[next.y][next.x] = true;
					++visitedCounter;
					pq.push(next);
					// set the color of visited cells
					cells[next.y][next.x]->setBGColor(VisitedCellColor);
					root[next.y][next.x] = currentCell;
				}
			}
			examined[currentCell.y][currentCell.x] = true;
			cells[currentCell.y][currentCell.x]->setBGColor(PathColor);
		}
		// redraw maze to update colors
		window->clear();
		draw();
		window->display();
	} while (!pq.empty() && !end);

	if (end)
	{
		// clear console screen
		system("cls");

		
		std::vector<Vector2i> path;

		Vector2i at = Vector2i(endMaze->getColumn(), endMaze->getRow());

		// get the path from root grid
		for (at; at.x != -1, at.y != -1; at = root[at.y][at.x])
			path.push_back(at);

		// reverse the path to ouput it correctly
		std::reverse(path.begin(), path.end());

		// Color the path
		for (int i = 0; i < path.size(); i++)
			cells[path[i].y][path[i].x]->setBGColor(RouteColor);

		std::cout << "Visited Cells Count : " << visitedCounter << "\nPath Cell Count : " << path.size() << "\n";

		int counter = 0;
		for (auto it : path)
		{
			std::cout << "(" << it.x << "," << it.y << ")" << " ";
			if (counter == 10)
			{
				std::cout << "\n";
				counter = 0;
			}
			++counter;
		}
	}

}
void Maze::dijkstra()
{

	clearColor();

	// if start and end not selected set them to default
	if (startMaze == NULL || endMaze == NULL)
	{
		setStart(cells[0][0]);
		SetEnd(cells[cellCount.y - 1][cellCount.x - 1]);
	}
	// counter to visited cells 
	int visitedCounter = 0;
	// bool grid to check visited or not
	std::vector<std::vector<bool>> visited(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			visited[y].push_back(false);

	std::vector<std::vector<Vector2i>> root(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			root[y].push_back(Vector2i(-1, -1));

	cout << root[4][6].y << "enddd2" << root[4][6].x << endl;

	vector<vector<int>> distance(this->cellCount.y);
	for (int y = 0; y < cellCount.y; y++)
		for (int x = 0; x < cellCount.x; x++)
			distance[y].push_back(-1);

	set<pair<int, pair<int, int>>> dset;

	dset.insert(make_pair(0, make_pair(startMaze->getRow(), startMaze->getColumn())));
	distance[startMaze->getRow()][startMaze->getColumn()] = 0;
	Vector2i node;
	node.y = startMaze->getRow();
	node.x = startMaze->getColumn();


	while (!dset.empty()) {
		//cells[node.y][node.x]->setBGColor(Color::Blue);
		dset.erase(dset.begin());
		visited[node.y][node.x] = true;
		++visitedCounter;
		for (int i = 0; i < 4; i++) {
			int rr = node.y + dr[i];
			int cc = node.x + dc[i];
			if (rr < 0 || cc < 0) continue;
			if (rr > cellCount.y - 1 || cc > cellCount.x - 1) continue;
			if (visited[rr][cc] == true) continue;
			if (i == 0) {
				if (!cells[node.y][node.x]->activeWalls[North]) {
					putcell(node.y, node.x, rr, cc, dset, distance[node.y][node.x], distance[rr][cc], root, distance);
					//	cout << rr << "  " << cc << endl;
				}
			}
			else if (i == 1) {
				if (!cells[node.y][node.x]->activeWalls[South]) {
					putcell(node.y, node.x, rr, cc, dset, distance[node.y][node.x], distance[rr][cc], root, distance);
					//cout << rr << " " << cc << endl;
				}
			}
			else if (i == 2) {
				if (!cells[node.y][node.x]->activeWalls[East]) {
					putcell(node.y, node.x, rr, cc, dset, distance[node.y][node.x], distance[rr][cc], root, distance);
					//cout << rr << " " << cc << endl;

				}
			}
			else if (i == 3) {
				if (!cells[node.y][node.x]->activeWalls[West]) {
					putcell(node.y, node.x, rr, cc, dset, distance[node.y][node.x], distance[rr][cc], root, distance);
					//	cout << rr << " " << cc << endl;

				}
			}

		}
		if (!dset.empty()) {
			pair<int, pair<int, int>> p = *(dset.begin());

			node.y = p.second.first;
			node.x = p.second.second;

		}


	}
	Vector2i end;
	end.x = endMaze->getRow();
	end.y = endMaze->getColumn();
	std::vector<Vector2i> path;

	while (end != Vector2i(-1, -1)) {
		path.push_back(end);
		cells[end.x][end.y]->setBGColor(Color::Green);
		end = root[end.x][end.y];
	}

	std::reverse(path.begin(), path.end());
	system("cls");
	cout << "Visited Cells : " << visitedCounter << "\nPath Size : " << path.size() << "\n";
	int cnt = 1;
	for (auto x : path)
	{
		if (cnt == 10)
		{
			cnt = 1;
			cout << "\n";
		}
		cout << "(" << x.y << "," << x.x << ") ";
		++cnt;
	}
	window->clear();
	draw();
	window->display();

}
void Maze::putcell(int r, int c, int rr, int cc, set<pair<int, pair<int, int>>>& dset, int distanceNood, int distanceNeighbour, vector<vector<Vector2i>>& root, vector<vector<int>>& distance)
{

	if (distanceNeighbour == -1) {
		distanceNeighbour = distanceNood + 1;
		dset.insert(make_pair(distanceNeighbour, make_pair(rr, cc)));
		distance[rr][cc] = distanceNeighbour;
		root[rr][cc] = Vector2i(r, c);
		//	cout << root[rr][cc].x<<" root "<< root[rr][cc].y<< endl;

	}
	else if (abs(distanceNood) + 1 < abs(distanceNeighbour)) {
		auto f = dset.find(make_pair(distanceNeighbour, make_pair(rr, cc)));

		dset.erase(f);

		distanceNeighbour = distanceNood + 1;


		dset.insert(make_pair(distanceNeighbour, make_pair(rr, cc)));

		distance[rr][cc] = distanceNeighbour;


		root[rr][cc] = Vector2i(r, c);

	}

}