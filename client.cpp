#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "client.h"

using namespace boost::asio;

void Client::connect(std::string ip_str, int port) {
    ip::tcp::endpoint ep(ip::address_v4::from_string(ip_str), port);
    socket.connect(ep);
}

std::string Client::readMessage() {
    std::ostringstream oss;
    size_t bytes = read_until(socket, buf, '\n');

    oss.str("");
    oss << &buf;
    buf.consume(bytes);
    std::string message = oss.str();
    message.pop_back();
    return message;
}

void Client::sendMessage(std::string message) {
    message += '\n';
    socket.write_some(buffer(message));
}

void Client::closeConnection() {
    socket.close();
}
