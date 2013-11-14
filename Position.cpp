#include "Position.h"

#include <iostream>

Position::Position(int _x, int _y)
{
	setX(_x);
	setY(_y);
}

int Position::getX() const
{
	return x;
}

void Position::setX(int x)
{
	this->x = x;
}

int Position::getY() const
{
	return y;
}

void Position::setY(int y)
{
	this->y = y;
}

std::ostream & operator<< (std::ostream & ofs, Position const & p)
{
    ofs << p.getX() << "-" << p.getY();
    return ofs;
}
