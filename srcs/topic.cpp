#include "../includes/all.hpp"

void	Server::TOPIC(int fd, std::deque<std::string> cmd){
	size_t	size = cmd.size();
	std::map<std::string, Channel *>::iterator it;

	it = _channels.find(cmd[1]);

	if (it->second->getTopicRestrict() == false || _clients[fd]->getBoolOps() == true){
		if (_clients[fd]->getNickName().empty()){
			mysend(fd, ":server 451 * :You have not registered\r\n");
			return ;
		}
		if (_clients[fd]->getUserName().empty()){
			mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
			return ;
		}

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
	else
		mysend(fd, ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n");
}
