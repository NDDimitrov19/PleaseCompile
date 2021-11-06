#include "maze.h"

Maze::Maze(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;

	this->generateMaze(this->cols, this->rows);
}

Maze::~Maze()
{
	for (auto i : grid)
	{
		delete i;
	}
}

Maze::Cell::Cell(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

void Maze::generateMaze(const int& cols, const int& rows)
{
	// Generate cells
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			this->grid.push_back(new Cell(j, i));

	// Choose starting point
	this->currentCell = this->grid[0];
	this->currentCell->visited = true;
	this->cellStack.push(this->currentCell);

	// Generate maze from starting point
	while (!this->cellStack.empty())
	{
		this->currentCell = this->cellStack.top();
		this->cellStack.pop();

		Cell* nextCell = this->getRandUnvisitedNeighbourAt(this->currentCell->x, this->currentCell->y);
		if (nextCell)
		{
			this->cellStack.push(this->currentCell);
			this->removeAdjacentCellWall(this->currentCell, nextCell);
			nextCell->visited = true;
			this->cellStack.push(nextCell);
		}
	}
}

void Maze::removeAdjacentCellWall(Cell* a, Cell* b)
{
	int x = a->x - b->x;
	if (x == 1)
	{
		a->walls[Maze::CellWallDirs::left] = false;
		b->walls[Maze::CellWallDirs::right] = false;
	}
	else if (x == -1)
	{
		a->walls[Maze::CellWallDirs::right] = false;
		b->walls[Maze::CellWallDirs::left] = false;
	}

	int y = a->y - b->y;
	if (y == 1)
	{
		a->walls[Maze::CellWallDirs::top] = false;
		b->walls[Maze::CellWallDirs::bottom] = false;
	}
	else if (y == -1)
	{
		a->walls[Maze::CellWallDirs::bottom] = false;
		b->walls[Maze::CellWallDirs::top] = false;
	}
}

Maze::Cell* Maze::getRandUnvisitedNeighbourAt(const int& x, const int& y)
{
	std::vector<Cell*> neighbours;

	Cell* top    = y > 0              ? grid[x     + (y - 1) * cols] : nullptr;
	Cell* right  = x < this->cols - 1 ? grid[x + 1 +  y      * cols] : nullptr;
	Cell* bottom = y < this->rows - 1 ? grid[x     + (y + 1) * cols] : nullptr;
	Cell* left   = x > 0              ? grid[x - 1 +  y      * cols] : nullptr;

	if (top && !top->visited)       neighbours.push_back(top);
	if (right && !right->visited)   neighbours.push_back(right);
	if (bottom && !bottom->visited) neighbours.push_back(bottom);
	if (left && !left->visited)     neighbours.push_back(left);

	if (!neighbours.empty())
	{
		GRand r;
		int index = r.i((int)neighbours.size());
		return neighbours[index];
	}

	return nullptr;
}

