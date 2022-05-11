#include "Commands/CommandMode.hpp"

CommandMode::CommandMode(Server *srv)
{
    this->s = srv;
}

CommandMode::~CommandMode()
{}

string modesToString(map<char, bool> mode)
{
    stringstream m;

    m << " ";
    for (map<char, bool>::iterator i = mode.begin(); i != mode.end(); i++)
    {
        if ((*i).second)
            m << "+" << (*i).first << " ";
    }
    return m.str();
}

int CommandMode::exec(Client *c)
{
    if (argv.size() < 1 || argv.size() > 2)
        return c->sendMessage(ERR_NEEDMOREPARAMS, ":Invalid params count.");
    if (this->argv[0][0] == '#')
    {
        if (!s->chanExist(argv[0]))
            return c->sendMessage(ERR_NOSUCHCHANNEL, ":Invalid channel.");
        Channel *chan = (*s->getChannels().find(argv[0])).second;
        if (argv.size() == 1)
            return c->sendMessage(RPL_CHANNELMODEIS, modesToString(chan->getMode()));
        if (c != chan->getCreator() || !c->isOper())
            return c->sendMessage(ERR_CHANOPRIVSNEEDED, ":Invalid privileges on the channel.");
        if (argv[1][0] == '+')
            c->setMode(argv[1][1], 1);
        else if (argv[1][0] == '-')
            c->setMode(argv[1][1], 0);
    }
    else
    {
        if (!this->s->userExist(this->argv[0]))
            return c->sendMessage(ERR_NOSUCHNICK, ":Invalid user.");
        if (c->getNickname() != argv[0])
            return c->sendMessage(ERR_USERSDONTMATCH, ":Invalid user.");
        if (argv.size() == 1)
            return c->sendMessage(RPL_UMODEIS, argv[0] + modesToString(c->getMode()));
        if (argv[1][0] == '+')
            c->setMode(argv[1][1], 1);
        else if (argv[1][0] == '-')
            c->setMode(argv[1][1], 0);
    }
    return c->sendRawMessage(c->to_string(false) + " MODE " + argv[0] + " " + argv[1][0] + argv[1][1]);
}