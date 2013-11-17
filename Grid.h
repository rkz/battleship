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
	std::vector <Ship> ships;
	
public:
	Grid(int _size);
	int getSize() const;
	Cell* getCell(Position position);
	bool isPositionValid(Position position);
	bool addShip (Position position, Direction direction, int length, std::string name);
	
};

std::ostream & operator<<(std::ostream & ofs, Grid& g);

#endif
