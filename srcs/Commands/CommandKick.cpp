#include "Commands/CommandKick.hpp"

CommandQuit::CommandQuit(Server *srv)
{
	this->s = srv;
}

CommandQuit::~CommandQuit() 
{}

int CommandQuit::exec(Client *c)
{
    if (this->argv.size() != 2)
        c->sendMessage(ERR_NEEDMOREPARAMS, "Not enough parameters");
    
    return 0;
}