#include "Commands/CommandUser.hpp"

CommandUser::CommandUser(Server *srv)
{
    this->s = srv;
}

CommandUser::~CommandUser() {}

int CommandUser::exec(Client *c)
{
	if (c->isConnected())
		return !c->sendMessage(ERR_ALREADYREGISTRED, ":Unauthorized command (already registered)");
	if (this->argv.size() < 3)
		return !c->sendMessage(ERR_NEEDMOREPARAMS, ":Not enough parameters");
	if (c->getUsername() == "")
	{
		c->setUsername(this->argv[0]);
		c->setHostname(this->argv[2]);
		c->setRealname(this->str);
	}
	c->connect();
	return 0;
}