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

#define MAX_MSIZE 2048

class Server
{
    private:
        int sock;
        struct addrinfo *addr;
        std::string password;
        fd_set set;
        int max_fd;
        std::map<std::string, int> users;
        sockaddr address;
        socklen_t addr_len;
        void create_connection();
        void check_action();
    public:
        Server(char *port, std::string password);
        void start();
        ~Server();
};

Server::Server(char *port, std::string password)
{
    struct addrinfo	hints;
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
    getaddrinfo("127.0.0.1", port, &hints, &addr);
    this->password = password;
}

void Server::start()
{
    this->sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(this->sock, this->addr->ai_addr, this->addr->ai_addrlen);
    listen(sock, 100);
    FD_ZERO(&set);
    FD_SET(sock, &set);
    max_fd = sock;
    while (1)
    {
        select(max_fd + 1, &set, NULL, NULL, NULL);
        std::cout << "afdsfdsfds\n";
        check_action();
    }
}

void Server::check_action()
{
    if (users.find("TOTO") == users.end())
        create_connection();
    else
    {
        char buff[MAX_MSIZE];
        int nbread = recv(users["TOTO"], buff, MAX_MSIZE, 0);
        std::string cmd = buff;
        std::cout << cmd << std::endl;
    }
}

void Server::create_connection()
{
    int client = accept(sock, &address, &addr_len);
    if (client > max_fd)
        max_fd = client;
    FD_SET(client, &set);
    users.insert(std::pair<std::string, int>("TOTO", client));
}

#endif