#pragma once

#include <vector>
#include <stack>
#include "grand.h"

class Maze
{
private:
	int cols;
	int rows;

	class Cell
	{
	public:
		int x;
		int y;

		Cell(int xPos, int yPos);
	
		bool visited = false;
		bool walls[4] = {true, true, true, true};
	};

public:
	std::vector<Cell*> grid;

private:
	std::stack<Cell*> cellStack;
	Cell* currentCell;

	Cell* getRandUnvisitedNeighbourAt(const int& x, const int& y);
	void removeAdjacentCellWall(Cell* a, Cell* b);
	
	void generateMaze(const int& cols, const int& rows);

public:
	Maze(int cols = 10, int rows = 10);
	
	enum CellWallDirs
	{
		top = 0,
		right,
		bottom,
		left
	};

	~Maze();
};