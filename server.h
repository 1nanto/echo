#pragma once
#include <boost/asio.hpp>

using namespace boost::asio;

class Server {
public:
    Server(unsigned short port) :
        endpoint(ip::tcp::endpoint(ip::tcp::v4(), port))
    { }

    void listen();

private:
    io_service service;
    ip::tcp::endpoint endpoint;
    streambuf buf;
};