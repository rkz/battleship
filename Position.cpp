#include <iostream>
#include <sstream>
#include "Position.h"

Position::Position(int _x, int _y) : x(_x), y(_y)
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

// Fonctions privées
char Position::toLetter(int x)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet.at(x-1);
}

int Position::toInt(char a)
{
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet.find_first_of(a)+1;
}

std::string Position::toString() const
{
    std::ostringstream oss;
    oss << Position::toLetter(x) << y;

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
