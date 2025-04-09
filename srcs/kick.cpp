#include "../includes/all.hpp"

void	Server::KICK(int fd, std::deque<std::string> cmd){
	std::string reason;
	size_t	size = cmd.size();

	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty()){
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return ;
	}
	if (size < 2){
		mysend(fd, "Usage: KICK <channel> <nick> [reason], kicks the nick from the current channel (needs chanop)\r\n");
		return ;
	}
	if (_channels.find(cmd[1]) == _channels.end()){
		mysend(fd, "No such channel.\r\n");
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
	sendChannel(-1, cmd[1], ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " KICK " + cmd[1] + " " + cmd[2] + " " + reason + "\r\n");
	_channels[cmd[1]]->removeOp((_nbCliChannel[cmd[1]].find(cmd[2]))->second);
	_nbCliChannel[cmd[1]].erase(cmd[2]);
}
