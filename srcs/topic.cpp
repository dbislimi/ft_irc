#include "../includes/all.hpp"

void	Server::TOPIC(int fd, std::deque<std::string> cmd){
	size_t	size = cmd.size();

	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty()){
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return ;
	}
	if ()
	if (size == 1){
		mysend(fd, ":serveur 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n");
		return ;
	}
	if (_channels.find(cmd[1]) == _channels.end()){
		mysend(fd, ":serveur 403 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such channel\r\n");
		return ;
	}
	if (size == 2){
		if (_channels[cmd[1]]->getTopic().empty()){
			mysend(fd, ":serveur 331 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No topic is set\r\n");
		}
		else{
			mysend(fd, ":serveur 332 " + _clients[fd]->getNickName() + " " + cmd[1] + _channels[cmd[1]]->getTopic() + "\r\n");
			mysend(fd, ":serveur 333 " + _clients[fd]->getNickName() + " " + cmd[1] + " " + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " " + longToString(_channels[cmd[1]]->getTime()) + "\r\n");
		}
		return ;
	}
	if (_channels[cmd[1]]->isOp(fd) == false){
		mysend(fd, ":serveur 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n");
		return ;
	}
	std::string	topic = " " + catParam(cmd, 2);
	sendChannel(-1, cmd[1], ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " TOPIC " + cmd[1] + topic + "\r\n");
	_channels[cmd[1]]->setTopic(topic);
	_channels[cmd[1]]->setTime();
}