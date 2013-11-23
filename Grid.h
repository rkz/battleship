#ifndef GRID_H_
#define GRID_H_

#include <vector>
#include <exception>

#include "Cell.h"
#include "Ship.h"

enum Direction
{
	HORIZONTAL = 0,
	VERTICAL = 1
};

class ShotResult;

class Grid
{
private:
	int size;
	std::vector< std::vector<Cell> > grid;
    std::vector<Ship> ships;

public:
	// Construction d'une grille N*N de taille donnée, toutes cases UNKNOWN
    Grid (int N);

    // Copie d'une grille
	Grid (Grid const& grid_to_copy);

	// Renvoie la taille de la grille
	int getSize () const;

	// Renvoie true si 'position' est sur la grille, false sinon
	bool isPositionValid (Position position);

	// Renvoie un pointeur vers la cellule se trouvant à la position donnée
	// Lance une exception si la position est hors grille
	Cell* getCell (Position position);

	// Ajoute un bateau à la grille, paramétré par la position de la première case,
	// une direction (HORIZONTAL ou VERTICAL), une longueur et un nom.
	// Renvoie un pointeur vers le bateau s'il a été ajouté, sinon lève une exception
	// ShipCreationExeception (par exemple en cas de dépassement de grille)
	Ship* addShip (Position position, Direction direction, int length, std::string name);

	// Renvoie un pointeur vers le bateau présent à une position donnée, ou un pointeur
	// nul si aucun bateau ne s'y trouve (cellule vide ou position hors grille)
	Ship* getShipAtPosition (Position);
    
    // Renvoie true si tous les bateaux sont coulés (partie perdue)
    bool allShipsSunk ();

	// Copie la grille en une "target grid", vue de la grille destinée à l'adversaire :
	// - les statuts des Cells sont conservés
	// - les bateaux sont supprimés sauf ceux qui sont coulés, i.e. dont toutes les Cells sont
	//   en statut TOUCH
	Grid getTargetGrid ();
    
    // A partir d'une position de tir, met à jour la Cell cible et calcule le ShoResult associé
    ShotResult* shoot (Position p);

};

// Affichage d'une grille sur un flux de sortie pour l'adversaire
std::ostream & operator<< (std::ostream & ofs, Grid& g);


/*
 * OutOfGridException : lancée lorsqu'une cellule est en dehors de la grille
 */
class OutOfGridException : public std::exception
{
	Position position;

public:
	OutOfGridException (Position p) : position(p) {}

	Position getPosition () { return position; }
};


/*
 * ShipOutOfGridException : lancée lorsqu'un bateau en cours de création dépasse de la grille
 */
class ShipOutOfGridException : public std::exception
{
public:
	ShipOutOfGridException () {}
};


/*
 * ShipCollisionException : lancée lorsqu'un bateau en cours de création recoupe un autre bateau
 */
class ShipCollisionException : public std::exception
{
public:
	ShipCollisionException () {}
};

#endif
