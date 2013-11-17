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
	if (isPositionValid(position))
		return (&grid[position.getX()][position.getY()]);
	else
		return 0;
}

bool Grid::isPositionValid(Position position)
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
		cells.push_back(getCell(Position(x + i*dx, y + i*dy)));

	// Ajouter le bateau à la grille
	ships.push_back(Ship(cells, name));
	return true;
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
