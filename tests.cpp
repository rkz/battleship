#include "tests.h"

#include <iostream>
#include <vector>
using namespace std;

#include "Position.h"
#include "Cell.h"
#include "Ship.h"
#include "Grid.h"

void runTests ()
{
	testPosition();
	testGrid();
	testAddShip();
	testShips();
	testShipSunk();
	testShipTouched();
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

void testGrid ()
{
	Grid g(10);
	cout << g << endl;
}

void testAddShip ()
{
	Grid g(5);
	bool test1 = g.addShip(Position(0,2), HORIZONTAL, 3, "Chantal");
	if (!test1) {
		cout << "Erreur dans le test 1" << endl;
	}
	bool test2 = g.addShip(Position(2,0), VERTICAL, 4, "Selier");
	if (test2) {
		cout << "Erreur dans le test 2" << endl;
	}
}

void testShips ()
{
	vector<Cell*> cells;
	cells.push_back(new Cell(Position(1, 2)));
	cells.push_back(new Cell(Position(2, 2)));
	Ship myShip(cells, string("patrol boat"));
}

void testShipSunk ()
{
    cout << endl << "test de Ship.isSunk" << endl;
    Position x(1,1), y(1,2);
    Cell p(x,TOUCH), q(y);
    vector<Cell*> cells;
    cells.push_back(&p); cells.push_back(&q);
    Ship myShip(cells, "patrol boat");
    if(myShip.isSunk()==true) { cout<< "true" << endl; }
    else { cout << "false" << endl; }
}

void testShipTouched ()
{
    cout << endl << "test de Ship.isTouched" << endl;
    Position x(1,1), y(1,2);
    Cell p(x), q(y);
    vector<Cell*> cells;
    cells.push_back(&p); cells.push_back(&q);
    Ship myShip(cells, "patrol boat");
    if(myShip.isTouched()==true) { cout<< "true" << endl; }
    else { cout << "false" << endl; }
}
