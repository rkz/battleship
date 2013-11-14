/*
 * Position.h
 *
 *
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <ostream>

class Position {

private:
	int x;
	int y;

public:
	Position(int x, int y); // Attention ne pas initialiser de position vides

	int getX() const;
	void setX(int x);

	int getY() const;
	void setY(int y);
};

std::ostream & operator<<(std::ostream & ofs, Position const & p);

#endif /* POSITION_H_ */
