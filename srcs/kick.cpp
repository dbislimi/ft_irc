#include "../includes/all.hpp"

void	Server::KICK(int fd, std::deque<std::string> cmd){
	std::string reason;
	size_t	size = cmd.size();

	if (size == 1){
		mysend(fd, "Usage: KICK <nick> [reason], kicks the nick from the current channel (needs chanop)\r\n", 0);
		return ;
	}
	reason = catParam(cmd);
	mysend(fd, ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " KICK " + _clients[fd]->getChannel() + " " + cmd[1] + " :" + reason + "\r\n", 0);
}