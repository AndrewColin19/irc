#pragma once
#include "includes.h"

class Client
{
    private:
        std::string username;
        int is_new;
        int is_connected;
        int fd;
    public:
        Client(int fd);
        int sendMessage(int err_code, string msg);
        void setUsername(std::string username);
        std::string getUsername();
        int isNew();
        int isConnected();
        int getFd();
        void connect();
};