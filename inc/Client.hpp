#pragma once
#include "includes.h"

class Client
{
    private:
        std::string username;
        std::string hostname;
        std::string realname;
        std::string nickname;
        int is_new;
        int is_connected;
        int fd;
        struct sockaddr address;
    public:
        Client(int fd, struct sockaddr address);
        int sendMessage(string err_code, string msg);
        int sendRawMessage(std::string message);
        void setUsername(std::string username);
        std::string getUsername();
        void setHostname(std::string hostname);
        std::string getHostname();
        void setRealname(std::string realname);
        std::string getRealname();
        void setNickname(std::string nickname);
        std::string getNickname();
        int isNew();
        int isConnected();
        int getFd();
        void connect();
        std::string	to_string(bool isAnon) const;
};