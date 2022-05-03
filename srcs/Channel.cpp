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

void Channel::setMode(string mode)
{
    char c;
    c = mode[1];

    if (mode[0] == '+')
    {
        if (modes.find(c) == modes.end())
            modes.insert(pair<char, bool>(c, true));
        else
            modes[c] = true;
    }
    else
    {
        if (modes.find(c) == modes.end())
            modes.insert(pair<char, bool>(c, false));
        else
            modes[c] = false;
    }
}