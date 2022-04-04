#pragma once
#ifndef __CHANNEL_HPP
#define __CHANNEL_HPP

#include "includes.h"
#include "Client.hpp"

class Channel
{
    private:
        std::string name;
        std::vector<Client> users;
    public:
        Channel();
};

#endif