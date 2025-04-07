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
    _channels[value]->add(fd);

    std::string msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + value + "\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
    msg = ":" + _name + " 353 " + _clients[fd]->getNickName() + " = " + value + " :";
    for (std::set<int>::iterator it = _nbCliChannel[value].begin(); it != _nbCliChannel[value].end(); ++it)
    {
        if (*it != fd){
            msg += _clients[*it]->getNickName() + " ";
        }
        // if (*it == fd) {
        //     msg += "@" + _clients[*it]->getNickName() + " ";
        // } else {
        //     msg += _clients[*it]->getNickName() + " ";
        // }
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
    for (std::set<int>::iterator it = _nbCliChannel[value].begin(); it != _nbCliChannel[value].end(); ++it)
    {
        if (*it != fd)
        {
            msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + value + "\r\n";
            send(*it, msg.c_str(), msg.length(), 0);
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
	if (cmd.size() == 1){
		mysend(fd, "Usage: JOIN <channel>, joins the channel\r\n", 0);
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