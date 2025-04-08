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

int	Channel::getOp() const{
	return (_op);
}

bool	Channel::findUser(std::string nick) {
	for (std::map<std::string, int>::iterator it = _users.begin(); it != _users.end(); ++it){
		if (it->first == nick)
			return (true);
	}
	return (false);
}

void	Channel::kick(std::string nick){
	_users.erase(nick);
}