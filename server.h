#pragma once
#include <boost/asio.hpp>

class Server 
{
public:
    Server(unsigned short port);

    void listen();
    std::string readMessage();
    void sendMessage(const std::string& message);
    void closeConnection();

    ~Server();

private:
    boost::asio::io_service mService;
    boost::asio::ip::tcp::acceptor mAcceptor;
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::streambuf mBuf;
};