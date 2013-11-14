#include <iostream>
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
std::string toLetter(int x)
{
    return "a";
}

int toInt(std::string a)
{
    return 1;
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

std::ostream & operator<< (std::ostream & ofs, Position const & p)
{
    ofs << p.getX() << "-" << p.getY();
    return ofs;
}
