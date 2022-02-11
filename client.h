#pragma once
#include <boost/asio.hpp>

using namespace boost::asio;

class Client {
public:
    Client() { }

    void connect(ip::address_v4 ipv4, int port);

private:
    io_service service;
    streambuf buf;
};