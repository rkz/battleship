#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include "Cell.h"
#include "Ship.h"

enum Direction
{
	HORIZONTAL = 0,
	VERTICAL = 1
};

class Grid
{
private:
	int size;
	std::vector < std::vector<Cell> > grid;
	std::vector <Ship> ship;
	
public:
	Grid(int _size);
	int getSize() const;
	Cell getCell(int x, int y) const;
	bool isPositionValid(Position position);
	bool addShip (Position position, Direction direction, int length, std::string name);
	
};

std::ostream & operator<<(std::ostream & ofs, Grid const& g);

#endif