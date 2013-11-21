#ifndef BATTLESHIP_BUILD_TESTS

#include <iostream>
#include <vector>
#include "Grid.h"

using namespace std;

int main ()
{

    Grid g(5);
    g.addShip(Position(2,1), HORIZONTAL, 3, "JCVD");
    g.getCell(Position(2,1))->setStatus(TOUCH); g.getCell(Position(3,1))->setStatus(TOUCH); g.getCell(Position(4,1))->setStatus(TOUCH);
    g.getCell(Position(3,3))->setStatus(WATER);
    cout <<  g;
	return 0;
}

#endif
