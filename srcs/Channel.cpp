#include "../includes/all.hpp"

void	Channel::add(int fd){
	this->_users.push_back(fd);
}

void Channel::delete_user(int fd) {
    for (size_t i = 0; i < _users.size(); ++i) {
        if (_users[i] == fd) {
            std::swap(_users[i], _users.back());
            _users.pop_back();
            break;
        }
    }
}

void	Channel::sendChannel(int fd, std::string msg){
	for (std::vector<int>::iterator it = _users.begin(); it != _users.end(); ++it){
        if (*it != fd)
			send(*it, msg.c_str(), msg.length(), 0);
    }
}
