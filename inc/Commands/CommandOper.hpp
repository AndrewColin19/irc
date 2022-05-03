#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandOper : public Command
{
    private:
        Server *s;
    public:
        CommandOper(Server *s);
        ~CommandOper();
        int exec(Client *c);
};