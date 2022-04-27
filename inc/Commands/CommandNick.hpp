#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandNick : public Command
{
    private:
        Server *s;
    public:
        CommandNick(Server *s);
        ~CommandNick();
        int exec(Client *c);
};