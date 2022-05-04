
#include "Server.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Usage : ./ircserv <PORT> <PASSWORD>" << std::endl;
        return 0;
    }
    int port = std::atoi(av[1]);
    std::string p = av[1];
    if (port < 0 || port > 65535 || !std::all_of(p.begin(), p.end(), ::isdigit))
    {
        std::cout << "Error : Port invalid." << std::endl;
        return 0;
    }
    Server *s = new Server(av[1], av[2], "abcdef");
    s->start();
    return 1;
}