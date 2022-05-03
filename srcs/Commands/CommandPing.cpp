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
    c->sendRawMessage("PONG :ft_irc");
    return 0;
}