#include "../includes/all.hpp"

void	Server::PART(int fd, std::deque<std::string> cmd){
	std::string reason;
	size_t	size = cmd.size();
	std::deque<std::string>	channels;

	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":server 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}
	if (size < 1){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	channels = split(cmd[1], ",");
	for (std::deque<std::string>::iterator it = channels.begin(); it != channels.end(); ++it){
		if (_channels.find(*it) == _channels.end()){
			mysend(fd, ":serveur 403 " + _clients[fd]->getNickName() + " " + *it + " :No such channel\r\n");
			continue ;
		}
		if (findUser(*it, _clients[fd]->getNickName()) == false){
			mysend(fd, ":serveur 442 " + _clients[fd]->getNickName() + " " + *it + " :You're not on that channel\r\n");
			continue ;
		}
		deleteFromChannel(fd, *it, cmd, ":Leaving");
	}
}