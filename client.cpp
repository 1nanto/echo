#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "client.h"

using namespace boost::asio;

void Client::connect(const std::string& ip_str, int port)
{
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip_str), port);
    mSocket.connect(ep);
}

std::string Client::readMessage() 
{
    std::ostringstream oss;
    size_t bytes = read_until(mSocket, mBuf, '\n');

    oss.str("");
    oss << &mBuf;
    mBuf.consume(bytes);
    std::string message = oss.str();
    message.pop_back();
    return message;
}

void Client::sendMessage(const std::string& message)
{
    mSocket.write_some(buffer(message + '\n'));
}

void Client::closeConnection() 
{
    mSocket.close();
}

Client::~Client()
{
    if (mSocket.is_open()) mSocket.close();
}