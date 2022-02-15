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

    std::cout << "Listening..." << std::endl;
    std::string message;
    while (true)
    {
        server.listen();
        while (true)
        {
            try 
            {
                message = server.readMessage();

                if (!message.compare("quit")) 
                    break;

                std::cout << "New message: " << message << std::endl;
                server.sendMessage(message);
            }
            catch (system_error e)
            {
                std::cout << e.code() << std::endl;
                break;
            }
        }
        server.closeConnection();
    }

#else
    int port;
    std::string ip_str;
    std::string message;
    std::string answer;

    while (true) 
    {
        std::cout << "Enter ipv4: ";
        std::cin >> ip_str;
        std::cout << "Enter port: ";
        std::cin >> port;
        Client client;
        try
        {
            client.connect(ip_str, port);
            std::cout << "Enter messages: " << std::endl;
            std::cin.ignore();
            while (true)
            {
                std::getline(std::cin, message);
                client.sendMessage(message);

                if (!message.compare("quit")) 
                    break;

                answer = client.readMessage();
                std::cout << "Server answered: " << answer << (message.compare(answer) ? ". Wrong." : ". Right.") << std::endl;
            }
            client.closeConnection();
        }
        catch (system_error e)
        {
            std::cout << e.code() << std::endl;
        }
    }
#endif
}