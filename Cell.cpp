/*
 * Cell.cpp
 *
 *  Created on: 14 nov. 2013
 *      Author: raphael
 */

#include "Cell.h"

Cell::Cell(Position& _position, CellStatus _status)
	: position(_position), status(_status)
{
}

Position& Cell::getPosition () const
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
		case SINK: return "sink";
	};
}

void Cell::setStatus (CellStatus _status)
{
	status = _status;
}
