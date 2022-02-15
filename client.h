#pragma once
#include <boost/asio.hpp>

class Client 
{
public:
    void connect(const std::string& ip_str, int port);
    std::string readMessage();
    void sendMessage(const std::string& message);
    void closeConnection();

    ~Client();

private:
    boost::asio::io_service mService;
    boost::asio::ip::tcp::socket mSocket{ mService };
    boost::asio::streambuf mBuf;
};