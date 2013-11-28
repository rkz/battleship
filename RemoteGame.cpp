/*
 * RemoteGame.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: raphael
 */

#include "RemoteGame.h"

#include <sstream>

using namespace std;

RemoteGame::RemoteGame(boost::asio::io_service& _io, std::string _host, int _port, LocalPlayer* _player)
	: io(_io), host(_host), port(_port), player(_player)
{
}

RemoteGame::~RemoteGame()
{

}

void RemoteGame::run()
{
	try {
		tcp::socket socket(io);

		// (conversion du numéro de port en chaîne)
		std::ostringstream stream;
		stream << port;

		tcp::resolver resolver(io);
		tcp::resolver::query query(host.c_str(), stream.str().c_str());
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Ouvrir la connexion
		boost::asio::connect(socket, endpoint_iterator);
		cout << "Connected to server at " << host << "." << endl;
	}
	catch (std::exception& e) {
		cout << "Error - uncaught (network?) exception: " << e.what() << endl;
	}
}
