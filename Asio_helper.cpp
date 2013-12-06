//
//  Asio_helper.cpp
//  Battleship
//
//  Created by Maxime Cartan on 07/12/2013.
//
//

#include "Asio_helper.h"

std::string read_socket(boost::asio::ip::tcp::socket* socket)
{
    std::string msg;
    
    while (true)
    {
        boost::array<char, 32> buf;
        boost::system::error_code error;
        
        int len = socket->read_some(boost::asio::buffer(buf), error);
        
        if (error == boost::asio::error::eof)
            // connection closed by server
            break;
        else if (error != 0)
            throw boost::system::system_error(error);
        else {
            msg += std::string(buf.data()).substr(0,len);
        }
    }
    
    return msg;
}