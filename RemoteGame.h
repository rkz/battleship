/*
 * RemoteGame.h
 *
 * Communique avec le serveur de jeu et contrôle un LocalPlayer en conséquence.
 */

#ifndef REMOTEGAME_H_
#define REMOTEGAME_H_

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "LocalPlayer.h"
#include "Asio_helper.h"

using boost::asio::ip::tcp;

class RemoteGame
{
public:
	RemoteGame(boost::asio::io_service& io, std::string host, int port, LocalPlayer* player);
	~RemoteGame();

	// Connects to the server and starts the game
	void run();
    
    void initFleet();
	std::string getTargetGrid();
	std::string play(Grid* targetGrid);
	std::string shoot(Position p);
	void showResult(ShotResult sr);
    std::string getName() const;
    std::string getGrid() const;
    void signature() const;
    void finalView(std::string ennemyName, Grid* ennemyGrid) const;

private:
	boost::asio::io_service& io;

	std::string host;
	int port;

	LocalPlayer* player;
};

#endif /* REMOTEGAME_H_ */
