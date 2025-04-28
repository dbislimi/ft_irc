#include "../includes/all.hpp"

void	Server::INVITE(int fd, std::deque<std::string> cmd){
	if (cmd[2] == _name){
		mysend(fd, ":serveur 442 " + _clients[fd]->getNickName() + " :You're not on a channel\r\n");
		return ;
	}
	if (!_channels[cmd[2]]->isOp(fd)){
		mysend(fd, ":serveur 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Permission Denied- You're not an IRC operator\r\n");
		return ;
	}
	if (cmd.size() != 3){
		mysend(fd, "Usage: INVITE <nick> [<channel>], invites someone to a channel, by default the current channel\r\n");
		return ;
	}
	if (!checkClient(cmd[1])){
		mysend(fd, cmd[1] + " :No such nick\r\n");
		return ;
	}
	if (_clients[fd]->getNickName() == cmd[1]){
		mysend(fd, ":serveur 443 " + _clients[fd]->getNickName() + " " + cmd[2] + " :is already on channel");
		return ;
	}
	if (!checkChannel(cmd[2])){
		mysend(fd, cmd[2] + " :No such channel\r\n");
		return ;
	}
	std::map<int, Client*>::iterator ot = _clients.begin();
	while (ot != _clients.end()){
		if (ot->second->getFd() == fd)
			break;
		ot++;
	}
	std::map<int, Client*>::iterator it = _clients.begin();
	while (it != _clients.end()){
		if (it->second->getNickName() == cmd[1])
			break;
		it++;
	}
	it->second->setInvited(cmd[2], true);
	
	mysend(it->second->getFd(), "You have been invited to \00306" + cmd[2] + "\003 by \00302" + ot->second->getNickName() + "\003\r\n");
	mysend(fd, "You've invited \00302" + it->second->getNickName() + "\003 to \00306" + cmd[2] + "\003\r\n");
}