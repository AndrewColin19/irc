#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandJoin : public Command
{
    private:
        Server *s;
    public:
        CommandJoin(Server *s);
        ~CommandJoin();
        int exec(Client *c);
};