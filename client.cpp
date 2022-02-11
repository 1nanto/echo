#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "client.h"

using namespace boost::asio;

void Client::connect(ip::address_v4 ipv4, int port)
{
    ip::tcp::socket socket(service);
    ip::tcp::endpoint ep(ipv4, port);
    socket.connect(ep);

    std::cout << "Enter messages: " << std::endl;
    std::string message;
    do 
    {
        std::cin >> message;
        message += '\n';
        socket.write_some(buffer(message));

        if (!message.compare("quit\n")) break;

        streambuf buf;
        int bytes = read_until(socket, buf, "\n");
        if (bytes == 0) {
            std::cout << "no message" << std::endl;
            continue;
        }
        std::ostringstream oss;
        oss << &buf;
        std::cout << (oss.str() == message ? "Right. " : "Wrong. ");
        message.pop_back();
        std::cout << "Server answered: " << message << std::endl;
    } 
    while (true);

    socket.close();
}