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
        void add(string name);
        void join(string name, Client *c);
};

ChannelManager::ChannelManager()
{}

ChannelManager::~ChannelManager()
{}

void ChannelManager::add(string name)
{
    channels.insert(pair<string, Channel*>(name, new Channel(name)));
}

void ChannelManager::join(string name, Client *c)
{
    channels[name]->join(c);
}