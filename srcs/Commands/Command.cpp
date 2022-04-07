#include "Commands/Command.hpp"

int Command::getCommand(string str, Client *c)
{
    size_t pos = 0;
    string token;
    cmd = "";
    this->str = "";
    if (argv.size() > 0)
        argv.erase(argv.begin());
    if ((pos = str.find(':')) != string::npos)
    {
        this->str = str.substr(pos + 1);
        str.erase(pos);
    }
    pos = str.find(' ');
    this->cmd = str.substr(0, pos);
    str.erase(0, pos);
    istringstream iss(str);
    vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
    argv = results;
    return (exec(c));
}

Command::~Command() {}