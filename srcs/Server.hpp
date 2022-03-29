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

class Server
{
    private:
        int sock;
        struct addrinfo *addr;
        std::string password;
        fd_set save;
        fd_set set;
        int max_fd;
        sockaddr address;
        socklen_t addr_len;
        void create_connection();
    public:
        Server(char *port, std::string password);
        void start();
        ~Server();
};

Server::Server(char *port, std::string password)
{
    getaddrinfo("127.0.0.1", port, NULL, &addr);
    this->password = password;
}

void Server::start()
{
    this->sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(this->sock, this->addr->ai_addr, this->addr->ai_addrlen);
    listen(sock, 5);
    FD_ZERO(&save);
    FD_ZERO(&set);
    FD_SET(sock, &save);
    max_fd = sock;
    while (1)
    {
        set = save;
        select(max_fd + 1, &set, NULL, NULL, NULL);
        std::cout << "abcd\n";
    }
}

void Server::create_connection()
{
    int i = 0;

    addr_len = sizeof(address);
    while (i <= max_fd)
    {
        if (FD_ISSET(i, &set))
        {
            if (i == sock)
            {
                int client = accept(sock, &address, &addr_len);
                if (max_fd < client)
                    max_fd = client;
                FD_SET(client, &save);
            }
            else
            {
                std::cout << "abcdefgh\n";
            }
        }
        i++;
    }

}

#endif