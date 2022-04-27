#include "Commands/CommandUser.hpp"

CommandUser::CommandUser(Server *srv)
{
    this->s = srv;
}

CommandUser::~CommandUser() {}

int CommandUser::exec(Client *c)
{
	if (c->isConnected())
		return !c->sendMessage("462", ":Unauthorized command (already registered)");

	if (this->argv.size() < 5)
		return !c->sendMessage("461", ":Not enough parameters");

	if (c->getUsername() == "")
	{
		c->setUsername(this->argv[1]);
		c->setHostname(this->argv[3]);
		c->setRealname(this->argv[4]);
	}

	return 0;
}