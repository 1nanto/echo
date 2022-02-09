#include <iostream>
#include <sstream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::asio;

io_service service;

void listen(int port) 
{
    ip::tcp::endpoint endpoint = ip::tcp::endpoint(ip::tcp::v4(), port);
    ip::tcp::acceptor acceptor(service, endpoint);

    boost::asio::streambuf buf;
    std::ostringstream oss;
    std::string message;
    while (true)
    {
        ip::tcp::socket socket(service);
        acceptor.accept(socket);
        size_t bytes = read_until(socket, buf, '\n');

        oss.str("");
        oss << &buf;
        message = oss.str();
        buf.consume(bytes);

        std::cout << "New message: " << message << std::endl;
        socket.write_some(buffer(message));
        socket.close();
    }
}

int main()
{
    int port;
    std::cout << "Enter port: ";
    std::cin >> port;
    std::cout << "Listening..." << std::endl;
    listen(port);
}
