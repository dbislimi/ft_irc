#include "../includes/all.hpp"

void	Server::PASS(int fd, std::deque<std::string> cmd){
	if (_clients[fd]->isConnected()){
		mysend(fd, ":server 462 " + _clients[fd]->getNickName() + " :You may not reregister\r\n");
		return ;
	}
	if (cmd.size() == 1){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	if (cmd[1] == this->_passWord){
		_clients[fd]->connect();
		_clients[fd]->setTimeConnect(time(NULL));
		return ;
	}
}
