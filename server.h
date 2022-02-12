#pragma once
#include <boost/asio.hpp>

using namespace boost::asio;

class Server {
public:
    Server(unsigned short port) :
        acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), port)), socket(service)
    { }

    void listen();
    std::string readMessage();
    void sendMessage(std::string message);
    void closeConnection();

private:
    io_service service;
    ip::tcp::acceptor acceptor;
    ip::tcp::socket socket;
    streambuf buf;
};