#include "Commands/CommandJoin.hpp"

CommandJoin::CommandJoin(Server *srv)
{
    this->s = srv;
}

CommandJoin::~CommandJoin()
{}

int CommandJoin::exec(Client *c)
{
    if (this->argv[0][0] == '#')
    {
        //chanel
    }
    else
    {
    }
    return 0;
}