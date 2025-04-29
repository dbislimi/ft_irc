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

long			Channel::getLimitUser(){
	return _limitUser;
}

void		Channel::setLimitUser(long val){
	_limitUser = val;
}

void		Channel::setTopicRestrict(bool val){
	_isTopicRestrict = val;
}

bool		Channel::getTopicRestrict(){
	return (_isTopicRestrict);
}

void	Channel::setTime(){
	_timestamp = std::time(NULL);
}

std::time_t	Channel::getTime() const{
	return (_timestamp);
}

void		Channel::setTopic(std::string topic){
	_topic = topic;
}

std::string	Channel::getTopic() const{
	return (_topic);
}

bool		Channel::getisLimitUser(){
	return _isLimitUser;
}

void		Channel::setisLimitUser(bool val){
	_isLimitUser = val;
}

void		Channel::updateModes(std::deque<std::string> cmd){
	char mode = cmd[2][1];

	if (cmd[2][0] == '+')
		_modes.push_back(mode);
	else{
		size_t pos = _modes.find(mode);
		if (pos != std::string::npos)
			_modes.erase(pos, 1);
	}
}

std::string	Channel::getModes(){
	std::string str = "";
	bool		k = 0;
	bool		l = 0;

	for (size_t i = 0; i < _modes.size(); ++i){
		if (_modes[i] == 'k')
			k = 1;
		else if (_modes[i] == 'l')
			l = 1;
		else
			str += _modes[i];
	}
	if (l)
		str += "l";
	if (k)
		str += 'k';
	if (l)
		str += " " + longToString(_limitUser);
	if (k)
		str += " " + _mdp;
	return (str);
}

// bool	Channel::getInvitRestrict(){
// 	return(_invitRestrict);
// }

// void	Channel::setInvitRestrict(bool value){
// 	_invitRestrict = value;
// }

// std::string	Channel::getMdp(){
// 	return (_mdp);
// }

// void	Channel::setMdp(std::string w){
// 	_mdp = w;
// }

// bool		Channel::getIsmdp(){
// 	return _ismdp;
// }

// void		Channel::setIsmdp(bool val){
// 	_ismdp = val;
// }

// size_t			Channel::getLimitUser(){
// 	return _limitUser;
// }

// void		Channel::setLimitUser(size_t val){
// 	_limitUser = val;
// }

// void		Channel::setTopicRestrict(bool val){
// 	_isTopicRestrict = val;
// }

// bool		Channel::getTopicRestrict(){
// 	return (_isTopicRestrict);
// }

// void	Channel::setTime(){
// 	_timestamp = std::time(NULL);
// }

// std::time_t	Channel::getTime() const{
// 	return (_timestamp);
// }

// void		Channel::setTopic(std::string topic){
// 	_topic = topic;
// }

// std::string	Channel::getTopic() const{
// 	return (_topic);
// }

// bool		Channel::getisLimitUser(){
// 	return _isLimitUser;
// }

// void		Channel::setisLimitUser(bool val){
// 	_isLimitUser = val;
// }

// void		Channel::updateModes(std::deque<std::string> cmd){
// 	char mode = cmd[2][1];

// 	if (cmd[2][0] == '+')
// 		_modes.push_back(mode);
// 	else{
// 		size_t pos = _modes.find(mode);
// 		if (pos != std::string::npos)
// 			_modes.erase(pos, 1);
// 	}
// }

// std::string	Channel::getModes(){
// 	std::string str = "";
// 	bool		k = 0;
// 	bool		l = 0;

// 	for (size_t i = 0; i < _modes.size(); ++i){
// 		if (_modes[i] == 'k')
// 			k = 1;
// 		else if (_modes[i] == 'l')
// 			l = 1;
// 		else
// 			str += _modes[i];
// 	}
// 	if (l)
// 		str += "l";
// 	if (k)
// 		str += 'k';
// 	if (l)
// 		str += " " + longToString(_limitUser);
// 	if (k)
// 		str += " " + _mdp;
// 	return (str);
// }

void Channel::setChannelOnInvited(bool channelOnInvited){
    this->_channelOnInvited = channelOnInvited;
}

bool Channel::getChannelOnInvited(){
    return this->_channelOnInvited;
}

// void Channel::setChannelOnInvited(bool channelOnInvited){
//     this->_channelOnInvited = channelOnInvited;
// }

// bool Channel::getChannelOnInvited(){
//     return this->_channelOnInvited;
// }
std::string Channel::getName(){
	return _name;
}

void		Channel::setLstInvit(std::string val){
	_lstInvit.push_back(val);
}

void		Channel::removeFromLstI(std::string nash){
	for(std::vector<std::string>::iterator it = _lstInvit.begin(); it != _lstInvit.end(); ++it){
		if (*it == nash){
			_lstInvit.erase(it);
			return ;
		}
	}
	std::cout << "CA PRINT ICI ?? " << std::endl;
}

bool		Channel::checkLstI(std::string nm){
	for (std::vector<std::string>::iterator it = _lstInvit.begin(); it != _lstInvit.end(); ++it){
		if (*it == nm){
			return true;
		}
	}
	return false;
}