#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandTopic : public Command
{
    private:
        Server *s;
    public:
        CommandTopic(Server *s);
        ~CommandTopic();
        int exec(Client *c);
};