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
	Grid (int _size); // Constructeur
	Grid (Grid const& grid_to_copy); // Constructeur de copie
	int getSize () const;
	Cell* getCell (Position position);
	bool isPositionValid (Position position);
	bool addShip (Position position, Direction direction, int length, std::string name);
	Grid getTargetGrid ();
	
};

std::ostream & operator<< (std::ostream & ofs, Grid& g);

#endif
