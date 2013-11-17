#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Position.h"

Position::Position(int _x, int _y) : x(_x), y(_y)
{

}

Position::Position(std::string pos)
{
    x = toInt(pos[0]);
    y = pos[1] - '1';
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

// Fonctions privées
char Position::toLetter(int x)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet.at(x);
}

int Position::toInt(char a)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet.find_first_of(a);
}

std::string Position::toString() const
{
    std::ostringstream oss;
    oss << Position::toLetter(x) << y+1;

    return oss.str();
}

// Opérateurs
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
