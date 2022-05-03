
#include "ChannelManager.hpp"

ChannelManager::ChannelManager()
{}

ChannelManager::~ChannelManager()
{}

void ChannelManager::add(string name, Client *c)
{
    channels.insert(pair<string, Channel*>(name, new Channel(name, c)));
}

void ChannelManager::join(string name, Client *c)
{
    channels[name]->join(c);
}