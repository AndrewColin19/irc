#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandPrivmsg : public Command
{
    private:
        Server *s;
    public:
        CommandPrivmsg(Server *s);
        ~CommandPrivmsg();
        int exec(Client *c);
};