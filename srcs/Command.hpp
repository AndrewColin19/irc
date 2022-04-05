#pragma once

#include "includes.h"

#include "Server.hpp"
#include "Client.hpp"

class Server;

class Command
{
    private:
        Server *s;
        std::vector<std::string> argv;
        map<string, function<int(Client *)> > commands;
        std::string cmd;
        std::string str;
        int pass(Client *c);
    public:
        Command(Server *s);
        int getCommand(std::string str, Client *c);
        ~Command();
};

Command::Command(Server *s)
{
    this->s = s;
    commands.insert(pair<string, function<int(Client *)> >("PASS", pass));
}

int Command::getCommand(string str, Client *c)
{
    size_t pos = 0;
    string token;
    cmd = nullptr;
    str = nullptr;
    argv.erase(argv.begin());

    if ((pos = str.find(':')) != string::npos)
    {
        this->str = str.substr(pos + 1);
        str.erase(pos);
    }
    if ((pos = str.find(' ')) != string::npos)
    {
        this->cmd = str.substr(0, pos);
        str.erase(0, pos + 1);
    }
    while ((pos = str.find(' ')) != string::npos) 
    {
        token = str.substr(0, pos);
        str.erase(0, pos + 1);
        argv.push_back(token);
    }
    //function<int(Client*)> f = commands[cmd];
    return (1);
}

Command::~Command() {}