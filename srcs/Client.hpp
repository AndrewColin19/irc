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
    public:
        Client();
        void setUsername(std::string username);
        std::string getUsername();
};

void Client::setUsername(std::string username)
{
    this->username = username;
}

std::string Client::getUsername()
{
    return username;
}

#endif