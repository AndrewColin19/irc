#include "Channel.hpp"

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