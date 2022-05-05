#include "Commands/CommandPing.hpp"

CommandPing::CommandPing(Server *srv)
{
    this->s = srv;
}

CommandPing::~CommandPing()
{}

int CommandPing::exec(Client *c)
{
    if (this->argv.size() == 0)
        return !c->sendMessage(ERR_NEEDMOREPARAMS, "Not enough parameters");
    return c->sendRawMessage(":ft_irc PONG ft_irc");
}