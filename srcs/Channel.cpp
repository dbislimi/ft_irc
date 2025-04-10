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

bool	Channel::getInvitRestrict(){
	return(_invitRestrict);
}

void	Channel::setInvitRestrict(bool value){
	_invitRestrict = value;
}

std::string	Channel::getMdp(){
	return (_mdp);
}

void	Channel::setMdp(std::string w){
	_mdp = w;
}

bool		Channel::getIsmdp(){
	return _ismdp;
}

void		Channel::setIsmdp(bool val){
	_ismdp = val;
}

int			Channel::getLimitUser(){
	return _limitUser;
}

void		Channel::setLimitUser(int val){
	_limitUser = val;
}