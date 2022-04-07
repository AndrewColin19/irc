#pragma once
#include "includes.h"
#include "../Client.hpp"

class Command
{
    protected:
        std::vector<std::string> argv;
        std::string cmd;
        std::string str;
    public:
        int getCommand(std::string str, Client *c);
        virtual int exec(Client *c) = 0;
        virtual ~Command();
};