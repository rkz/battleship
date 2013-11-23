#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Position.h"
#include <stdexcept>

Position::Position(int _x, int _y) : x(_x), y(_y)
{
}

Position::Position(std::string pos)
{
    if (pos.length() < 2 || pos.length() > 3) throw InvalidPositionString(pos);

    try {
		x = toInt(pos[0]);
		y = numberToInt(pos.substr(1)) - 1;

		if (x > 25 || y > 25) throw InvalidPositionString(pos);
    }
    catch (std::invalid_argument&) {
    	throw InvalidPositionString(pos);
    }
}

Position::Position(const Position& other) : x(other.x), y(other.y)
{
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

char Position::toLetter(int x)
{
	if (x < 0 || x > 25) throw std::invalid_argument("x");

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet.at(x);
}

int Position::toInt(char a)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int pos = alphabet.find_first_of(a);

    if (pos != std::string::npos) return pos;
    else throw std::invalid_argument("a");
}

int Position::numberToInt(std::string numberString)
{
	std::istringstream is(numberString);
	int n = 0;
	is >> n;

	if (n != 0) return n;
	else throw std::invalid_argument("numberString");
}

std::string Position::toString() const
{
    std::ostringstream oss;
    oss << Position::toLetter(x) << y+1;

    return oss.str();
}

bool operator==(Position const& a, Position const& b)
{
    if (a.getX() == b.getX() && a.getY() == b.getY())
        return true;
    else
        return false;
}

bool operator!=(Position const& a, Position const& b)
{
    if (a.getX() != b.getX() || a.getY() != b.getY())
        return true;
    else
        return false;
}

std::ostream & operator<<(std::ostream & ofs, Position const& p)
{
    ofs << p.toString();
    return ofs;
}
