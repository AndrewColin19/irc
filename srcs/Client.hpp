#pragma once
#ifndef __CLIENT_HPP
#define __CLIENT_HPP

#include "includes.h"

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