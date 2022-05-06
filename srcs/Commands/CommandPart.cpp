#include "Commands/CommandPart.hpp"

CommandPart::CommandPart(Server *srv)
{
    this->s = srv;
}

CommandPart::~CommandPart()
{}

int CommandPart::exec(Client *c)
{
    if (argv.size() < 1)
        return c->sendMessage(ERR_NEEDMOREPARAMS, "Not enough parameters");
    if (argv[0][0] == '#')
    {
        if (!s->chanExist(argv[0]))
            return c->sendMessage(ERR_NOSUCHCHANNEL, "Invalid channel.");
        if (!this->s->isInChan(argv[0], c->getNickname()))
            return c->sendMessage(ERR_USERNOTINCHANNEL, c->getNickname() + " " + argv[1] + " :They aren't on that channel");
        Channel *chan = s->getChannels()[argv[0]];
        chan->sendOnChannel(c->to_string(false) + " PART " + argv[0], c);
        chan->removeUser(c);
    }
    return 0;
}