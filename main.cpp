#include <iostream>
#include <vector>
using namespace std;

#include "Position.h"
#include "Cell.h"
#include "Ship.h"

int main ()
{
	// Tests de positions
	Position p(1, 2);
	Position q(1, 3);
	Position z("C2");
    cout << z.getX() << "," << z.getY() << endl;
	cout << z << endl << q;
	Cell c1(p);
	Cell c2(q);
	vector<Cell*> cells;
	cells.push_back(&c1);
	cells.push_back(&c2);
	string name("patrol boat");
	Ship myShip(cells, name);

	return 0;
}
