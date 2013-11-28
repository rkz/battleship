/*
 * Cell.cpp
 *
 *  Created on: 14 nov. 2013
 *      Author: raphael
 */

#include "Cell.h"

Cell::Cell(Position _position, CellStatus _status)
	: position(_position), status(_status)
{
}

bool Cell::isEqual(Cell cell_to_compare) const
{
    return position == cell_to_compare.position
        && status == cell_to_compare.status;
}

Position Cell::getPosition () const
{
	return position;
}

CellStatus Cell::getStatus () const
{
	return status;
}

std::string Cell::getStatusAsString () const
{
	switch (status) {
		case UNKNOWN: return "unknown";
		case WATER: return "water";
		case TOUCH: return "touch";
		default: return "";
	};
}

void Cell::setStatus (CellStatus _status)
{
	status = _status;
}

bool operator== (Cell const& c1, Cell const& c2)
{
    return c1.isEqual(c2);
}