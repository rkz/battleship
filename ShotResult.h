/*
 * ShotResult.h
 *
 * ShotResult représente le résultat d'un coup sur une grille.
 */

#ifndef SHOTRESULT_H_
#define SHOTRESULT_H_

class ShotResult
{
private:
    bool winningShot;
    
public:
	ShotResult();
    bool isWinning();
};

#endif /* SHOTRESULT_H_ */
