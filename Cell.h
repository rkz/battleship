/*
 * Cell.h
 *
 * Une Cell contient le statut d'une case du jeu à un instant t.
 */

#ifndef CELL_H_
#define CELL_H_

#include <string>
#include "Position.h"

enum CellStatus
{
	UNKNOWN = 0, // pas encore de tir
	WATER = 1, // à l'eau (pas de bateau)
	TOUCH = 2, // touché (mais pas coulé)
	SINK = 3 // coulé
};

class Cell
{
private:
	Position position;
	CellStatus status;

public:
	Cell(Position position, CellStatus status = UNKNOWN);

	Position getPosition () const;

	CellStatus getStatus () const;
	std::string getStatusAsString () const;
	void setStatus (CellStatus);

};

#endif /* CELL_H_ */
