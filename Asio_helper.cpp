//
//  Asio_helper.cpp
//  Battleship
//
//  Created by Maxime Cartan on 07/12/2013.
//
//

#include "Asio_helper.h"

void write_socket(boost::asio::ip::tcp::socket* socket, std::string s)
{
    boost::system::error_code err = boost::asio::error::eof;
    boost::asio::write(*socket, boost::asio::buffer(s, s.length()), err);
}

std::string read_socket(boost::asio::ip::tcp::socket* socket)
{
    std::string msg;

    boost::array<char, 512> buf;
        
    int len = socket->read_some(boost::asio::buffer(buf, 512));
    std::cout << len << std::endl;
    msg = std::string(buf.data()).substr(0,len);
    
    return msg;
}