#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandPass : public Command
{
    private:
        Server *s;
    public:
        CommandPass(Server *s);
        ~CommandPass();
        int exec(Client *c);
};