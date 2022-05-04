#include "Commands/CommandMode.hpp"

CommandMode::CommandMode(Server *srv)
{
    this->s = srv;
}

CommandMode::~CommandMode()
{}

string modesToString(map<char, bool> mode)
{
    string m = "";

    for (map<char, bool>::iterator i = mode.begin(); i != mode.end(); i++)
    {
        if ((*i).second)
            m.append("+"), m.append(1, (*i).first), m.append(" ");
    }
    return m;
}

int CommandMode::exec(Client *c)
{
    if (argv.size() < 1 || argv.size() > 2)
        return c->sendMessage(ERR_NEEDMOREPARAMS, "Invalid params count.");
    if (this->argv[0][0] == '#')
    {
        if (!s->chanExist(argv[0]))
            return c->sendMessage(ERR_NOSUCHCHANNEL, "Invalid channel.");
        Channel *chan = (*s->getChannels().find(argv[0])).second;
        if (argv.size() == 1)
            return c->sendMessage(RPL_CHANNELMODEIS, modesToString(chan->getMode()));
        if (c != chan->getCreator() || c->isOper())
            return c->sendMessage(ERR_CHANOPRIVSNEEDED, "Invalid privileges on the channel.");
        for (int i = 1; i < argv[1].size(); i++)
        {
            if (argv[1][i] == 'i' || argv[1][i] == 'o' ||argv[1][i] == 'O' ||argv[1][i] == 'r' || argv[1][i] == 'w')
            {
                if (argv[1][0] == '+')
                    c->setMode(argv[1][i], 1);
                else
                    c->setMode(argv[1][i], 0);
            }
        } 
    }
    else
    {
        if (!this->s->userExist(this->argv[0]))
            return c->sendMessage(ERR_NOSUCHNICK, "Invalid user.");
        if (c->getNickname() != argv[0])
            return c->sendMessage(ERR_USERSDONTMATCH, "Invalid user.");
        if (argv.size() == 1)
            return c->sendMessage(RPL_UMODEIS, modesToString(c->getMode()));
        for (int i = 1; i < argv[1].size(); i++)
        {
            if (argv[1][i] == 'b' || argv[1][i] == 'e' ||argv[1][i] == 'l' ||argv[1][i] == 'i' || argv[1][i] == 'I' || argv[1][i] == 'k' || argv[1][i] == 'm' || argv[1][i] == 's')
            {
                if (argv[1][0] == '+')
                    c->setMode(argv[1][i], 1);
                else
                    c->setMode(argv[1][i], 0);
            }
        } 
    }
    return 0;
}