#include "Client.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

Client::Client(int fd, struct sockaddr_in address)
{
    is_new = 1;
    is_connected = 0;
    this->fd = fd;
    this->address = address;
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

void Client::setHostname(std::string hostname)
{
    this->hostname = hostname;
}

std::string Client::getHostname()
{
    return hostname;
}

void Client::setRealname(std::string realname)
{
    this->realname = realname;
}

std::string Client::getRealname()
{
    return realname;
}

void Client::setNickname(std::string nickname)
{
    this->nickname = nickname;
}

std::string Client::getNickname()
{
    return this->nickname;
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
    cout << c.str() << endl;
    send(fd, c.str().c_str(), c.str().length(), 0);
    return 1;
}

int Client::sendRawMessage(std::string message)
{
    send(this->fd, message.c_str(), message.length(), 0);
    return 1;
}

std::string Client::getAddress() const
{ 
    return inet_ntoa(this->address.sin_addr); 
}

void Client::connect()
{
    if (this->is_connected != 1)
    {
        this->is_connected = 1;
        sendMessage(RPL_WELCOME, " Welcome to the Internet Relay Network " + to_string(false));
    }
}

std::string	Client::to_string(bool isAnon) const
{
    if (isAnon)
		return ":anonymous!anonymous@anonymous";
	return (":" + this->nickname + "!" + this->username + "@" + this->getAddress());
}