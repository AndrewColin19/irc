#pragma once
#ifndef __CLIENT_HPP
#define __CLIENT_HPP

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

class Client
{
    private:
        std::string username;
        int is_new;
    public:
        Client();
        void setUsername(std::string username);
        std::string getUsername();
        int isNew();
};

Client::Client()
{
    is_new = 1;
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

#endif