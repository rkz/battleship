/*
 * LocalPlayer.h
 *
 * LocalPlayer implémente AbstractPlayer pour un joueur local.
 */

#ifndef LOCALPLAYER_H_
#define LOCALPLAYER_H_

#include "AbstractPlayer.h"

class LocalPlayer: public AbstractPlayer
{
public:
	LocalPlayer();
	~LocalPlayer();

	void initFleet();
	Grid* getTargetGrid();
	Position play(Grid* targetGrid);
	ShotResult shoot(Position p);
	void showResult(ShotResult sr);

private:
    bool placeShip(std::string name, int length);
};

#endif /* LOCALPLAYER_H_ */
