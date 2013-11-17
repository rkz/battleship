/*
 * Ship.cpp
 *
 *  Created on: 17 nov. 2013
 *      Author: benjamin
 */
#include "Cell.h"
#include "Ship.h"

using namespace std;

Ship::Ship(vector<Cell*> _cells, string _name)
: cells(_cells), name(_name)
{
}

bool Ship::isSunk() const {

    for(unsigned int i = 0; i < cells.size(); i++){
        if(cells[i]->getStatus() != TOUCH)
            return false;
    }
    return true;
}

bool Ship::isTouched() const {

    for(unsigned int i = 0; i < cells.size(); i++){
        if(cells[i]->getStatus() == TOUCH)
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

