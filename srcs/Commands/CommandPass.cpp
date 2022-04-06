#include "Commands/CommandPass.hpp"

CommandPass::CommandPass(Server *srv)
{
    this->s = srv;
}

CommandPass::~CommandPass()
{}

int CommandPass::exec(Client *c)
{
    if (c->isConnected())
        return c->sendMessage(462, "User already logged");
    if (argv.size() != 1)
        return c->sendMessage(461, "Invalid number of param");
    if (s->getPassword() != argv[0])
        return c->sendMessage(464, "Wrong password");
    c->connect();
    return 0;
}