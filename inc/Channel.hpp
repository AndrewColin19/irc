#pragma once

#include "includes.h"
#include "Client.hpp"

class Channel
{
    private:
        std::string name;
        Client *creator;
        std::vector<Client*> users;
    public:
        Channel(string name);
        ~Channel();
        void join(Client *c);
};