#include "Server.hpp"

Server::Server(char *port, std::string password, std::string opass)
{
    struct addrinfo	hints;
    memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
    getaddrinfo("127.0.0.1", port, &hints, &addr);
    this->password = password;
    this->opass = opass;

    cmdManager.add("PASS", new CommandPass(this));
    cmdManager.add("USER", new CommandUser(this));
    cmdManager.add("NICK", new CommandNick(this));
    cmdManager.add("PING", new CommandPing(this));
    cmdManager.add("QUIT", new CommandQuit(this));
    cmdManager.add("OPER", new CommandOper(this));
    cmdManager.add("KICK", new CommandKick(this));
    cmdManager.add("MODE", new CommandMode(this));
    cmdManager.add("PRIVMSG", new CommandPrivmsg(this));
    cmdManager.add("JOIN", new CommandJoin(this));

    chanManager.add("#Bienvenue", NULL);
}

void Server::start()
{
    this->sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    bind(this->sock, this->addr->ai_addr, this->addr->ai_addrlen);
    listen(sock, 10);
    FD_ZERO(&set);
    FD_ZERO(&save);
    FD_SET(sock, &set);
    max_fd = sock;
    while (1)
    {
        save = set;
        select(max_fd + 1, &save, NULL, NULL, NULL);
        check_action();
    }
}

int Server::get_fd()
{
    int i = 0;

    while (i <= max_fd)
    {
        if (FD_ISSET(i, &save))
            return i;
        i++;
    }
    return (i);
}

void Server::check_action()
{
    char buff[MAX_MSIZE];
    ssize_t nbread = 0;
    int fd = this->get_fd();

    if (fd == sock)
        create_connection();
    else
    {
        memset(buff, 0, sizeof buff);
        nbread = recv(fd, buff, MAX_MSIZE, 0);
        if (nbread <= 0)
        {
            close(fd);
            FD_CLR(fd, &set);
            users.erase(users.find(fd));
        }
        else
        {
            size_t pos = 0;
            std::string c;
            string str(buff);
            while ((pos = str.find('\n')) != std::string::npos)
            {
                c = str.substr(0, pos);
                str.erase(0, pos + 1);
                cmdManager.exec(c, users[fd]);
            }
        }
    }
}

string Server::getPassword()
{
    return password;
}

std::map<std::string, Channel*> Server::getChannels()
{
    return this->chan;
}

std::map<int, Client*> Server::getClients()
{
    return this->users;
}

int Server::removeClient(int fd)
{
    if (this->users.at(fd))
    {
        this->users.erase(fd);
        return (1);
    }
    return (0);
}

bool Server::chanExist(std::string chanName)
{
    if (chan.at(chanName))
        return (true);
    return (false);
}

bool Server::isInChan(std::string chanName, std::string username)
{
    if (chanExist(chanName))
    {
        if(chan.at(chanName)->isIn(username))
            return (true);
        return (false);
    }
    return (false);
}

int Server::userExist(string user)
{
    for (std::map<int, Client *>::iterator it = users.begin(); it != users.end(); ++it)
        if(it->second->getUsername() == user)
            return (1);
    return (0);
}

Client *Server::getUser(string user)
{
    for (std::map<int, Client *>::iterator it = users.begin(); it != users.end(); ++it)
        if(it->second->getUsername() == user)
            return (it->second);
    return (NULL);
}

void Server::create_connection()
{
    struct sockaddr_in address;
    socklen_t addr_len;
    addr_len = sizeof address;
    int client = accept(sock, (struct sockaddr *) &address, &addr_len);
    if (client > max_fd)
        max_fd = client;
    FD_SET(client, &set);
    users.insert(std::pair<int, Client*>(client, new Client(client, address)));
}

ChannelManager Server::getChanManager()
{
    return this->chanManager;
}

string  Server::getOPassword()
{
    return opass;
}