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
	this->s->removeClient(c->getFd());
    close(c->getFd());
    delete c;
    return 0;
}