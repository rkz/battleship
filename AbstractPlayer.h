/*
 * AbstractPlayer.h
 *
 *
 */

#ifndef ABSTRACTPLAYER_H_
#define ABSTRACTPLAYER_H_

#include "Position.h"
#include "Grid.h"
#include "ShotResult.h"

class AbstractPlayer
{
protected:
    std::string name;
    Grid* grid;

public:
	virtual void initFleet() = 0;
	virtual Grid* getTargetGrid() = 0;
	virtual Position play(Grid* targetGrid) = 0;
	virtual ShotResult shoot(Position p) = 0;
	virtual void showResult(ShotResult sr) = 0;
	virtual void signature() const = 0;
	virtual void finalView(std::string ennemyName, Grid* ennemyGrid) const = 0;
	virtual std::string getName() const = 0;

	// pour l'affichage final des deux grilles, révelant au perdant la position effective des bateaux du vainqueur :
	virtual Grid* getGrid() const = 0;
};

#endif /* ABSTRACTPLAYER_H_ */
