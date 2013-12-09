/*
 * RemotePlayer.cpp
 *
 *  Created on: 28 nov. 2013
 *      Author: raphael
 */

#include "RemotePlayer.h"

RemotePlayer::RemotePlayer(boost::asio::ip::tcp::socket* _socket)
: socket(_socket)
{
}

RemotePlayer::~RemotePlayer()
{
    
}

void RemotePlayer::initFleet()
{
    std::string order = "initFleet";
    
    write_socket(socket, order);
    read_socket(socket);
}

Grid* RemotePlayer::getTargetGrid()
{
    std::string order = "getTargetGrid";
    
    write_socket(socket, order);
    std::string msg = read_socket(socket);
    
    return new Grid (gridFromString(msg));
}

Position RemotePlayer::play(Grid* targetGrid)
{
    std::string serial = targetGrid->stringFromGrid();
    std::string order = "play";
    
    write_socket(socket, order);
    read_socket(socket);
    write_socket(socket, serial);
    std::string msg = read_socket(socket);
    
    return Position(msg);
}

ShotResult RemotePlayer::shoot(Position p)
{
    std::string serial = p.toString();
    std::string order = "shoot";
    
    write_socket(socket, order);
    read_socket(socket);
    write_socket(socket, serial);
    std::string msg = read_socket(socket);
    
    return ShotResult::unserialize(msg);
}

void RemotePlayer::showResult(ShotResult sr)
{
    std::string serial = sr.serialize();
    std::string order = "showResult";
    
    write_socket(socket, order);
    read_socket(socket);
    write_socket(socket, serial);
    read_socket(socket);
}

std::string RemotePlayer::getName() const
{
    std::string order = "getName";
    
    write_socket(socket, order);
    std::string msg = read_socket(socket);
    
    return msg;
}

Grid* RemotePlayer::getGrid() const
{
    std::string order = "getGrid";
    
    write_socket(socket, order);
    std::string msg = read_socket(socket);
    
    return new Grid (gridFromString(msg));
}

void RemotePlayer::signature() const
{
    std::string order = "signature";
    
    write_socket(socket, order);
    read_socket(socket);
}

void RemotePlayer::finalView(std::string ennemyName, Grid* ennemyGrid) const
{
    std::string serial = ennemyGrid->stringFromGrid();
    std::string order = "finalView";
    
    write_socket(socket, order);
    read_socket(socket);
    write_socket(socket, ennemyName);
    read_socket(socket);
    write_socket(socket, serial);
    read_socket(socket);
}
