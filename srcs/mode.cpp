#include "../includes/all.hpp"

void	Server::MODE(int fd, std::deque<std::string> cmd){
	std::string flags[] = {"+i", "+t", "+k", "+o", "+l"};
	void (Server::*fct[])(int, std::deque<std::string>) = { &Server::MODEi, &Server::MODEt, &Server::MODEk, &Server::MODEo, &Server::MODEl };
	for (int i = 0; i < 5; ++i){
		if (cmd[1] == flags[i]){
			(this->*fct[i])(fd, cmd);
			return;
		}
	}
	std::string msg = "Error: must use modes with a known flags\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
}

void	Server::MODEi(int fd, std::deque<std::string> cmd){
	(void)cmd;
	(void)fd;
	std::map<std::string, Channel*>::iterator it;

	it = _channels.find(_name);
	if (it->second->getInvitRestrict() == false)
		it->second->setInvitRestrict(true);
	else
		it->second->setInvitRestrict(false);
	std::cout << "MODEi EST APPELER" << std::endl;
}

void	Server::MODEt(int fd, std::deque<std::string> cmd){
	(void)fd;
	(void)cmd;
	std::cout << "MODEt EST APPELER" << std::endl;
}

void	Server::MODEk(int fd, std::deque<std::string> cmd){
	std::map<std::string, Channel*>::iterator it;
	std::string msg;

	it = _channels.find(_name);
	if (cmd[2].empty()){
		it->second->setMdp(NULL);
	}
	else{
		it->second->setMdp(cmd[2]);
		msg = "New mdp is " + it->second->getMdp() + "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
	std::cout << "MODEk EST APPELER" << std::endl;
}

void	Server::MODEo(int fd, std::deque<std::string> cmd){
	(void)fd;
	std::map<int, Client*>::iterator it;
	it = _clients.begin();
	it->second->getNickName();
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it){
		if (it->second->getNickName() == cmd[2]){
			
		}
	}
	std::cout << "MODEo EST APPELER" << std::endl;
}

void	Server::MODEl(int fd, std::deque<std::string> cmd){
	(void)fd;
	(void)cmd;
	std::cout << "MODEl EST APPELER" << std::endl;
	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty()){
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return ;
	}
}