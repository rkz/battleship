#include "Grid.h"
#include "ShotResult.h"
#include<sstream>

#include <cassert>
#include <cmath>

Grid::Grid (int _size)
	: size(_size)
{
	for (int i = 0; i < size; i++)
	{
		std::vector<Cell> v;
		for (int j = 0; j < size; j++)
			v.push_back(Cell(Position(i,j)));

		grid.push_back(v);
	}
}

Grid::Grid (Grid const& grid_to_copy)
	: size(grid_to_copy.size), grid(grid_to_copy.grid), ships(grid_to_copy.ships)
{
}

// convertir un entier en string
std::string convert_itos(int a)
{
    std::ostringstream oss;
    oss << a;
    return oss.str();
}

// convertit une string en entier, renvoie 0 en cas d'erreur de conversion
int convert_stoi(std::string str)
{
    int res;
    std::istringstream stream(str);
    if (!(stream >> res))
        res = 0;
    return res;
}

std::string Grid::serialize ()
{
	/**
	 * Format de sérialisation des Grid :
	 *  <size>/<cells>/<ships>
	 *
	 * avec :
	 *  <size> : taille de la grille sur 1 ou 2 chiffres
	 *  <cells> : statuts des cellules (U, W ou T)
	 *  <ships> : sérialisation des bateaux, séparés par des virgules
	 *
	 * Exemple : 3/UUUUUUUUU/A1H3a,A3H2d
	 */

    std::string serial = convert_itos(size) + '/';

    // Statuts des cellules
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            switch (getCell(Position(j, i))->getStatus()) {
                case UNKNOWN:
                    serial += 'U';
                    break;
                case WATER:
                    serial += 'W';
                    break;
                case TOUCH:
                    serial += 'T';
                    break;
                default:
                	assert(false);
                    break;
            }
        }
    }

    serial += '/';

    // Bateaux
    // Remarque : il faut que la longueur du bateau soit >= 2 et <= 9
    for (int k = 0; k < ships.size(); k++)
    {
        std::vector<Cell*> cells = ships[k].getCells();
        assert(cells.size() >= 2);
        assert(cells.size() <= 9);

        Position firstCellPos = cells[0]->getPosition();

        // Première case (écrire la position sur 3 lettres)
        std::string p = firstCellPos.toString();
        if (p.size() == 2) p += ".";
        serial += p;

        // Direction
        if (cells[1]->getPosition().getX() == firstCellPos.getX())
            serial += 'V';
        else
            serial += 'H';

        // Taille
        serial += convert_itos(cells.size());

        // Première lettre du nom
        serial += ships[k].getName().at(0);

        if (k < ships.size() - 1)
            serial += ',';
    }

    return serial;
}

Grid Grid::unserialize (std::string serial)
{
	// Taille : entier avant le premier "/"
	int gridSize = convert_stoi(serial.substr(0, serial.find('/')));

	// Extraire les chaînes des cellules et des bateaux
	int cellsPartBegin = serial.find('/') + 1;
	int cellsPartSize = gridSize*gridSize;
	int shipsPartBegin = serial.find('/', cellsPartBegin + 1) + 1;
	std::string cellsPart = serial.substr(cellsPartBegin, cellsPartSize);
	std::string shipsPart = serial.substr(shipsPartBegin);

	// Construire la grille
	Grid grid(gridSize);
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			Cell* cell = grid.getCell(Position(j, i));
			switch (cellsPart.at(i*gridSize + j)) {
				case 'U':
					cell->setStatus(UNKNOWN);
					break;
				case 'W':
					cell->setStatus(WATER);
					break;
				case 'T':
					cell->setStatus(TOUCH);
					break;
				default:
					assert(false);
					break;
			}
		}
	}

	// Placer les bateaux
	while (shipsPart.size() > 0)
    {
		// Position
		std::string posString = shipsPart.substr(0, 3);
		if (posString.at(2) == '.') posString = posString.substr(0, 2);
		Position topLeft = Position(posString);

		// Direction
        Direction direction = HORIZONTAL;
        if (shipsPart.at(3) == 'H') direction = HORIZONTAL;
        else if (shipsPart.at(3) == 'V') direction = VERTICAL;
        else assert(false);

        // Longueur
        int length = convert_stoi(shipsPart.substr(4, 1));

        // Nom
        std::string name;
        switch (shipsPart.at(5)) {
            case 'a':
                name = "aircraft carrier";
                break;
            case 'b':
                name = "battleship";
                break;
            case 's':
                name = "submarine";
                break;
            case 'd':
                name = "destroyer";
                break;
            case 'p':
                name = "patrol boat";
                break;
            default:
            	assert(false);
                break;
        }

        grid.addShip(topLeft, direction, length, name);

        // Enlever le premier bateau de shipsPart
        int commaPos = shipsPart.find(',');

        if (commaPos != std::string::npos) shipsPart = shipsPart.substr(commaPos + 1);
        else if (shipsPart.size() == 6) shipsPart = "";
        else assert(false);
    }

    return grid;
}

int Grid::getSize () const
{
	return size;
}

