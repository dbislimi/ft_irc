#include "../includes/all.hpp"

void	Server::TOPIC(int fd, std::deque<std::string> cmd){
	size_t	size = cmd.size();
	std::map<std::string, Channel *>::iterator it;

	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":" + _name + " 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":" + _name + " 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}
	if (size == 1){
		mysend(fd, ":" + _name + " 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n");
		return ;
	}
	it = _channels.find(cmd[1]);
	if (it == _channels.end()){
		mysend(fd, ":" + _name + " 403 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such channel\r\n");
		return ;
	}
	if (size == 2){
		if (_channels[cmd[1]]->getTopic().empty()){
			mysend(fd, ":" + _name + " 331 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No topic is set\r\n");
		}
		else{
			mysend(fd, ":" + _name + " 332 " + _clients[fd]->getNickName() + " " + cmd[1] + " :" + _channels[cmd[1]]->getTopic() + "\r\n");
			mysend(fd, ":" + _name + " 333 " + _clients[fd]->getNickName() + " " + cmd[1] + " " + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " " + longToString(_channels[cmd[1]]->getTime()) + "\r\n");
		}
		return ;
	}
	if (it->second->getTopicRestrict() == false || it->second->isOp(fd) == true){
		std::string	topic;
		size_t	begin = 1;

		for (std::deque<std::string>::iterator it = cmd.begin() + 2; it != cmd.end(); ++it){
			++begin;
			if ((*it)[0] == ':')
				break ;
		}
		topic = catParam(cmd, begin);
		if (topic[0] == ':')
			topic.erase(topic.begin());
		sendChannel(-1, cmd[1], ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " TOPIC " + cmd[1] + " :" + topic + "\r\n");
		_channels[cmd[1]]->setTopic(topic);
		_channels[cmd[1]]->setTime();
	}
	else
		mysend(fd, ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n");
}
