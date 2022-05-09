#include "Commands/CommandKick.hpp"

CommandKick::CommandKick(Server *srv)
{
	this->s = srv;
}

CommandKick::~CommandKick() 
{}

int CommandKick::exec(Client *c)
{
    if (this->argv.size() != 2)
        return c->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");
    if (!this->s->chanExist(argv[0]))
        return c->sendMessage(ERR_NOSUCHCHANNEL, argv[0] + ":No such channel");
    if (!c->isOper())
        return c->sendMessage(ERR_CHANOPRIVSNEEDED, ":You're not channel operator");
    if (!this->s->isInChan(argv[0], argv[1]))
        return c->sendMessage(ERR_USERNOTINCHANNEL, c->getNickname() + " " + argv[1] + " :They aren't on that channel");
    if (!this->s->isInChan(argv[0], c->getUsername()))
        return c->sendMessage(ERR_NOTONCHANNEL, ":You're not on that channel");
    this->s->getChannels()[argv[0]]->kick(argv[1]);
    return c->sendRawMessage(c->to_string(false) + " KICK " + argv[0] + " " + argv[1]);
}