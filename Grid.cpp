#include "Grid.h"
#include "ShotResult.h"

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

std::string Grid::stringFromGrid () const
{
    std::string serial = std::to_string(size) + '/';
    
    for (int i=0; i < size; i++)
    {
        for (int j=0; j < size; j++)
        {
            switch (grid[j][i].getStatus()) {
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
                    break;
            }
        }
    }
    
    serial += '/';
    
    for (int k=0; k < ships.size(); k++)
    {
        std::vector<Cell*> cells = ships[k].getCells();
        Position firstCellPos = cells[k]->getPosition();
        serial += firstCellPos.toString();
        
        if (cells[1]->getPosition().getX() == firstCellPos.getX())
            serial += 'V';
        else
            serial += 'H';
        
        serial += std::to_string(cells.size());
        serial += (ships[k].getName())[0];
        if (k < ships.size() - 1)
            serial += ',';
    }
    
    return serial;
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
			return false;
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

Grid gridFromString (std::string serial)
{
    int deserialSize = std::stoi(serial);
    Grid deserialGrid = Grid(deserialSize);
    int currentChar;
    
    if (deserialSize < 10)
        currentChar = 2;
    else
        currentChar = 3;
    assert(serial[currentChar-1] == '/');
    
    for (int i=0; i < deserialSize; i++)
    {
        for (int j=0; j < deserialSize; j++)
        {
            Cell* cell = deserialGrid.getCell(Position(j,i));
            switch (serial[currentChar]) {
                case 'U':
                    cell -> setStatus(UNKNOWN);
                    break;
                case 'W':
                    cell -> setStatus(WATER);
                    break;
                case 'T':
                    cell -> setStatus(TOUCH);
                    break;
                default:
                    break;
            }
            
            currentChar++;
        }
    }
    
    assert(serial[currentChar] == '/');
    std::string serialShips = serial.substr(currentChar-1);
    
    while (serialShips.size() > 6)
    {
        Direction direction = HORIZONTAL;
        if (serialShips[4] == 'V')
            direction = VERTICAL;
        std::string name;
        switch (serialShips[6]) {
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
                break;
        }
        
        deserialGrid.addShip(Position(serialShips.substr(2,2)), direction, std::stoi (serialShips.substr(5)), name);
        serialShips = serialShips.substr(6);
    }
    
    return deserialGrid;
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
