
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

map<string, Channel*> ChannelManager::getChannels()
{
    return channels;
}

bool ChannelManager::chanExist(std::string chanName)
{
    if (channels.find(chanName) == channels.end())
        return false;
    return true;
}