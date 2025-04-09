#include "../includes/all.hpp"

bool	Channel::isOp(int fd){
	for (std::deque<int>::iterator it = _ops.begin(); it != _ops.end(); ++it)
		if (*it == fd)
			return (true);
	return (false);
}

void	Channel::removeOp(int fd){
	for (std::deque<int>::iterator it = _ops.begin(); it != _ops.end(); ++it){
		if (*it == fd){
			_ops.erase(it);
			return ;
		}
	}
}

void    Channel::addOp(int fd){
    _ops.push_back(fd);
}
