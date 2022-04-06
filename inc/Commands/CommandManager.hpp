#pragma once

#include "Client.hpp"
#include "Command.hpp"

class CommandManager
{
    private:
        map<string, Command*> cmds;
    public:
        CommandManager();
        ~CommandManager();
        void add(string str, Command *c);
        int exec(string str, Client *c);
};