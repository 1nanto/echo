#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "server.h"

using namespace boost::asio;

void Server::listen() {
    acceptor.accept(socket);
}

std::string Server::readMessage() {
    std::ostringstream oss;
    size_t bytes = read_until(socket, buf, '\n');

    oss.str("");
    oss << &buf;
    buf.consume(bytes);
    std::string message = oss.str();
    message.pop_back();
    return message;
}

void Server::sendMessage(std::string message) {
    message += '\n';
    socket.write_some(buffer(message));
}

void Server::closeConnection() {
    socket.close();
}
