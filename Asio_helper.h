//
//  Asio_helper.h
//  Battleship
//
//  Created by Maxime Cartan on 06/12/2013.
//
//

#ifndef Battleship_Asio_helper_h
#define Battleship_Asio_helper_h

#include <boost/asio.hpp>
#include <boost/bind.hpp>

void write_socket(boost::asio::ip::tcp::socket* socket, std::string s);
std::string read_socket(boost::asio::ip::tcp::socket* socket);

#endif