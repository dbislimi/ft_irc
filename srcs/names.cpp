#include "../includes/all.hpp"

void Server::NAMES(int fd, std::deque<std::string> cmd){
	std::string msg;
	std::deque<std::string> channels;
	if (cmd.size() < 1){
		mysend(fd, ":" + _name + " 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	channels = split(cmd[1], ",");
	msg = ":" + _name + " 353 " + _clients[fd]->getNickName() + " = " + cmd[1] + " :";
	for (std::deque<std::string>::iterator channel = channels.begin(); channel != channels.end(); ++channel){
		for (std::map<std::string, int>::iterator it = _nbCliChannel[*channel].begin(); it != _nbCliChannel[*channel].end(); ++it)
		{
			if (_channels[*channel]->isOp(it->second))
				msg += "@" + _clients[it->second]->getNickName() + " ";
			else 
				msg += _clients[it->second]->getNickName() + " ";
		}
	}
	mysend(fd, msg + "\r\n");
	mysend(fd, ":" + _name + " 366 " + _clients[fd]->getNickName() +  " " + cmd[1] + " :End of /NAMES list\r\n");
}
