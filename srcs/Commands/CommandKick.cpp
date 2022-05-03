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
    if (!this->s->chanExist(argv[0]))
        c->sendMessage(ERR_NOSUCHCHANNEL, argv[0] + ":No such channel");
    if (!c->isOper())
        c->sendMessage(ERR_CHANOPRIVSNEEDED, "You're not channel operator");
    if (!this->s->isInChan(argv[0], argv[1]))
        c->sendMessage(ERR_USERNOTINCHANNEL, c->getNickname() + " " + argv[1] + " :They aren't on that channel");
    if (!this->s->isInChan(argv[0], c->getUsername()))
        c->sendMessage(ERR_NOTONCHANNEL, "You're not on that channel");
    this->s->getChannels().at(argv[0])->kick(argv[1]);
    c->sendRawMessage(c->to_string(false) + " KICK " + argv[0] + " " + argv[1]);
    return 0;
}