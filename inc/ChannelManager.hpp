#pragma once

#include "includes.h"
#include "Client.hpp"
#include "Channel.hpp"

class ChannelManager
{
    private:
        map<string, Channel*> channels;
    public:
        ChannelManager();
        ~ChannelManager();
        void add(string name, Client *c);
        void join(string name, Client *c);
};