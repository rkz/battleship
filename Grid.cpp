#include "Grid.h"

Grid::Grid(int _size)
	: size(_size)
{
	for (int i(0); i < _size; i++)
	{
		std::vector <Cell> v;
		for (int j(0); j < _size; j++)
			v.push_back (Cell(Position(i,j)));
		grid.push_back (v);
	}
}

Cell Grid::getCell(int x, int y)
{
	return grid[x][y];
}