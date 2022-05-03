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
    if (1)//!exist(argv[0]))
        c->sendMessage(ERR_NOSUCHCHANNEL, argv[0] + ":No such channel");
    if (1)//c->isop()
        c->sendMessage(ERR_CHANOPRIVSNEEDED, "You're not channel operator");
    if (1) //!isInChan(c->getUsername()) <nick> <channel> :They aren't on that channel
        c->sendMessage(ERR_USERNOTINCHANNEL, c->getNickname() + " " + argv[1] + " :They aren't on that channel")
    return 0;
}