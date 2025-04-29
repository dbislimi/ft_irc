#include "../includes/all.hpp"

void	Server::KICK(int fd, std::deque<std::string> cmd){
	std::string reason;
	size_t	size = cmd.size();

	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":server 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}
	if (size < 2){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	if (_channels.find(cmd[1]) == _channels.end()){
		mysend(fd, ":serveur 403 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such channel\r\n");
		return ;
	}
	if (findUser(cmd[1], _clients[fd]->getNickName()) == false){
		mysend(fd, ":serveur 442 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not on that channel\r\n");
		return ;
	}
	if (_channels[cmd[1]]->isOp(fd) == false){
		mysend(fd, ":serveur 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n");
		return ;
	}
	if (findUser(cmd[1], cmd[2]) == false){
		mysend(fd, ":serveur 401 " + _clients[fd]->getNickName() + " " + cmd[2] + " :No such nick\r\n");
		return ;
	}
	reason = catParam(cmd, 3);
	if (reason.empty())
		reason = ":" + _clients[fd]->getNickName();
	deleteFromChannel(fd, cmd[1], cmd, reason);
}

void	Server::deleteFromChannel(int fd, std::string channel, std::deque<std::string> cmd, std::string reason){
	std::string msg;
	int	fd_leaving;

	if (cmd[0] == "KICK"){
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " " + cmd[0] + " " + channel + " " + cmd[2] + " " + reason + "\r\n";
		fd_leaving = (_nbCliChannel[channel].find(cmd[2]))->second;
	}
	else{
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " " + cmd[0] + " " + channel + " " + reason + "\r\n";
		fd_leaving = fd;
	}
	sendChannel(-1, channel, msg);	
	_channels[channel]->removeOp(fd_leaving);
	std::cout << "LE NOM EN QUESTION " << _clients[fd_leaving]->getNickName() << std::endl;
	_channels[channel]->removeFromLstI(_clients[fd_leaving]->getNickName());
	_nbCliChannel[channel].erase(_clients[fd_leaving]->getNickName());
	if (_nbCliChannel[channel].size() == 0){
		//_clients[fd]->deleteFromInvite(channel);
		_nbCliChannel.erase(channel);
		delete _channels[channel];
		_channels.erase(channel);
	}
}
