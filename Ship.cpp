#include "Ship.h"

#include <cassert>
using namespace std;

#include "Cell.h"

Ship::Ship(vector<Cell*> _cells, string _name)
: cells(_cells), name(_name)
{
	// Vérifier que tous les pointeurs Cell* sont non nuls
	for (int i = 0; i < cells.size(); i++)
		assert(cells[i] != 0);
}

bool Ship::isEqual(Ship ship_to_compare) const
{
    bool sameCells = true;
    for (int i=0; i < cells.size(); i++)
    {
        sameCells &= (*cells[i] == *ship_to_compare.cells[i]);
    }
        return sameCells && name == ship_to_compare.name;
}

bool Ship::isSunk() const
{
    for (unsigned int i = 0; i < cells.size(); i++) {
        if (cells[i]->getStatus() != TOUCH)
            return false;
    }

    return true;
}

bool Ship::isTouched() const
{
    for (unsigned int i = 0; i < cells.size(); i++) {
        if (cells[i]->getStatus() == TOUCH)
            return true;
    }

    return false;
}

std::vector<Cell*> Ship::getCells() const
{
    return cells;
}

std::string Ship::getName() const
{
    return name;
}

bool operator== (Ship const& s1, Ship const& s2)
{
    return s1.isEqual(s2);
}
