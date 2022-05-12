#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class Server;

class CommandNotice : public Command
{
    private:
        Server *s;
    public:
        CommandNotice(Server *s);
        ~CommandNotice();
        int exec(Client *c);
};