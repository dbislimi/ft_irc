#include "../includes/all.hpp"

void	Server::KICK(int fd, std::deque<std::string> cmd){
	std::string reason;
	size_t	size = cmd.size();

	if (size == 1){
		mysend(fd, "Usage: KICK <nick> [reason], kicks the nick from the current channel (needs chanop)\r\n", 0);
		return ;
	}
	if (size == 2)
		reason = _clients[fd]->getNickName();
	else if (size == 3)
		reason = cmd[2];
	else{
		for (size_t i = 2; i < size - 2; ++i)
			reason += cmd[i];
	}
	mysend(fd, ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " KICK " + _clients[fd]->getChannel() + " " + cmd[1] + " :" + reason + "\r\n", 0);
}