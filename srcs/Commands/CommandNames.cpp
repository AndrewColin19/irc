#include "Commands/CommandNames.hpp"

CommandNames::CommandNames(Server *srv)
{
    this->s = srv;
}

CommandNames::~CommandNames()
{}

int CommandNames::exec(Client *c)
{
    if (argv.size() != 1)
        return c->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");

    vector<string> splited;
    size_t pos = 0;
    while ((pos = argv[0].find(',')) != string::npos) 
    {
        splited.push_back(argv[0].substr(0, pos));
        argv[0].erase(0, pos + 1);
    }
    splited.push_back(argv[0]);
    for (vector<string>::iterator it = splited.begin(); it != splited.end(); it++)
    {
        if (s->chanExist(*it))
        {
            Channel *chan = s->getChannels()[*it];
            c->sendMessage(RPL_NAMREPLY, "= " + *it + " :" + chan->listUsers());
            c->sendMessage(RPL_ENDOFNAMES, *it + " :End of NAMES list");
        }
        else
            return c->sendMessage(RPL_ENDOFNAMES, argv[0] + " :No such channel");
    }
    
    return 0;
}