#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>


int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage : ./ircserv <PORT> <PASSWORD>" << std::endl;
        return 0;
    }
    int port = std::atoi(av[1]);
    std::string password = av[2];
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    int addrlen =  sizeof(addr);
    bind(sock, (struct sockaddr *) &addr, addrlen);
    while (1)
    {
        if (listen(sock, 1))
            accept(sock, (struct sockaddr *) &addr, (socklen_t*) &addrlen);
    }

    return 1;
}