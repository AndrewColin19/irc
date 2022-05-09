#include "Commands/CommandPrivmsg.hpp"

CommandPrivmsg::CommandPrivmsg(Server *srv)
{
	this->s = srv;
}

CommandPrivmsg::~CommandPrivmsg() 
{}

int CommandPrivmsg::exec(Client *c)
{
    if (argv.size() != 1)
        return c->sendMessage(ERR_TOOMANYTARGETS, "Invalid targets.");
    if (str.empty())
        return c->sendMessage(ERR_NOTEXTTOSEND, "No text to send.");
    if (argv[0][0] == '#')
    {
        if (!s->chanExist(argv[0]))
            return c->sendMessage(ERR_NOSUCHCHANNEL, "Invalid channel.");
        if (!this->s->isInChan(argv[0], c->getNickname()))
            return c->sendMessage(ERR_USERNOTINCHANNEL, c->getNickname() + " " + argv[1] + " :They aren't on that channel");
        Channel *chan = s->getChannels()[argv[0]];
        chan->sendOnChannel(c->to_string(false) + " PRIVMSG " + argv[0] + " :" + str, c, 0);
    }
    else
    {
        if (!s->userExist(argv[0]))
            return c->sendMessage(ERR_NOSUCHNICK, "Invalid user.");
        Client *u = s->getUser(argv[0]);
        u->sendRawMessage(c->to_string(false) + " PRIVMSG " + u->getNickname() + " :" + str);
    }
    return 0;
}