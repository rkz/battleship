#include <iostream>
using namespace std;

#include "Position.h"
#include "Cell.h"

int main ()
{
	// Tests de positions
	Position p(1, 2);
	Position q(1, 2);
	Position z("C2");
    cout << z.getX() << "," << z.getY() << endl;
	cout << z << endl << q;

	return 0;
}
