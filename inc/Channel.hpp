#pragma once

#include "includes.h"
#include "Client.hpp"

class Channel
{
    private:
        std::string name;
        Client *creator;
        map<char, bool> modes;
        std::vector<Client*> users;
    public:
        Channel(string name);
        ~Channel();
        bool isIn(string username);
        void setMode(string mode);
        void join(Client *c);
        void kick(std::string username);
};