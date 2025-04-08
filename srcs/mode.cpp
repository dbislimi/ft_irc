#include "../includes/all.hpp"

void	Server::MODE(int fd, std::deque<std::string> cmd){
	(void)fd;
	(void)cmd;
	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty()){
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return ;
	}
}