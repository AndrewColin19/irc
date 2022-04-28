#include "Commands/CommandPass.hpp"

CommandPass::CommandPass(Server *srv)
{
    this->s = srv;
}

CommandPass::~CommandPass()
{}

int CommandPass::exec(Client *c)
{
    cout << "START" << endl;
    if (c->isConnected())
        return c->sendMessage(ERR_ALREADYREGISTRED, "Unauthorized command (already registered)");
    if (argv.size() != 1)
        return c->sendMessage(ERR_NEEDMOREPARAMS, "Not enough parameters");
    if (s->getPassword() != argv[0])
        return c->sendMessage(ERR_PASSWDMISMATCH, "Password incorrect");
    return 0;
}