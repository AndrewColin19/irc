#include "Commands/CommandList.hpp"

CommandList::CommandList(Server *srv)
{
    this->s = srv;
}

CommandList::~CommandList()
{}

int CommandList::exec(Client *c)
{
    map<string, Channel*> chans = s->getChannels();
    c->sendMessage(RPL_LISTSTART, "Channel :Users Name");
    if (argv.size() == 0)
    {
        for (map<string, Channel*>::iterator it = chans.begin(); it != chans.end(); it++)
            c->sendMessage(RPL_LIST, (*it).first + " " + to_string((*it).second->getUsers().size()) + " :" + (*it).second->getTopic());
    }
    else
    {
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
                c->sendMessage(RPL_LIST, *it + " " + to_string(chan->getUsers().size()) + " :" + chan->getTopic());
            }
            
        }
    }
    return c->sendMessage(RPL_LISTEND, ":End of /LIST");
}