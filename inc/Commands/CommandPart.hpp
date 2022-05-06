#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandPart : public Command
{
    private:
        Server *s;
    public:
        CommandPart(Server *s);
        ~CommandPart();
        int exec(Client *c);
};