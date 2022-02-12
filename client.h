#pragma once
#include <boost/asio.hpp>

using namespace boost::asio;

class Client {
public:
    Client() = default;

    void connect(std::string ip_str, int port);
    std::string readMessage();
    void sendMessage(std::string message);
    void closeConnection();

private:
    io_service service;
    ip::tcp::socket socket{ service };
    streambuf buf;
};