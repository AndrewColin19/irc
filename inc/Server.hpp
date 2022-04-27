#pragma once

#include "includes.h"
#include "Client.hpp"
#include "Channel.hpp"
#include "Commands/CommandManager.hpp"
#include "Commands/CommandPass.hpp"
#include "Commands/CommandUser.hpp"
#include "ChannelManager.hpp"

#define MAX_MSIZE 2048

class Server
{
    private:
        int sock;
        struct addrinfo *addr;
        std::string password;
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
        Server(char *port, std::string password);
        void start();
        int userExist(string user);
        std::map<std::string, Channel*> getChannels();
        std::map<int, Client*> getClients();
        string getPassword();
        ~Server();
};