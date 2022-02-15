#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "server.h"

using namespace boost::asio;

Server::Server(unsigned short port) : 
    mAcceptor(mService, ip::tcp::endpoint(ip::tcp::v4(), port)), mSocket(mService)
{ }

void Server::listen() 
{
    mAcceptor.accept(mSocket);
}

std::string Server::readMessage() 
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

void Server::sendMessage(const std::string& message)
{
    mSocket.write_some(buffer(message + '\n'));
}

void Server::closeConnection() 
{
    mSocket.close();
}

Server::~Server() 
{
   if (mSocket.is_open()) mSocket.close();
}
