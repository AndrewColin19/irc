#pragma once
#ifndef __SERVER_HPP
#define __SERVER_HPP

#include "includes.h"
#include "Client.hpp"
#include "Channel.hpp"
#include "Command.hpp"

#define MAX_MSIZE 2048

class Server
{
    private:
        int sock;
        struct addrinfo *addr;
        std::string password;
        fd_set set;
        fd_set save;
        int max_fd;
        std::map<int, Client*> users;
        std::map<std::string, Channel*> chan;
        sockaddr address;
        socklen_t addr_len;
        void create_connection();
        void check_action();
        int  get_fd();
    public:
        Server(char *port, std::string password);
        void start();
        void initUser(string str, int fd);
        int userExist(string user);
        ~Server();
};

Server::Server(char *port, std::string password)
{
    struct addrinfo	hints;
    memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
    getaddrinfo("127.0.0.1", port, &hints, &addr);
    this->password = password;
    addr_len = sizeof address;
}

void Server::start()
{
    this->sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(this->sock, this->addr->ai_addr, this->addr->ai_addrlen);
    listen(sock, 10);
    FD_ZERO(&set);
    FD_ZERO(&save);
    FD_SET(sock, &set);
    max_fd = sock;
    while (1)
    {
        save = set;
        select(max_fd + 1, &save, NULL, NULL, NULL);
        check_action();
    }
}

int Server::get_fd()
{
    int i = 0;

    while (i <= max_fd)
    {
        if (FD_ISSET(i, &save))
            return i;
        i++;
    }
    return (i);
}

void Server::check_action()
{
    char buff[MAX_MSIZE];
    ssize_t nbread = 0;
    int fd = this->get_fd();

    if (fd == sock)
        create_connection();
    else
    {
        memset(buff, 0, sizeof buff);
        nbread = recv(fd, buff, MAX_MSIZE, 0);
        if (nbread <= 0)
        {
            close(fd);
            FD_CLR(fd, &set);
            users.erase(users.find(fd));
        }
        else
        {
			std::string str(buff);
            /*std::string delimiter = "\n";

            size_t pos = 0;
            std::string c;
            while ((pos = str.find(delimiter)) != std::string::npos) {
                c = str.substr(0, pos);
                Command cmd = Command(c);
                str.erase(0, pos + delimiter.length());
            }*/
            if (users[fd]->isNew())
                this->initUser(str, fd);
            else
                std::cout << "User : " << users[fd]->getUsername() << " send : " << str << std::endl;//Traiter la commande*/
        }
    }
}

void Server::initUser(string str, int fd)
{
    size_t pos;
    string user;

    if (str.find("CAP") == string::npos)
        return ;
    if ((pos = str.find("PASS")) == string::npos)
        return ;
    if (str.substr(pos + 5, this->password.length()) != this->password)
        return ;
    if ((pos = str.find("NICK")) == string::npos)
        return ;
    //cout << pos << "    " << str.find("\r", pos);
    if (this->userExist((user = str.substr(pos + 5, str.find("\n", pos)))) && user.length() >= 1) 
        return ;
    users[fd]->setUsername(user);
    send(fd, "001 acolin :Welcome to the Internet Relay Network acolin\n", strlen("001 acolin :Welcome to the Internet Relay Network acolin\n"), 0);
}

int Server::userExist(string user)
{
    for (std::map<int, Client *>::iterator it = users.begin(); it != users.end(); ++it)
        if(it->second->getUsername() == user)
            return (1);
    return (0);
}

void Server::create_connection()
{
    int client = accept(sock, &address, &addr_len);
    if (client > max_fd)
        max_fd = client;
    FD_SET(client, &set);
    users.insert(std::pair<int, Client*>(client, new Client()));

    char buff[MAX_MSIZE];
    int nbread = recv(client, buff, MAX_MSIZE, 0);
    std::string str(buff);
    std::cout << str;
}

#endif