#include "Commands/CommandQuit.hpp"

CommandQuit::CommandQuit(Server *srv)
{
	this->s = srv;
}

CommandQuit::~CommandQuit() 
{}

int CommandQuit::exec(Client *c)
{
    if (!c->isConnected())
		    return !c->sendMessage(ERR_NOTREGISTERED, ":You have not registered");
    map<string, Channel*> chans = s->getChannels();
    map<string, Channel*>::iterator it = chans.begin();
    while (it != chans.end())
    {
        if (s->isInChan((*it).first, c->getUsername()))
            (*it).second->kick(c->getUsername());
        it++;
    }
    map<int, Client*> users = s->getClients();
    map<int, Client*>::iterator b = users.begin();
    while (b != users.end())
    {
        (*b).second->sendRawMessage(c->to_string(false) + " QUIT :Quit: " + str);
        b++;
    }
    this->s->removeClient(c->getFd());
    return 0;
}