#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandKick : public Command
{
    private:
        Server *s;
    public:
        CommandKick(Server *s);
        ~CommandKick();
        int exec(Client *c);
};