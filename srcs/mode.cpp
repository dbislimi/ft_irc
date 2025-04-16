#include "../includes/all.hpp"

void Server::MODE(int fd, std::deque<std::string> cmd)
{
	std::string flags[] = {"+i", "+t", "+k", "+o", "+l"};
	std::string flags2[] = {"-i", "-t", "-k", "-o", "-l"};
	bool (Server::*fct[])(int, std::deque<std::string>, Channel* channel) = {&Server::MODEi, &Server::MODEt, &Server::MODEk, &Server::MODEo, &Server::MODEl};
	std::map<std::string, Channel *>::iterator it;
	
	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":server 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}
	if (cmd.size() == 1){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	it = _channels.find(cmd[1]);
	if (it == _channels.end()){
		mysend(fd, ":serveur 403 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such channel\r\n");
		return ;
	}
	if (cmd.size() == 2){
		std::cout << "test" << std::endl;
		mysend(fd, ":server 324 " + _clients[fd]->getNickName() +  " " + cmd[1] + " :+" + _channels[cmd[1]]->getModes() + "\r\n");
		return ;	
	}
	if (_clients[fd]->getBoolOps() == false){
		mysend(fd, ":" + _name + " 482 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You're not channel operator\r\n");
		return ;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (cmd[2] == flags[i] || cmd[2] == flags2[i])
		{
			if ((this->*fct[i])(fd, cmd, it->second))
				_channels[cmd[1]]->updateModes(cmd);
			return;
		}
	}
	mysend(fd, ":server 472 " + _clients[fd]->getNickName() +  " " + cmd[1][1] + " :is unknown mode char to me\r\n");
}

bool Server::MODEi(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::string msg;

	if (cmd[2] == "+i"){
		channel->setInvitRestrict(true);
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
		sendChannel(-1, cmd[1], msg);
	}
	else{
		channel->setInvitRestrict(false);
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
		sendChannel(-1, cmd[1], msg);
	}
	return (1);
}

bool Server::MODEt(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::string msg;

	if (cmd[2] == "+t"){
		if (channel->getTopicRestrict() == 0){
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			channel->setTopicRestrict(true);
		}
	}
	else{
		if (channel->getTopicRestrict() == 1){
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			channel->setTopicRestrict(false);
		}
	}
	return (1);
}

bool Server::MODEk(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::string msg;

	if (cmd.size() == 3){
		msg = ":" + _name + " 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return (0);
	}
	if (cmd[2] == "+k")
	{
		if (channel->getIsmdp() == false){
			channel->setMdp(cmd[3]);
			channel->setIsmdp(true);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else if (channel->getIsmdp() == true){
			msg = ":" + _name + " 467 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Channel key already set\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return (0);
		}
	}
	else if (cmd[2] == "-k"){
		if (cmd[3] == channel->getMdp()){
			channel->setMdp("");
			channel->setIsmdp(false);
			msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else{
			msg = ":" + _name + " 467 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Channel key already set\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return (0);
		}
	}
	return (1);
}

bool Server::MODEo(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::map<int, Client *>::iterator target = _clients.begin();
	while (target->second->getNickName() != cmd[3] && target != _clients.end())
		target++;
	std::string msg;

	if (cmd.size() == 3){
		msg = ":" + _name + " 696 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return (0);
	}
	if (cmd[4] == target->second->getNickName()){	
		if (cmd[2] == "+o" && (cmd.size() == 4)){
			channel->addOp(target->first);
			target->second->setBoolOps(true);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->second->getNickName() + "\r\n";
			sendChannel(-1, cmd[1], msg);
		}
		else if (cmd[2] == "-o" && (cmd.size() == 4)){
			channel->addOp(target->first);
			target->second->setBoolOps(false);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->second->getNickName() + "\r\n";
			sendChannel(-1, cmd[1], msg);
		}
	}
	else{
		msg = ":" + _name + " 401 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such nick\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return (0);
	}
	return (1);
}

bool Server::MODEl(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::string msg;

	if (cmd[2] == "+l" && isnumber(cmd[3]) == true){
		if (cmd.size() == 3){
			msg = ":" + _name + " 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return (0);
		}
		channel->setLimitUser(atoi(cmd[3].c_str()));
		channel->setisLimitUser(true);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
	else if (cmd[2] == "-l"){
		channel->setLimitUser(INT_MAX);
		channel->setisLimitUser(false);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
	}
	return (1);
}
