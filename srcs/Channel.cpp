#include "../includes/all.hpp"

void	Channel::add(int fd){
	this->_users.push_back(fd);
}

void	Channel::sendChannel(int fd, std::string msg){
	for (std::vector<int>::iterator it = _users.begin(); it != _users.end(); ++it){
        if (*it == -1 || *it != fd)
		    send(*it, msg.c_str(), msg.length(), 0);
    }
}
