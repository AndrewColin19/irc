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
        Channel(string name, Client *c);
        ~Channel();
        bool isIn(string username);
        void setMode(char mode, int add);
        void join(Client *c);
        void kick(std::string username);
        void sendOnChannel(string msg, Client *sender);
        map<char, bool> getMode();
        Client *getCreator();
};