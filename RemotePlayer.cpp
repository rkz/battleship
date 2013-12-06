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
    
    socket->write_some(boost::asio::buffer(order));
    read_socket(socket);
}

Grid* RemotePlayer::getTargetGrid()
{
    std::string order = "getTargetGrid";
    
    socket->write_some(boost::asio::buffer(order));
    std::string msg = read_socket(socket);
    
    return new Grid (gridFromString(msg));
}

Position RemotePlayer::play(Grid* targetGrid)
{
    std::string serial = targetGrid->stringFromGrid();
    std::string order = "play";
    
    socket->write_some(boost::asio::buffer(order));
    socket->write_some(boost::asio::buffer(serial));
    std::string msg = read_socket(socket);
    
    return Position(msg);
}

ShotResult RemotePlayer::shoot(Position p)
{
    std::string serial = p.toString();
    std::string order = "shoot";
    
    socket->write_some(boost::asio::buffer(order));
    socket->write_some(boost::asio::buffer(serial));
    std::string msg = read_socket(socket);
    
    return shotResultFromString(msg);
}

void RemotePlayer::showResult(ShotResult sr)
{
    std::string serial = sr.stringFromShotResult();
    std::string order = "showResult";
    
    socket->write_some(boost::asio::buffer(order));
    socket->write_some(boost::asio::buffer(serial));
    read_socket(socket);
}

std::string RemotePlayer::getName() const
{
    std::string order = "getName";
    
    socket->write_some(boost::asio::buffer(order));
    std::string msg = read_socket(socket);
    
    return msg;
}

Grid* RemotePlayer::getGrid() const
{
    std::string order = "getGrid";
    
    socket->write_some(boost::asio::buffer(order));
    std::string msg = read_socket(socket);
    
    return new Grid (gridFromString(msg));
}

void RemotePlayer::signature() const
{
    std::string order = "signature";
    
    socket->write_some(boost::asio::buffer(order));
    read_socket(socket);
}

void RemotePlayer::finalView(std::string ennemyName, Grid* ennemyGrid) const
{
    std::string serial = ennemyGrid->stringFromGrid();
    std::string order = "finalView";
    
    socket->write_some(boost::asio::buffer(order));
    socket->write_some(boost::asio::buffer(ennemyName));
    socket->write_some(boost::asio::buffer(serial));
    read_socket(socket);
}