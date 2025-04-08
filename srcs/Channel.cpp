#include "../includes/all.hpp"

void	Channel::add(int fd, std::string nick){
	this->_users.insert(std::pair<std::string, int>(nick, fd));
}

void	Channel::sendChannel(int fd, std::string msg){
	for (std::map<std::string, int>::iterator it = _users.begin(); it != _users.end(); ++it){
        if (fd == -1 || it->second != fd)
			send(it->second, msg.c_str(), msg.length(), 0);
    }
}

bool	Channel::isOp(int fd){
	for (std::deque<int>::iterator it = _ops.begin(); it != _ops.end(); ++it)
		if (*it == fd)
			return (true);
	return (false);
}

bool	Channel::findUser(std::string nick) {
	for (std::map<std::string, int>::iterator it = _users.begin(); it != _users.end(); ++it){
		if (it->first == nick)
			return (true);
	}
	return (false);
}

void	Channel::erase(std::string nick){
	for (std::deque<int>::iterator it = _ops.begin(); it != _ops.end(); ++it){
		if (*it == _users[nick]){
			_ops.erase(it);
			break ;
		}
	}
	_users.erase(nick);
}

std::map<std::string, int>	Channel::getUsers(){
	return (_users);
}