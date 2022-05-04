#include "Commands/CommandJoin.hpp"

CommandJoin::CommandJoin(Server *srv)
{
    this->s = srv;
}

CommandJoin::~CommandJoin()
{}

int CommandJoin::exec(Client *c)
{
    if (argv.size() != 1)
        return c->sendMessage(ERR_NEEDMOREPARAMS, "Not enough parameters");

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
        if ((*it)[0] == '#')
        {
            if (s->chanExist(*it))
                s->getChannels()[*it]->join(c);
            else
                s->addChannel(*it, c);
        }
        else
            return c->sendMessage(ERR_NOSUCHCHANNEL, argv[0] + ":No such channel");
    }
    
    return 0;
}