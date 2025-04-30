#include "../includes/all.hpp"

void	Server::INVITE(int fd, std::deque<std::string> cmd){
	if (cmd[2] == _name){
		mysend(fd, ":serveur 442 " + _clients[fd]->getNickName() + " :You're not on a channel\r\n");
		return ;
	}
	if (!_channels[cmd[2]]->isOp(fd)){
		mysend(fd, ":serveur 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n");
		return ;
	}
	if (cmd.size() < 3){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	if (!checkClient(cmd[1])){
		mysend(fd, ":serveur 401 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such nick\r\n");
		return ;
	}
	if (findUser(cmd[2], cmd[1]) == true){
		mysend(fd, ":serveur 443 " + _clients[fd]->getNickName() + " "  + cmd[1] + " " + cmd[2] + " :is already on channel");
		return ;
	}
	if (!checkChannel(cmd[2])){
		mysend(fd, ":server 403 " + _clients[fd]->getNickName() +  " " + cmd[2] + " :No such channel\r\n");
		return ;
	}
	if (_channels[cmd[2]]->checkLstI(cmd[1]) == false)
		_channels[cmd[2]]->setLstInvit(cmd[1]);
	std::map<int, Client*>::iterator it = _clients.begin();
	while (it != _clients.end()){
		if (it->second->getNickName() == cmd[1])
			break;
		it++;
	}
	mysend(it->second->getFd(), ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " INVITE " + cmd[1] + " "  + cmd[2] + "\r\n");
	mysend(fd, ":server 341 " + _clients[fd]->getNickName() +  " " + cmd[1] +  + " " + cmd[2] + "\r\n");
}