#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "Command.hpp"

class CommandPass : public Command
{
    public:
        CommandPass(Server *s);
        ~CommandPass();
        int exec(Client *c);
};