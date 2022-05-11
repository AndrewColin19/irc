#include "Channel.hpp"

Channel::Channel(string name, Client *c)
{
    this->name = name;
    creator = c;
    if (c)
        users.push_back(c);
}

Channel::~Channel()
{}

void Channel::join(Client *c)
{
    users.push_back(c);
}

bool Channel::isIn(std::string username)
{
    for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
    {
        if ((*it)->getUsername() == username)
            return true;
    }
    return (false);
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

void Channel::sendOnChannel(string msg, Client *sender, int send)
{
    for (size_t i = 0; i < users.size(); i++)
        if (send || users[i] != sender)
            users[i]->sendRawMessage(msg);
}

string	Channel::listUsers()
{
	stringstream list;
    for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
    {
        if ((*it)->isOper())
            list << "@";
        list << (*it)->getNickname() << " ";
    }
	return list.str();
}

string Channel::getTopic()
{
    return topic;
}

void Channel::setTopic(string topic)
{
    this->topic = topic;
}

vector<Client*> Channel::getUsers()
{
    return users;
}

string Channel::getTopicSetter()
{
    return topicSetter;
}

void Channel::setTopicSetter(string user)
{
    topicSetter = user;
}

time_t Channel::getTopicSetted()
{
    return topicSetted;
}

void Channel::setTopicSetter()
{
    topicSetted = time(0);
}