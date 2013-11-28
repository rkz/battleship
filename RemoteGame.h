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

class RemoteGame
{
public:
	RemoteGame(std::string host, LocalPlayer* player);
	~RemoteGame();

	// Connects to the server and starts the game
	void run();

private:
	boost::asio::ip::tcp::socket* socket;
	LocalPlayer* player;
};

#endif /* REMOTEGAME_H_ */
