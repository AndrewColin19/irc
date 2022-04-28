#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandMode : public Command
{
    private:
        Server *s;
    public:
        CommandMode(Server *s);
        ~CommandMode();
        int exec(Client *c);
};