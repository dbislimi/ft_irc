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
	_nbCliChannel[value].insert(std::pair<std::string, int>(_clients[fd]->getNickName(), fd));
	std::string msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + value + "\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
	msg = ":" + _name + " 353 " + _clients[fd]->getNickName() + " = " + value + " :";
	for (std::map<std::string, int>::iterator it = _nbCliChannel[value].begin(); it != _nbCliChannel[value].end(); ++it)
	{
        if (_channels[value]->isOp(it->second)) {
            msg += "@" + _clients[it->second]->getNickName() + " ";
        } else {
            msg += _clients[it->second]->getNickName() + " ";
        }
	}
	msg += "\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
    msg = ":" + _name +  " 366 " + _clients[fd]->getNickName() + " " + value + " :End of /NAMES list.\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
    msg = ":" + _name +  " 324 " + _clients[fd]->getNickName() + " " + value + " :+nt\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
    msg = ":" + _name +  " 329 " + _clients[fd]->getNickName() + " " + value + " :1743783418\r\n"; 
    send(fd, msg.c_str(), msg.length(), 0);
    msg = ":" + _name +  " 354 " + _clients[fd]->getNickName() + " 152 " + value + " " + _clients[fd]->getNickName() + " " + _clients[fd]->getIp() + "\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
	for (std::map<std::string, int>::iterator it = _nbCliChannel[value].begin(); it != _nbCliChannel[value].end(); ++it)
	{
		if (it->second != fd)
		{
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + value + "\r\n";
			send(it->second, msg.c_str(), msg.length(), 0);
		}
	}
}

void Server::createChannel(int op, std::string value)
{
	Channel *channel = new Channel(op, value);
	_channels.insert(std::pair<std::string, Channel *>(value, channel));
}

void Server::JOIN(int fd, std::deque<std::string> cmd)
{
	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":server 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}

	if (cmd.size() == 1){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	std::string msg = "Please add # after /join\r\n";
	if (cmd[1][0] != '#')
		send(fd, msg.c_str(), msg.length(), 0);
	else
	{
		if (!checkChannel(cmd[1]))
			createChannel(fd, cmd[1]);
		joinChannel(cmd[1], fd);
	}
}