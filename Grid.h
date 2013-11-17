#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include "Cell.h"

class Grid
{
private:
	int size;
	std::vector < std::vector<Cell> > grid;
	
public:
	Grid(int _size);
	Cell getCell(int x, int y);
	
};

#endif