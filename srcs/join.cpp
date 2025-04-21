#include "../includes/all.hpp"

bool Server::checkChannel(std::string value)
{
	std::map<std::string, Channel *>::iterator it = _channels.find(value);
	if (it == _channels.end())
		return false;
	return true;
}

void Server::joinChannel(std::string channel, int fd)
{
	std::string msg;

	_nbCliChannel[channel].insert(std::pair<std::string, int>(_clients[fd]->getNickName(), fd));
	sendChannel(-1, channel, ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " JOIN " + channel + "\r\n");
	if (!_channels[channel]->getTopic().empty())
		mysend(fd, ":server 332 " + _clients[fd]->getNickName() +  " " + channel + _channels[channel]->getTopic() +"\r\n");
	msg = ":" + _name + " 353 " + _clients[fd]->getNickName() + " = " + channel + " :";
	for (std::map<std::string, int>::iterator it = _nbCliChannel[channel].begin(); it != _nbCliChannel[channel].end(); ++it)
	{
		if (_channels[channel]->isOp(it->second))
			msg += "@" + _clients[it->second]->getNickName() + " ";
		else 
			msg += _clients[it->second]->getNickName() + " ";
	}
	mysend(fd, msg + "\r\n");
	mysend(fd, ":server 366 " + _clients[fd]->getNickName() +  " " + channel + " :End of /NAMES list\r\n");
}

void Server::createChannel(int op, std::string value)
{
	Channel *channel = new Channel(op, value);
	_channels.insert(std::pair<std::string, Channel *>(value, channel));
	channel->setInvitRestrict(false);
	channel->setIsmdp(false);
	channel->setTopicRestrict(false);
	channel->setisLimitUser(false);
}

void Server::JOIN(int fd, std::deque<std::string> cmd)
{
	std::deque<std::string>	channels;
	std::deque<std::string>	keys;

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
	channels = split(cmd[1], ",");
	if (cmd.size() > 2)
		keys = split(cmd[2], ",");
	for (size_t	i = 0; i < channels.size(); ++i){
		if ((*(channels.begin() + i))[0] != '#')
			mysend(fd, ":server 403 " + _clients[fd]->getNickName() +  " " + *(channels.begin() + i) + " :No such channel\r\n");
		else{
			if (!checkChannel(*(channels.begin() + i)))
				createChannel(fd, *(channels.begin() + i));
			if (_channels[*(channels.begin() + i)]->getIsmdp() == true && (cmd.size() <= 2 || i >= keys.size() || *(keys.begin() + i) != _channels[*(channels.begin() + i)]->getMdp())){
				mysend(fd, ":server 475 " + _clients[fd]->getNickName() +  " " + *(channels.begin() + i) + " :Cannot join channel (+k)\r\n");
				continue ;
			}
			if (_channels[*(channels.begin() + i)]->getisLimitUser() == true && _nbCliChannel[*(channels.begin() + i)].size() >= static_cast<size_t>(_channels[*(channels.begin() + i)]->getLimitUser())){
				mysend(fd, ":server 471 " + _clients[fd]->getNickName() +  " " + *(channels.begin() + i) + " :Cannot join channel (+l)\r\n");
				continue ;
			}
			joinChannel(*(channels.begin() + i), fd);
		}
	}
}
