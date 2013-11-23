/*
 * ShotResult.h
 *
 * ShotResult représente le résultat d'un coup sur une grille.
 */

#ifndef SHOTRESULT_H_
#define SHOTRESULT_H_

#include <iostream>
#include <string>
#include "Grid.h"

enum Result
{
    MISSED = 0, // à l'eau (pas de bateau)
	TOUCHED = 1, // touché (mais pas coulé)
	SUNK = 2, // coulé
    ALREADY_PLAYED = 3 // position déjà jouée
};

class ShotResult
{
private:
    Grid targetGrid;
    Result result;
    bool winningShot;

public:
	ShotResult(Grid targetGrid, Result result, bool winningShot);
    bool isValid() const;
    bool isWinning() const;
    std::string getResultAsString() const;
    Grid* getTargetGrid () const;
};

#endif /* SHOTRESULT_H_ */
