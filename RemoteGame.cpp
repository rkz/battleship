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
        
        bool notOver = true;
        
        while (notOver)
        {
            std::string order = read_socket(&socket);
            
            if (order == "initFleet")
            {
                initFleet();
                socket.write_some(boost::asio::buffer("OK"));
            }
            
            else if (order == "getTargetGrid")
                socket.write_some(boost::asio::buffer(getTargetGrid()));
            
            else if (order == "play")
            {
                std::string serial = read_socket(&socket);
                Grid targetGrid = gridFromString(serial);
                std::string p = play(&targetGrid);
                socket.write_some(boost::asio::buffer(p));
            }
            
            else if (order == "shoot")
            {
                std::string p = read_socket(&socket);
                std::string sr = shoot(p);
                socket.write_some(boost::asio::buffer(sr));
            }
            
            else if (order == "showResult")
            {
                std::string sr = read_socket(&socket);
                showResult(shotResultFromString(sr));
                socket.write_some(boost::asio::buffer("OK"));
            }
            
            else if (order == "getName")
                socket.write_some(boost::asio::buffer(getName()));
            
            else if (order == "getGrid")
                socket.write_some(boost::asio::buffer(getGrid()));
    
            else if (order == "signature")
            {
                signature();
                socket.write_some(boost::asio::buffer("OK"));
            }
            
            else if (order == "finalView")
            {
                std::string ennemyName = read_socket(&socket);
                std::string serial = read_socket(&socket);
                Grid ennemyGrid = gridFromString(serial);
                finalView(ennemyName, &ennemyGrid);
                socket.write_some(boost::asio::buffer("OK"));
                notOver = false;
            }
        }
        
    }
    
	catch (std::exception& e) {
		cout << "Error - uncaught (network?) exception: " << e.what() << endl;
	}
}

void RemoteGame::initFleet()
{
    player->initFleet();
}

std::string RemoteGame::getTargetGrid()
{
    Grid* target = player->getTargetGrid();
    return target->stringFromGrid();
}

std::string RemoteGame::play(Grid* targetGrid)
{
    Position p = player->play(targetGrid);
    return p.toString();
}

std::string RemoteGame::shoot(Position p)
{
    ShotResult result = player->shoot(p);
    return result.stringFromShotResult();
}

void RemoteGame::showResult(ShotResult sr)
{
    player->showResult(sr);
}

std::string RemoteGame::getName() const
{
    return player->getName();
}

std::string RemoteGame::getGrid() const
{
    Grid* g = player->getGrid();
    return g->stringFromGrid();
}

void RemoteGame::signature() const
{
    player->signature();
}

void RemoteGame::finalView(std::string ennemyName, Grid* ennemyGrid) const
{
    player->finalView(ennemyName, ennemyGrid);
}