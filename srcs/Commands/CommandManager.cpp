#include "Commands/CommandManager.hpp"

CommandManager::CommandManager()
{}

CommandManager::~CommandManager()
{}

void CommandManager::add(string str, Command *c)
{
    cmds.insert(pair<string, Command*>(str, c));
}

int CommandManager::exec(string str, Client *c)
{
    cout << str << endl;
    string cmd;

    cmd = str.substr(0, str.find(' '));
    try
    {
        cmds.at(cmd);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Command invalid" << '\n';
        return 1;
    }
    return (cmds[cmd]->getCommand(str, c));
}