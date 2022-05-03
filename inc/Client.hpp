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
        map<char, bool> modes;
        int oper;
        struct sockaddr_in address;
    public:
        Client(int fd, struct sockaddr_in address);
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
        void setOper(int b);
        int isOper();
        std::string	getAddress(void) const;
        int isNew();
        void setMode(string mode);
        int isConnected();
        int getFd();
        void connect();
        std::string	to_string(bool isAnon) const;
};