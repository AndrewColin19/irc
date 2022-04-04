#pragma once
#include "includes.h"

class Command
{
    private:
        std::vector<std::string> argv;
        std::string cmd;
    public:
        Command(std::string str);
        ~Command();
        vector<string> getArgv();
};

Command::Command(string str)
{
    size_t pos = 0;
    string token;
    std::string delimiter = " ";

    while ((pos = str.find(delimiter)) != string::npos) 
    {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        argv.push_back(token);
    }
}

Command::~Command() {}

vector<string> Command::getArgv()
{ return this->argv;}