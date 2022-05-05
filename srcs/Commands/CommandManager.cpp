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
    string cmd;

    cout << str << endl;
    cmd = str.substr(0, str.find(' '));
    if (cmd == "CAP")
        return 0;
    else if (!c->isPassed())
    {
        if (cmd != "PASS")
            return c->sendMessage(ERR_NOTREGISTERED, "You have not registered."); 
    }
    else if (!c->isConnected() && cmd != "USER" && cmd != "NICK")
        return c->sendMessage(ERR_NOTREGISTERED, "You have not registered.");
    try
    {
        cmds.at(cmd);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Command invalid : " << str << '\n';
        return 1;
    }
    return (cmds[cmd]->getCommand(str, c));
}