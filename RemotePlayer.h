/*
 * RemotePlayer.h
 *
 * Implémente un AbstractPlayer faisant la communication avec le joueur via le réseau.
 */

#ifndef REMOTEPLAYER_H_
#define REMOTEPLAYER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "AbstractPlayer.h"

class RemotePlayer : public AbstractPlayer
{
public:
	RemotePlayer();
	~RemotePlayer();

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
    boost::asio::ip::tcp::socket* socket;

};

#endif /* REMOTEPLAYER_H_ */
