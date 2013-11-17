#include "tests.h"

#include <iostream>
#include <vector>
using namespace std;

#include "Position.h"
#include "Cell.h"
#include "Ship.h"

void runTests ()
{
	testPosition();
	testShips();
}

void testPosition ()
{
	// Tests de positions
	Position p(1, 2);
	Position q(1, 2);
	cout << "p = " << p << " = " << p.getX() << "," << p.getY() << endl;
	cout << "q = " << q << " = " << q.getX() << "," << q.getY() << endl;
	cout << "p == q ? " << ((p == q) ? "oui" : "non") << endl;
}

void testShips ()
{
	vector<Cell*> cells;
	cells.push_back(new Cell(Position(1, 2)));
	cells.push_back(new Cell(Position(2, 2)));
	Ship myShip(cells, string("patrol boat"));
}
