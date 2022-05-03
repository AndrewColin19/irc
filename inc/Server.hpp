#pragma once

#include "includes.h"
#include "Client.hpp"
#include "Channel.hpp"
#include "Commands/CommandManager.hpp"
#include "Commands/CommandPass.hpp"
#include "Commands/CommandUser.hpp"
#include "Commands/CommandNick.hpp"
#include "Commands/CommandPing.hpp"
#include "Commands/CommandQuit.hpp"
#include "Commands/CommandOper.hpp"
#include "ChannelManager.hpp"

#define MAX_MSIZE 2048

class Server
{
    private:
        int sock;
        struct addrinfo *addr;
        std::string password;
        std::string opass;
        fd_set set;
        fd_set save;
        int max_fd;
        CommandManager cmdManager;
        ChannelManager chanManager;
        std::map<int, Client*> users;
        std::map<std::string, Channel*> chan;
        void create_connection();
        void check_action();
        int  get_fd();
    public:
        Server(char *port, std::string password, std::string opass);
        void start();
        int userExist(string user);
        std::map<std::string, Channel*> getChannels();
        std::map<int, Client*> getClients();
        int removeClient(int fd);
        string getPassword();
        string getOPassword();
        bool chanExist(std::string chanName);
        bool isInChan(std::string chanName, std::string username);
        ~Server();
};