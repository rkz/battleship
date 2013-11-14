#include <iostream>
using namespace std;

#include "Position.h"

int main ()
{
	// Tests de positions
	Position p(1, 2);
	Position q(1, 2);
	Position z(2,2);

	cout << (q != p) << endl << (z != q);

	return 0;
}
