#include <iostream>
using namespace std;

#include "Position.h"

int main ()
{
	cout << "Hello, world!" << endl;

	// Tests de positions
	Position p(1, 2);
	cout << p.getX() << ", " << p.getY() << endl;
	cout << p << endl;

	return 0;
}
