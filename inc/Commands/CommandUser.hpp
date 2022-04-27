#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandUser : public Command
{
    private:
        Server *s;
    public:
        CommandUser(Server *s);
        ~CommandUser();
        int exec(Client *c);
};