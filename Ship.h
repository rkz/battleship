/*
 * Ship.h
 *
 * Un ship est l'entit� d�finie par le joueur en d�but de partie. Il contient des pointeurs vers des cellules.
 */

#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED
#include <vector>
#include "Cell.h"

class Ship
{
private:
    std::vector<Cell*>  cells;
    std::string name;
public:
    Ship(std::vector<Cell*> cells, std::string name);
    bool isSunk();
    bool isTouched();
    std::vector<Cell*> getCells();
};



#endif // SHIP_H_INCLUDED
