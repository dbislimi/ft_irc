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
	if (_clients[fd]->getBoolOps() == false){
	msg = ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
	return;
	}
	for (std::map<int, Client *>::iterator i = _clients.begin(); i != _clients.end(); ++i){
		if (i->first == fd){
			if (cmd[2] == "+i"){
				it->second->setInvitRestrict(true);
				msg = ":" + i->second->getNickName() + "!" + i->second->getUserName() + "@" + i->second->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
				sendChannel(-1, cmd[1], msg);
				if (cmd.size() == 4){
					msg = ":" + _name + " 472 " + _clients[fd]->getNickName() + " " + cmd[1] + " :is unknown mode char to me\r\n";
					send(fd, msg.c_str(), msg.length(), 0);
				}
			}
			else{
				it->second->setInvitRestrict(false);
				msg = ":" + i->second->getNickName() + "!" + i->second->getUserName() + "@" + i->second->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
				sendChannel(-1, cmd[1], msg);
				if (cmd.size() == 4){
					msg = ":" + _name + " 472 " + _clients[fd]->getNickName() + " " + cmd[1] + " :is unknown mode char to me\r\n";
					send(fd, msg.c_str(), msg.length(), 0);
				}
			}
		}
	}
}

void Server::MODEt(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator it;
	std::string msg;

	it = _channels.find(cmd[1]);
	if (_clients[fd]->getBoolOps() == false){
		msg = ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd[2] == "+t"){
		if (it->second->getTopicRestrict() == 0){
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			it->second->setTopicRestrict(true);
			if (cmd.size() == 4){
				msg = ":" + _name + " 472 " + _clients[fd]->getNickName() + " " + cmd[1] + " :is unknown mode char to me\r\n";
				send(fd, msg.c_str(), msg.length(), 0);
			}
		}
		else
			return;
	}
	else{
		if (it->second->getTopicRestrict() == 1){
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			it->second->setTopicRestrict(false);
			if (cmd.size() == 4){
				msg = ":" + _name + " 472 " + _clients[fd]->getNickName() + " " + cmd[1] + " :is unknown mode char to me\r\n";
				send(fd, msg.c_str(), msg.length(), 0);
			}
		}
		else
			return;
	}
}

void Server::MODEk(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator it;
	std::string msg;

	it = _channels.find(cmd[1]);
	if (_clients[fd]->getBoolOps() == false){
	msg = ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n";
	send(fd, msg.c_str(), msg.length(), 0);
	return;
	}
	if (cmd.size() == 3){
		msg = ":" + _name + " 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd[2] == "+k")
	{
		if (it->second->getIsmdp() == false){
			it->second->setMdp(cmd[3]);
			it->second->setIsmdp(true);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else if (it->second->getIsmdp() == true){
			msg = ":" + _name + " 467 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Channel key already set\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
	}
	else if (cmd[2] == "-k"){
		if (cmd[3] == it->second->getMdp()){
			it->second->setMdp("");
			it->second->setIsmdp(false);
			msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else{
			msg = ":" + _name + " 467 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Channel key already set\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
	}
}

void Server::MODEo(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator i;
	std::map<int, Client *>::iterator target = _clients.begin();
	while (target->second->getNickName() != cmd[3] && target != _clients.end())
		target++;
	std::string msg;

	i = _channels.find(cmd[1]);
	if (_clients[fd]->getBoolOps() == false){
		msg = ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd.size() == 3){
		msg = ":" + _name + " 696 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return;
	}
	if (cmd[4] == target->second->getNickName()){	
		if (cmd[2] == "+o" && (cmd.size() == 4)){
			i->second->addOp(target->first);
			target->second->setBoolOps(true);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->second->getNickName() + "\r\n";
			sendChannel(-1, cmd[1], msg);
		}
		else if (cmd[2] == "-o" && (cmd.size() == 4)){
			i->second->addOp(target->first);
			target->second->setBoolOps(false);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->second->getNickName() + "\r\n";
			sendChannel(-1, cmd[1], msg);
		}
	}
	else{
		msg = ":" + _name + " 401 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such nick\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return;
	}
}

void Server::MODEl(int fd, std::deque<std::string> cmd)
{
	std::map<std::string, Channel *>::iterator it;
	std::string msg;

	it = _channels.find(cmd[1]);
	std::cout << cmd.size() << std::endl;
	//std::cout << cmd[3] << std::endl;
	if (_clients[fd]->getBoolOps() == false){
		msg = ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return;
	}
	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty())
	{
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return;
	}
	if (cmd[2] == "+l" && isnumber(cmd[3]) == true){
		if (cmd.size() == 3){
			msg = ":" + _name + " 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return;
		}
		it->second->setLimitUser(atoi(cmd[3].c_str()));
		it->second->setisLimitUser(true);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
	else if (cmd[2] == "-l"){
		it->second->setLimitUser(INT_MAX);
		it->second->setisLimitUser(false);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
}