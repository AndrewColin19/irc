#pragma once
#ifndef __SERVER_HPP
#define __SERVER_HPP

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <map>
#include "Client.hpp"

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
        sockaddr address;
        socklen_t addr_len;
        void create_connection();
        void check_action();
        int  get_fd();
    public:
        Server(char *port, std::string password);
        void start();
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
            if (users[fd]->isNew())
                users[fd]->setUsername(str);
            else
                std::cout << "User : " << users[fd]->getUsername() << " send : " << str << std::endl;//Traiter la commande
        }
    }
}

void Server::create_connection()
{
    std::cout << "TOTO\n";
    int client = accept(sock, &address, &addr_len);
    if (client > max_fd)
        max_fd = client;
    FD_SET(client, &set);
    users.insert(std::pair<int, Client*>(client, new Client()));
}

#endif