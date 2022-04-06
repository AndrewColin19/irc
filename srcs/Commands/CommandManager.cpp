#include "Commands/CommandManager.hpp"

CommandManager::CommandManager()
{}

void CommandManager::add(string str, Command *c)
{
    cmds.insert(pair<string, Command*>(str, c));
}

int CommandManager::exec(string str, Client *c)
{
    string cmd;

    cmd = str.substr(0, str.find(' '));
    return (cmds[cmd]->getCommand(str, c));
}