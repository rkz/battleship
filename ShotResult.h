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

    Result getResult() const;

    bool isWinning() const;

    // Affichage "human-readable" du résultat
    std::string getResultAsString() const;

    Grid* getTargetGrid () const;

    // Sérialisation d'un ShotResult en string
    std::string serialize () const;

    // Désérialisation d'une string en ShotResult
    static ShotResult unserialize(std::string);
};


#endif /* SHOTRESULT_H_ */
