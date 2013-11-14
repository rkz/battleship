/*
 * Position.h
 *
 *
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <ostream>

class Position
{
private:
	int x;
	int y;
	static char toLetter(int x);
	static int toInt(char a);

public:
	Position(int x, int y); // Attention ne pas initialiser de position vides

	int getX() const;
	int getY() const;
	std::string toString() const;
};

bool operator==(Position const& a, Position const& b);
bool operator!=(Position const& a, Position const& b);
std::ostream & operator<<(std::ostream & ofs, Position const& p);

#endif /* POSITION_H_ */
