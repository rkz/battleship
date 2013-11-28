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

using boost::asio::ip::tcp;

class RemoteGame
{
public:
	RemoteGame(boost::asio::io_service& io, std::string host, int port, LocalPlayer* player);
	~RemoteGame();

	// Connects to the server and starts the game
	void run();

private:
	boost::asio::io_service& io;

	std::string host;
	int port;

	LocalPlayer* player;
};

#endif /* REMOTEGAME_H_ */
