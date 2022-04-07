#include "Client.hpp"


Client::Client(int fd)
{
    is_new = 1;
    is_connected = 0;
    this->fd = fd;
}

void Client::setUsername(std::string username)
{
    this->username = username;
    is_new = 0;
}

std::string Client::getUsername()
{
    return username;
}

int Client::isNew()
{
    return is_new;
}

int Client::isConnected()
{
    return is_connected;
}

int Client::getFd()
{
    return fd;
}

int Client::sendMessage(string err_code, string msg)
{
    stringstream c;

    c << ":ft_irc " << err_code << " " << this->username << ":" << msg << "\n";
    send(fd, c.str().c_str(), c.str().length(), 0);
    return 1;
}

void Client::connect()
{
    this->is_connected = 1;
}
