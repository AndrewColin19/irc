#include "Commands/CommandOper.hpp"

CommandOper::CommandOper(Server *srv)
{
    this->s = srv;
}

CommandOper::~CommandOper()
{}

int CommandOper::exec(Client *c)
{
    if (argv.size() != 2)
        return c->sendMessage(ERR_NEEDMOREPARAMS, ":Invalid params count.");
    if (s->getOPassword() != argv[1])
        return c->sendMessage(ERR_PASSWDMISMATCH, ":Invalid password.");
    c->setMode('o', 1);
    return c->sendMessage(RPL_YOUREOPER, ":You are now operator !");
}