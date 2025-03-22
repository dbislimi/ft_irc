#include "../includes/all.hpp"

bool Server::checkChannel(std::string value)
{
	std::map<std::string, Channel *>::iterator it = _channels.find(value);
	if (it == _channels.end())
		return false;
	return true;
}

void Server::joinChannel(std::string value, int fd)
{
	_nbCliChannel[value].insert(fd);

	std::string msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + value + "\r\n";
	send(fd, msg.c_str(), msg.length(), 0);

	msg = _clients[fd]->getNickName() + " " + value + " :Bienvenue sur " + value + " !\r\n";
	send(fd, msg.c_str(), msg.length(), 0);

	msg = _clients[fd]->getNickName() + " = " + value + " :";
	for (std::set<int>::iterator it = _nbCliChannel[value].begin(); it != _nbCliChannel[value].end(); ++it)
	{
		msg += _clients[*it]->getNickName() + " ";
	}
	msg += "\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
	msg =  _clients[fd]->getNickName() + " " + value + " :End of NAMES list\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
	for (std::set<int>::iterator it = _nbCliChannel[value].begin(); it != _nbCliChannel[value].end(); ++it)
	{
		if (*it != fd)
		{
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + value + "\r\n";
			send(*it, msg.c_str(), msg.length(), 0);
		}
	}
}

void Server::createChannel(std::string value)
{
	Channel *channel;
	_channels.insert(std::pair<std::string, Channel *>(value, channel));
}

void Server::JOIN(int fd, std::string value)
{
	std::string msg = "Please add # after /join\r\n";
	if (value[0] != '#')
		send(fd, msg.c_str(), msg.length(), 0);
	else
	{
		if (!checkChannel(value))
			createChannel(value);
		joinChannel(value, fd);
	}
}