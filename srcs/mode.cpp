#include "../includes/all.hpp"

void	Server::MODE(int fd, std::deque<std::string> cmd){
	(void)fd;
	(void)cmd;
	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":server 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}

}