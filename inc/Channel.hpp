#pragma once

#include "includes.h"
#include "Client.hpp"

class Channel
{
    private:
        std::string name;
        std::vector<Client*> users;
    public:
        Channel(string name);
        ~Channel();
        void join(Client *c);
};

Channel::Channel(string name)
{
    this->name = name;
}

Channel::~Channel()
{}

void Channel::join(Client *c)
{
    users.push_back(c);
}