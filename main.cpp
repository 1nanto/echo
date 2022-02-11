//#define SERVER

#include <iostream>
#include <boost/system/error_code.hpp>
#ifdef SERVER
#include "server.h"
#else
#include "client.h"
#endif

using namespace boost::system;

int main()
{
#ifdef SERVER
    unsigned short port;
    std::cout << "Enter port: ";
    std::cin >> port;

    Server server(port);
    server.listen();
#else
    std::string ip_str;
    int port;
    while (true) {
        std::cout << "Enter ipv4: ";
        std::cin >> ip_str;
        std::cout << "Enter port: ";
        std::cin >> port;
        Client client;
        try
        {
            client.connect(ip::address_v4::from_string(ip_str), port);
        }
        catch (system_error e)
        {
            std::cout << e.code() << std::endl;
        }
    }
#endif
}