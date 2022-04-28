#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandPing : public Command
{
    private:
        Server *s;
    public:
        CommandPing(Server *s);
        ~CommandPing();
        int exec(Client *c);
};