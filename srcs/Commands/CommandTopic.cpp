#include "Commands/CommandTopic.hpp"

CommandTopic::CommandTopic(Server *srv)
{
    this->s = srv;
}

CommandTopic::~CommandTopic()
{}

int CommandTopic::exec(Client *c)
{
    if (this->argv.size() != 1)
        return c->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");
    if (!this->s->chanExist(this->argv[0]))
        return c->sendMessage(ERR_NOSUCHCHANNEL, argv[0] + ":No such channel");
    if (!this->s->isInChan(this->argv[1], c->getUsername()))
        return c->sendMessage(ERR_NOTONCHANNEL, ":You're not on that channel");
    Channel *ch = this->s->getChannels()[argv[0]];
    ch->setTopic(str);
    std::vector<Client *> clients = ch->getUsers();
    for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
        (*it)->sendRawMessage("TOPIC " + str);
    return 0;
}