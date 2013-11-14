#include <iostream>
using namespace std;

#include "Position.h"
#include "Cell.h"

int main ()
{
	cout << "Hello, world!" << endl;

	// Tests de positions
	Position p(1, 2);
	cout << p.getX() << ", " << p.getY() << endl;
	cout << p << endl;

	// Tests de Cell
	Cell c(p, SINK);
	cout << c.getPosition() << endl;
	cout << c.getStatusAsString() << endl;

	return 0;
}
