#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandQuit : public Command
{
    private:
        Server *s;
    public:
        CommandQuit(Server *s);
        ~CommandQuit();
        int exec(Client *c);
};