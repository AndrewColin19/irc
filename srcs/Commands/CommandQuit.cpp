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
    for (map<string, Channel*>::iterator it = s->getChannels().begin(); it != s->getChannels().end(); it++)
    {
        if (s->isInChan((*it).first, c->getUsername()))
        {
            (*it).second->sendOnChannel(c->to_string(false) + " PART :" + argv[0], c, 1);
            (*it).second->kick(c->getUsername());
        }
    }
    map<int, Client*> users = s->getClients();
    map<int, Client*>::iterator b = users.begin();
    while (b != users.end())
    {
        (*b).second->sendRawMessage(c->to_string(false) + " QUIT :Quit: " + str);
        b++;
    }
    cout << "CHACAL2\n";
    this->s->removeClient(c->getFd());
    close(c->getFd());
    delete c;
    return 0;
}