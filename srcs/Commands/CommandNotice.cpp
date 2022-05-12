#include "Commands/CommandNotice.hpp"

CommandNotice::CommandNotice(Server *srv)
{
	this->s = srv;
}

CommandNotice::~CommandNotice() 
{}

int CommandNotice::exec(Client *c)
{
    if (argv.size() != 1)
        return 0;
    if (str.empty())
        return 0;
    if (argv[0][0] == '#')
    {
        if (!s->chanExist(argv[0]))
            return 0;
        if (!this->s->isInChan(argv[0], c->getNickname()))
            return 0;
        Channel *chan = s->getChannels()[argv[0]];
        chan->sendOnChannel(c->to_string(false) + " NOTICE " + argv[0] + " :" + str, c, 0);
    }
    else
    {
        if (!s->userExist(argv[0]))
            return 0;
        Client *u = s->getUser(argv[0]);
        u->sendRawMessage(c->to_string(false) + " NOTICE " + u->getNickname() + " :" + str);
    }
    return 0;
}