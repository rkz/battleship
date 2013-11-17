/*
 * Ship.h
 *
 * Un ship est l'entité définie par le joueur en début de partie. Il contient des pointeurs vers des cellules.
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

    bool isSunk() const;
    bool isTouched() const;

    std::vector<Cell*> getCells() const;
    std::string getName() const;
};

#endif // SHIP_H_INCLUDED
