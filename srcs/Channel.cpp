#include "Channel.hpp"

Channel::Channel(string name, Client *c)
{
    this->name = name;
    creator = c;
}

Channel::~Channel()
{}

void Channel::join(Client *c)
{
    users.push_back(c);
}

bool Channel::isIn(std::string username)
{
    bool test = false;
    for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
    {
        if ((*it)->getUsername() == username)
            test = true;
    }
    return (test);
}

void Channel::kick(std::string username)
{
    for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
    {
        if ((*it)->getUsername() == username)
        {
            users.erase(it);
            break;
        }
    }
}

void Channel::setMode(char mode, int add)
{
    if (add)
    {
        if (modes.find(mode) == modes.end())
            modes.insert(pair<char, bool>(mode, true));
        else
            modes[mode] = true;
    }
    else
    {
        if (modes.find(mode) == modes.end())
            modes.insert(pair<char, bool>(mode, false));
        else
            modes[mode] = false;
    }
}

Client *Channel::getCreator()
{
    return creator;
}

map<char, bool> Channel::getMode()
{
    return modes;
}

void Channel::sendOnChannel(string msg)
{
    for (int i = 0; i < users.size(); i++)
        users[i]->sendRawMessage(msg);
}