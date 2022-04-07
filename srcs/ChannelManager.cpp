
#include "ChannelManager.hpp"

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