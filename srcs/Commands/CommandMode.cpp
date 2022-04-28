#include "Commands/CommandMode.hpp"

CommandMode::CommandMode(Server *srv)
{
    this->s = srv;
}

CommandMode::~CommandMode()
{}

int CommandMode::exec(Client *c)
{
    if (this->argv[0][0] == '#')
    {
        //chanel
    }
    else
    {
        if (!this->s->userExist(this->argv[0]))
            return c->sendMessage(ERR_NOSUCHNICK, "No user find.");
        if (c->getNickname() != argv[0])
            return c->sendMessage(ERR_USERSDONTMATCH, "Invalid user.");
    }
    return 0;
}