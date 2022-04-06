#include "Commands/Command.hpp"

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
    return (exec(c));
}

Command::~Command() {}