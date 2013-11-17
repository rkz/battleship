#include "Grid.h"

Grid::Grid (int _size)
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

Grid::Grid (Grid const& grid_to_copy)
	: size (grid_to_copy.size), grid (grid_to_copy.grid), ships (grid_to_copy.ships)
{
}

int Grid::getSize () const
{
	return size;
}

Cell* Grid::getCell (Position position)
{
	if (isPositionValid(position))
		return (&grid[position.getX()][position.getY()]);
	else
		return 0;
}

bool Grid::isPositionValid (Position position)
{
	int x = position.getX(), y = position.getY();
	return (x >= 0 && x < size && y >= 0 && y < size);
}

bool Grid::addShip (Position position, Direction direction, int length, std::string name)
{
	int x = position.getX();
	int y = position.getY();
	int dx = 0;
	int dy = 0;

	if (!isPositionValid (position) || length <= 0)
		return false;

	// Selon la direction, définir la direction sur laquelle itérer (dx et dy) et
	// vérifier que le bateau ne va pas dépasser de la grille
	switch (direction) {
		case HORIZONTAL:
			if (y+length > size) return false;
			dy = 1;
			break;
		case VERTICAL:
			if (x+length > size) return false;
			dx = 1;
			break;
		default:
			return false;
	}

	// Créer la liste de Cells du bateau
	std::vector<Cell*> cells;
	for (int i = 0; i < length; i++)
	{
		int curr_x = x + i*dx;
		int curr_y = y + i*dy;
		if (getShipAtPosition(Position(curr_x,curr_y)))
			return false;
		cells.push_back(getCell(Position(curr_x, curr_y)));
	}

	// Ajouter le bateau à la grille
	ships.push_back(Ship(cells, name));
	return true;
}

Grid Grid::getTargetGrid ()
{
	int i = 0;
	Grid target = *this;
	while (i < target.ships.size()) {
		if (!target.ships[i].isSunk())
			target.ships.erase(target.ships.begin() + i);
		else
			i++;
	}
	return target;
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
