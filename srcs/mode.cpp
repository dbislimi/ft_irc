#include "../includes/all.hpp"

void Server::MODE(int fd, std::deque<std::string> cmd)
{
	std::string flags[] = {"+i", "+t", "+k", "+o", "+l"};
	std::string flags2[] = {"-i", "-t", "-k", "-o", "-l"};
	void (Server::*fct[])(int, std::deque<std::string>) = {&Server::MODEi, &Server::MODEt, &Server::MODEk, &Server::MODEo, &Server::MODEl};
	for (int i = 0; i < 5; ++i)
	{
		if (cmd[2] == flags[i] || cmd[2] == flags2[i])
		{
			(this->*fct[i])(fd, cmd);
			return;
		}
	}
	std::string msg = "Error: must use modes with a known flags\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
}

void Server::MODEi(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator it;
	std::string msg;

	it = _channels.find(cmd[1]);
	for (std::map<int, Client *>::iterator i = _clients.begin(); i != _clients.end(); ++i){
		if (i->first == fd){
			if (cmd[2] == "+i"){
				it->second->setInvitRestrict(true);
				msg = ":" + i->second->getNickName() + "!" + i->second->getUserName() + "@" + i->second->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
				sendChannel(-1, cmd[1], msg);
			}
			else{
				it->second->setInvitRestrict(false);
				msg = ":" + i->second->getNickName() + "!" + i->second->getUserName() + "@" + i->second->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
				sendChannel(-1, cmd[1], msg);
			}
		}
	}
}

void Server::MODEt(int fd, std::deque<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	std::cout << "MODEt EST APPELER" << std::endl;
}

void Server::MODEk(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator it;
	std::string msg;

	it = _channels.find(_name);
	if (cmd[2].empty())
	{
		it->second->setMdp(NULL);
	}
	else
	{
		it->second->setMdp(cmd[2]);
		msg = "New mdp is " + it->second->getMdp() + "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
	std::cout << "MODEk EST APPELER" << std::endl;
}

void Server::MODEo(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator i;
	std::map<int, Client *>::iterator target = _clients.begin();
	while (target->second->getNickName() != cmd[3] && target != _clients.end())
		target++;
	std::string msg;

	i = _channels.find(cmd[1]);
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first == fd && target->second->getNickName() == cmd[3])
		{
			if (cmd[2] == "-o"){
				i->second->removeOp(target->first);
				msg = ":" + it->second->getNickName() + "!" + it->second->getUserName() + "@" + it->second->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->second->getNickName() + "\r\n";
				sendChannel(-1, cmd[1], msg);
			}
			else
			{
				i->second->addOp(target->first);
				msg = ":" + it->second->getNickName() + "!" + it->second->getUserName() + "@" + it->second->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->second->getNickName() + "\r\n";
				sendChannel(-1, cmd[1], msg);
			}
		}
	}
}

void Server::MODEl(int fd, std::deque<std::string> cmd)
{
	(void)fd;
	(void)cmd;
	std::cout << "MODEl EST APPELER" << std::endl;
	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty())
	{
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return;
	}
}