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
	LocalPlayer(std::string name);
	~LocalPlayer();

	void initFleet();
	Grid* getTargetGrid();
	Position play(Grid* targetGrid);
	ShotResult shoot(Position p);
	void showResult(ShotResult sr);
    std::string getName() const;
    Grid* getGrid() const;
    void signature() const;
    void finalView(std::string ennemyName, Grid* ennemyGrid) const;

private:
	void printInitFleetTitle();
    bool placeShip(std::string name, int length);
    std::string name;

};

#endif /* LOCALPLAYER_H_ */
