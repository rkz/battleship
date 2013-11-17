#include "Grid.h"

Grid::Grid(int _size)
	: size(_size)
{
	for (int i(0); i < _size; i++)
	{
		std::vector <Cell> v;
		for (int j(0); j < _size; j++)
			v.push_back (Cell(Position(i,j)));
		grid.push_back (v);
	}
}

int Grid::getSize() const
{
	return size;
}

Cell* Grid::getCell(Position position)
{
	return &(grid[position.getX()][position.getY()]);
}

bool Grid::isPositionValid(Position position)
{
	int x = position.getX(), y = position.getY();
	return (x >= 0 && x < size && y >= 0 && y < size);
}

bool Grid::addShip (Position position, Direction direction, int length, std::string name)
{
	int x = position.getX(), y = position.getY();
	if (isPositionValid (position)) {
		switch (direction) {
			case HORIZONTAL:
				if (y+length <= size) {
					std::vector <Cell*> cells;
					for (int j(0); j < length; j++)
					{
						Cell *p;
						p = &grid[x][y+j];
						cells.push_back (p);
					}
					ship.push_back (Ship(cells, name));
					return true;
				}
				else {
					return false;
				}
			case VERTICAL:
				if (x+length <= size) {
					std::vector <Cell*> cells;
					for (int i(0); i < length; i++)
					{
						Cell *p;
						p = &grid[x+i][y];
						cells.push_back (p);
					}
					ship.push_back (Ship(cells, name));
					return true;
				}
				else {
					return false;
				}
			default: return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream & operator<<(std::ostream & ofs, Grid& g)
{
	int g_size = g.getSize();
	ofs << "   ";
	for (int k(0); k < g_size; k++)
		ofs << char (k+65) << " ";
	ofs << std::endl;
    for (int i(0); i < g_size; i++)
	{
		if (i<9) {
			ofs << i+1 << "  ";
		}
		else {
			ofs << i+1 << " ";
		}
		for (int j(0); j < g_size; j++) {
			switch (g.getCell(Position(i,j))->getStatus()) {
				case UNKNOWN: ofs << ". ";
					break;
				case WATER: ofs << "  ";
					break;
				case TOUCH: ofs << "+ ";
					break;
				default: ofs << "";
					break;
			}
		}
		ofs << std::endl;
	}
    return ofs;
}

Ship* Grid::getShipAtPosition (Position position) const
{

}
