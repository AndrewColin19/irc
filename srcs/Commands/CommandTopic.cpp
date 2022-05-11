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
    if (!this->s->isInChan(this->argv[0], c->getUsername()))
        return c->sendMessage(ERR_NOTONCHANNEL, ":You're not on that channel");
    Channel *ch = this->s->getChannels()[argv[0]];
    if (!isstr)
    {
        if (ch->getTopic().empty())
            c->sendMessage(RPL_NOTOPIC, argv[0] + " :No topic is set");
        else
        {
            c->sendMessage(RPL_TOPIC, argv[0] + " :" + ch->getTopic());
            c->sendMessage("333", argv[0] + " " + ch->getTopicSetter() + " " + to_string(ch->getTopicSetted()));
        }
    }
    else
    {
        map<char, bool> m = ch->getMode();
        bool t = m.find('t') == m.end() ? 0 : m['t'];
        if (!t || c->isOper())
        {
            ch->setTopic(str);
            ch->setTopicSetter(c->getUsername());
            ch->getTopicSetted();
            std::vector<Client *> clients = ch->getUsers();
            for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
                (*it)->sendRawMessage(":" + c->getNickname() + " TOPIC " + argv[0] + " :" + str);
        }
        else
            c->sendMessage(ERR_CHANOPRIVSNEEDED, argv[0] + " :You're not channel operator");
    }
    return 0;
}