#include "Commands/CommandInvite.hpp"

CommandInvite::CommandInvite(Server *srv)
{
    this->s = srv;
}

CommandInvite::~CommandInvite()
{}

int CommandInvite::exec(Client *c)
{
    if (this->argv.size() != 2)
        return c->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");
    if (!this->s->chanExist(this->argv[1]))
        return c->sendMessage(ERR_NOSUCHCHANNEL, argv[1] + ":No such channel");
    if (!this->s->isInChan(this->argv[0], c->getUsername()))
        return c->sendMessage(ERR_NOTONCHANNEL, ":You're not on that channel");
    if (s->isInChan(this->argv[1], this->argv[0]));
        return c->sendMessage(ERR_USERONCHANNEL, c->getNickname() + " " + this->argv[0] + " :already in this channel");
    if (this->s->userExist(this->argv[0]))
        this->s->getChanManager().join(this->argv[1], this->s->getUser(this->argv[0]));
    c->sendMessage(RPL_INVITING, argv[0] + " " + argv[1]);
	return c->sendRawMessage(c->to_string(false) + " INVITE " + argv[0] + " " + argv[1]);
}