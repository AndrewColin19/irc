#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandNames : public Command
{
    private:
        Server *s;
    public:
        CommandNames(Server *s);
        ~CommandNames();
        int exec(Client *c);
};