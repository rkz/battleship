//
//  Asio_helper.cpp
//  Battleship
//
//  Created by Maxime Cartan on 07/12/2013.
//
//

#include "Asio_helper.h"

#include <iostream>

void write_socket(boost::asio::ip::tcp::socket* socket, std::string s)
{
#ifdef BATTLESHIP_NETWORK_TRACE
	std::cout << "Write " << s << std::endl;
#endif

    boost::system::error_code err = boost::asio::error::eof;
    boost::asio::write(*socket, boost::asio::buffer(s, s.length()), err);
}

std::string read_socket(boost::asio::ip::tcp::socket* socket)
{
    std::string msg;

    boost::array<char, 512> buf;
        
    int len = socket->read_some(boost::asio::buffer(buf, 512));
    msg = std::string(buf.data()).substr(0,len);
    
#ifdef BATTLESHIP_NETWORK_TRACE
	std::cout << "Read " << msg << std::endl;
#endif

    return msg;
}
