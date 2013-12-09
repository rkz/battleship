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
                write_socket(&socket, "OK");
            }
            
            else if (order == "getTargetGrid")
                write_socket(&socket, getTargetGrid());
            
            else if (order == "play")
            {
                write_socket(&socket, "OK");
                std::string serial = read_socket(&socket);
                Grid targetGrid = Grid::unserialize(serial);
                std::string p = play(&targetGrid);
                write_socket(&socket, p);
            }
            
            else if (order == "shoot")
            {
                write_socket(&socket, "OK");
                std::string p = read_socket(&socket);
                std::string sr = shoot(p);
                write_socket(&socket, sr);
            }
            
            else if (order == "showResult")
            {
                write_socket(&socket, "OK");
                std::string sr = read_socket(&socket);
                showResult(ShotResult::unserialize(sr));
                write_socket(&socket, "OK");
            }
            
            else if (order == "getName")
                write_socket(&socket, getName());
            
            else if (order == "getGrid")
                write_socket(&socket, getGrid());
    
            else if (order == "signature")
            {
                signature();
                write_socket(&socket, "OK");
            }
            
            else if (order == "finalView")
            {
                write_socket(&socket, "OK");
                std::string ennemyName = read_socket(&socket);
                write_socket(&socket, "OK");
                std::string serial = read_socket(&socket);
                Grid ennemyGrid = Grid::unserialize(serial);
                finalView(ennemyName, &ennemyGrid);
                write_socket(&socket, "OK");
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
    
    std::cout << "Youpi" << std::endl;
    player->initFleet();
}

std::string RemoteGame::getTargetGrid()
{
    Grid* target = player->getTargetGrid();
    return target->serialize();
}

std::string RemoteGame::play(Grid* targetGrid)
{
    Position p = player->play(targetGrid);
    return p.toString();
}

std::string RemoteGame::shoot(Position p)
{
    ShotResult result = player->shoot(p);
    return result.serialize();
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
    return g->serialize();
}

void RemoteGame::signature() const
{
    player->signature();
}

void RemoteGame::finalView(std::string ennemyName, Grid* ennemyGrid) const
{
    player->finalView(ennemyName, ennemyGrid);
}
