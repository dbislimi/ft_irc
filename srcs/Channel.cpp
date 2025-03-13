#include "../includes/Channel.hpp"

void	Channel::add(int fd){
	this->_users.push_back(fd);
}

void	Channel::sendChannel(std::string msg){
	for (std::vector<int>::iterator it = _users.begin(); it != _users.end(); ++it)
		send(*it, msg.c_str(), msg.length(), 0);
}
