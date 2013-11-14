#include <iostream>
using namespace std;

#include "Position.h"
#include "Cell.h"

int main ()
{
	// Tests de positions
	Position p(1, 2);
	Position q(1, 2);
	Position z(2,2);

	cout << z;

	// Tests de Cell
	Cell c(p, SINK);
	cout << c.getPosition() << endl;
	cout << c.getStatusAsString() << endl;

	return 0;
}
