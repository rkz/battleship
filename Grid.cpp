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

Cell Grid::getCell(int x, int y) const
{
	return grid[x][y];
}

std::ostream & operator<<(std::ostream & ofs, Grid const& g)
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
			switch (g.getCell(i,j).getStatus()) {
				case UNKNOWN: ofs << ". ";
					break;
				case WATER: ofs << "  ";
					break;
				case TOUCH: ofs << "+ ";
					break;
				case SINK: ofs << "X ";
					break;
				default: ofs << "";
					break;
			}
		}
		ofs << std::endl;
	}
    return ofs;
}