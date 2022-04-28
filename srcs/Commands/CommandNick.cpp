#include "Commands/CommandNick.hpp"

static bool checkNicknameAnonymous(std::map<std::string, Channel*> channels, std::string nickname)
{
	for (std::map<std::string, Channel*>::const_iterator it = channels.begin(); it != channels.end(); it++) {
		if (/*it->second->isSetMode('a', "") && */ nickname == "anonymous")
			return (true);
	}
	return (false);
}

static bool checkNicknameAvailability(Server* server, std::string nickname)
{
	std::map<int, Client*> clients = server->getClients();
	std::map<int, Client*>::iterator begin = clients.begin();
	for (; begin != clients.end(); begin++)
		if (begin->second != NULL
			&& begin->second->isConnected()
			&& nickname == begin->second->getNickname())
			return false;
	return true;
}

static bool checkNicknameValidity(std::string nickname)
{
	if (nickname.size() > 9)
		return false;
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if (!std::isalpha(nickname[i]) && !std::isdigit(nickname[i]))
			return false;
	}
	return true;
}

CommandNick::CommandNick(Server *srv)
{
    this->s = srv;
}

CommandNick::~CommandNick()
{}

int CommandNick::exec(Client *c)
{
    if (c->isConnected()) //&& c->isMode('r'))
		return !c->sendMessage(ERR_RESTRICTED, "Your connection is restricted!");

	if (this->argv.size() != 1 || this->argv[0].length() == 0)
		return !c->sendMessage(ERR_NONICKNAMEGIVEN, "Not nickname given");

	if (!checkNicknameValidity(this->argv[0])
		|| checkNicknameAnonymous(this->s->getChannels(), this->argv[0]))
		return !c->sendMessage(ERR_ERRONEUSNICKNAME, "Erroneous nickname");

	if (!checkNicknameAvailability(this->s, this->argv[0]))
		return !c->sendMessage(ERR_NICKNAMEINUSE, "Nickname is already in use");

	if (!c->getNickname().empty())
		c->sendRawMessage(c->to_string(false) + " NICK :" + this->argv[0]);
	c->setNickname(this->argv[0]);
	return 0;
}
