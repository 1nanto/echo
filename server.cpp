#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "server.h"

using namespace boost::asio;

void Server::listen() 
{
    ip::tcp::acceptor acceptor(service, endpoint);
    std::ostringstream oss;
    std::string message;
    std::cout << "Listening..." << std::endl;
    while (true)
    {
        ip::tcp::socket socket(service);
        acceptor.accept(socket);
        do 
        {
            size_t bytes = read_until(socket, buf, '\n');

            oss.str("");
            oss << &buf;
            message = oss.str();
            buf.consume(bytes);

            if (!message.compare("quit\n")) break;

            std::cout << "New message: " << message;
            socket.write_some(buffer(message));
        } 
        while (true);
        socket.close();
    }
}
