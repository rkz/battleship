
#ifndef BATTLESHIP_BUILD_TESTS

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Game.h"
#include "RemoteGame.h"
#include "RemotePlayer.h"
#include "Grid.h"
#include "LocalPlayer.h"
#include <cstdlib>

using namespace std;

enum BattleshipMode
{
	LOCAL,
	NETWORK_CLIENT,
	NETWORK_SERVER
};

class UnknownMode : public exception {};

BattleshipMode getMode (int argc, char** argv)
{
	if (argc < 2) throw UnknownMode();
    
	string mode(argv[1]);
	if (mode == "local") return LOCAL;
	else if (mode == "client") return NETWORK_CLIENT;
	else if (mode == "server") return NETWORK_SERVER;
	else throw UnknownMode();
}

int main (int argc, char** argv)
{
	try
	{
		BattleshipMode mode = getMode(argc, argv);
        
		if (mode == LOCAL)
		{
			string name1, name2;
			cout << "Please type players' names." << endl << endl;
			cout << "Player 1: ";
			cin >> name1;
			cout << "Player 2: ";
			cin >> name2;
			cout << endl;
			system("pause");
            
			LocalPlayer* player1 = new LocalPlayer(name1);
			LocalPlayer* player2 = new LocalPlayer(name2);
            
			Game game = Game(player1, player2);
			game.run();
            
			delete player1;
			delete player2;
            
			return 0;
		}
        
		if (mode == NETWORK_CLIENT)
		{
			if (argc < 3) {
				cout << "Please provide the server's hostname or IP address as third argument." << endl;
				exit(1);
			}
			string hostname(argv[2]);
            
			string name;
			cout << "Please type your name: ";
			cin >> name;
			cout << endl;
            
			boost::asio::io_service io;
            
			LocalPlayer* player = new LocalPlayer(name);
			RemoteGame game(io, hostname, 1005, player);
            
			game.run();
            
			delete player;
            
			return 0;
		}
        
		if (mode == NETWORK_SERVER)
		{
			// Création du service principal et du résolveur.
            boost::asio::io_service ios;
            std::string ip_address = boost::asio::ip::host_name();
            std::cout << "Server running on IP: " << ip_address << std::endl;
            
            // Création de l'acceptor avec le port d'écoute 1005 et une adresse quelconque de type IPv4
            tcp::acceptor acceptor(ios, tcp::endpoint(tcp::v4(), 1005));
            
            // On attend la venue d'un client
            // Création d'une socket
            tcp::socket socket1(ios);
            
            // On accepte la connexion
            acceptor.accept(socket1);
            
            // On crée le RemotePlayer
            RemotePlayer player1 = RemotePlayer(&socket1);
            std::cout << "Player 1 connected" << std::endl;
            
            // Idem avec le deuxième client
            tcp::socket socket2(ios);
            acceptor.accept(socket2);
            RemotePlayer player2 = RemotePlayer(&socket2);
            std::cout << "Player 2 connected" << std::endl;
            
            Game game = Game(&player1, &player2);
            game.run();
            
            return 0;
		}
	}
	catch (UnknownMode&)
	{
		cout << "Usage: battleship <mode>" << endl << endl
        << "Supported modes:" << endl
        << "    local -- Both players play on this computer." << endl
        << "    client -- Network mode / client." << endl
        << "    server -- Network mode / server." << endl;
		exit(1);
	}
}

#endif