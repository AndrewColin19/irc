#pragma once
#include "includes.h"
#include "../Server.hpp"
#include "../Client.hpp"

class Server;
class Command
{
    protected:
        Server *s;
        std::vector<std::string> argv;
        std::string cmd;
        std::string str;
    public:
        int getCommand(std::string str, Client *c);
        virtual int exec(Client *c) = 0;
        virtual ~Command();
};