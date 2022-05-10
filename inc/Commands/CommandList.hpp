#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandList : public Command
{
    private:
        Server *s;
    public:
        CommandList(Server *s);
        ~CommandList();
        int exec(Client *c);
};