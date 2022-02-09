#include <iostream>
#include <sstream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::asio;
using namespace boost::system;

io_service service;

void echo(std::string ip_str, int port, std::string message)
{
    message += "\n";
    ip::tcp::socket socket(service);
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip_str), port);
    socket.connect(ep);

    socket.write_some(buffer(message));
    boost::asio::streambuf buf;
    int bytes = read_until(socket, buf, "\n");
    if (bytes == 0) {
        std::cout << "no message" << std::endl;
        return;
    }

    std::ostringstream oss;
    oss << &buf;
    std::cout << (oss.str() == message ? "Right. " : "Wrong. ");
    message.pop_back();
    std::cout << "Server answered: " << message << std::endl;
    socket.close();
}

int main()
{
    std::string message;
    std::string ip_str;
    int port;
    while (true) {
        std::cout << "Enter ipv4: ";
        std::cin >> ip_str;
        std::cout << "Enter port: ";
        std::cin >> port;
        std::cout << "Enter message: ";
        std::cin >> message;
        try 
        {
            echo(ip_str, port, message);
        }
        catch (boost::system::system_error e)
        {
            std::cout << e.code() << std::endl;
        }
    }
}