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

    std::vector<std::string> splited;
    size_t pos = 0;
    while ((pos = argv[0].find(',')) != std::string::npos) 
    {
        splited.insert(argv[0].substr(0, pos));
        argv[0].erase(0, pos + 1);
    }
    for (std::vector<std::string>::iterator it = splited.begin(); it != splited.end(); it++)
    {
        if ((*it)[0] == '#')
        {
            if (this->s->chanExist((*it)))
                this->s->getChannels().at((*it))->join(c);
            else
                this->s->getChanManager().add((*it), c);
        }
        else
            return c->sendMessage(ERR_NOSUCHCHANNEL, argv[0] + ":No such channel");
    }
    
    return 0;
}