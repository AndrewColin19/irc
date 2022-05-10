#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandInvite : public Command
{
    private:
        Server *s;
    public:
        CommandInvite(Server *s);
        ~CommandInvite();
        int exec(Client *c);
};