bool Grid::isEqual (Grid grid_to_compare) const
{
    return size == grid_to_compare.size
        && grid == grid_to_compare.grid
        && ships == grid_to_compare.ships;
}

Cell* Grid::getCell (Position position)
{
	if (isPositionValid(position))
		return &(grid[position.getX()][position.getY()]);
	else
		throw OutOfGridException(position);
}

bool Grid::isPositionValid (Position position)
{
	int x = position.getX();
	int y = position.getY();
	return (x >= 0) && (x < size) && (y >= 0) && (y < size);
}

Ship* Grid::addShip (Position position, Direction direction, int length, std::string name = "")
{
	int x = position.getX();
	int y = position.getY();
	int dx = 0;
	int dy = 0;

	if (!isPositionValid (position) || length <= 0)
		throw ShipOutOfGridException();

	// Selon la direction, définir la direction sur laquelle itérer (dx et dy) et
	// vérifier que le bateau ne va pas dépasser de la grille
	switch (direction) {
		case HORIZONTAL:
			if (x+length > size) throw ShipOutOfGridException();
			dx = 1;
			break;
		case VERTICAL:
			if (y+length > size) throw ShipOutOfGridException();
			dy = 1;
			break;
		default:
			assert(false);
			return 0;
	}

	// Créer la liste de Cells du bateau
	std::vector<Cell*> cells;
	for (int i = 0; i < length; i++)
	{
		Position pos(x + i*dx, y + i*dy);

		if (getShipAtPosition(pos))
			throw ShipCollisionException();

        if (getShipNearPosition(pos))
            throw ShipNearbyException();

		Cell* c = getCell(pos);
		cells.push_back(c);
	}

	// Ajouter le bateau à la grille et renvoyer un pointeur
	ships.push_back(Ship(cells, name));
	return &ships[ships.size() - 1];
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

std::ostream & operator<<(std::ostream & ofs, Grid &g)
{
	int g_size = g.getSize();
	ofs << "   ";
	for (int k(0); k < g_size; k++)
		ofs << char (k+65) << " ";
	ofs << std::endl;
    for (int i(0); i < g_size; i++)
	{
		ofs << i+1 << ((i < 9) ? "  " : " ");

		for (int j = 0; j < g_size; j++)
        {
            Position pos(j,i);
			assert(g.getCell(pos) != 0);
			if (g.getShipAtPosition(pos))
            {
                switch (g.getCell(pos)->getStatus()) {
                    case UNKNOWN:
                        ofs << "X ";
                        break;
                    case WATER:
                        assert(false);
                        break;
                    case TOUCH:
                        if(g.getShipAtPosition(pos)->isSunk())
                            ofs << "O ";
                        else
                            ofs << "+ ";
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch (g.getCell(pos)->getStatus()) {
                    case UNKNOWN:
                        ofs << ". ";
                        break;
                    case WATER:
                        ofs << "  ";
                        break;
                    case TOUCH:
                        ofs << "+ ";
                        break;
                    default:
                        break;
                }
            }
		}
		ofs << std::endl;
	}
    return ofs;
}

bool operator== (Grid const& g1, Grid const& g2)
{
    return g1.isEqual(g2);
}

Ship* Grid::getShipAtPosition (Position position)
{
	for (int i = 0; i < ships.size(); i++) {
		Ship* ship = &(ships[i]);
		std::vector<Cell*> shipCells = ship->getCells();
		for (int j = 0; j < shipCells.size(); j++) {
			if (shipCells[j]->getPosition() == position) return ship;
		}
	}

	return 0;
}

bool Grid::getShipNearPosition( Position position)
{
    std::vector<Position> adjacentPos = position.adjacent();
    for(int i = 0; i < 4; i++) {
        if (isPositionValid( adjacentPos[i])) if (getShipAtPosition(adjacentPos[i])) return true;
    }
    return false;
    }


bool Grid::allShipsSunk ()
{
    for (unsigned int i = 0; i < ships.size(); i++) {
        if (!ships[i].isSunk())
            return false;
    }
    return true;
}

ShotResult* Grid::shoot (Position p)
{
    Cell* targetCell = getCell(p);
    if (targetCell->getStatus() != UNKNOWN)
        return new ShotResult (ShotResult(getTargetGrid(), ALREADY_PLAYED, false));

    Ship* targetShip = getShipAtPosition(p);
    if (!targetShip)
    {
        targetCell->setStatus(WATER);
        return new ShotResult (ShotResult(getTargetGrid(), MISSED, false));
    }

    targetCell->setStatus(TOUCH);
    if (targetShip->isSunk())
        return new ShotResult (ShotResult(getTargetGrid(), SUNK, allShipsSunk()));
    else
        return new ShotResult (ShotResult(getTargetGrid(), TOUCHED, false));
}

int Grid::destructionPercentage()
{
    int nbTouchedCells = 0;
    int nbCells = 0;
    for (int i = 0; i < ships.size(); i++) {
        std::vector<Cell*> cells = ships[i].getCells();
        for (int j = 0; j < cells.size(); j++){
            nbCells++;
            if (cells[j]->getStatus() == TOUCH)
                nbTouchedCells ++;
        }
    }
    return ceil(nbTouchedCells * 100 / nbCells);
}
