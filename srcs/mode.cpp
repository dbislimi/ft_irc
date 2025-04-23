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
		mysend(fd, ":server 324 " + _clients[fd]->getNickName() +  " " + cmd[1] + " :+" + _channels[cmd[1]]->getModes() + "\r\n");
		return ;	
	}
	if (_channels[cmd[1]]->isOp(fd) == false){
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
		if (channel->getTopicRestrict() == false){
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
			sendChannel(-1, cmd[1], msg);
			channel->setTopicRestrict(true);
		}
	}
	else{
		if (channel->getTopicRestrict() == true){
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
			sendChannel(-1, cmd[1], msg);
			channel->setTopicRestrict(false);
		}
	}
	return (1);
}

bool Server::MODEk(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::string msg;

	if (cmd[2] == "+k")
	{
		if (cmd.size() < 4){
			msg = ":" + _name + " 461 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Not enough parameters\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return (0);
		}
		if (channel->getIsmdp() == false){
			channel->setMdp(cmd[3]);
			channel->setIsmdp(true);
			msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
			sendChannel(-1, cmd[1], msg);
		}
		else if (channel->getIsmdp() == true){
			msg = ":" + _name + " 467 " + _clients[fd]->getNickName() + " " + cmd[1] + " :Channel key already set\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			return (0);
		}
	}
	else if (cmd[2] == "-k"){
		channel->setMdp("");
		channel->setIsmdp(false);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
		sendChannel(-1, cmd[1], msg);
	}
	return (1);
}

bool Server::MODEo(int fd, std::deque<std::string> cmd, Channel* channel)
{
	if (cmd.size() < 4){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return (0);
	}
	std::map<std::string, int>::iterator target = _nbCliChannel[cmd[1]].find(cmd[3]);
	std::string msg;
	
	if (target == _nbCliChannel[cmd[1]].end()){
		msg = ":" + _name + " 401 " + _clients[fd]->getNickName() + " " + cmd[3] + " :No such nick\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return (0);
	}
	if (cmd.size() == 3){		send(fd, msg.c_str(), msg.length(), 0);

		msg = ":" + _name + " 696 " + _clients[fd]->getNickName() + " " + cmd[1] + " :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
		send(fd, msg.c_str(), msg.length(), 0);
		return (0);
	}
	if (cmd[2] == "+o"){
		channel->addOp(target->second);
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->first + "\r\n";
	}
	else if (cmd[2] == "-o"){
		channel->addOp(target->second);
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + target->first + "\r\n";
	}
	sendChannel(-1, cmd[1], msg);
	return (1);
}

bool Server::MODEl(int fd, std::deque<std::string> cmd, Channel* channel)
{
	std::string msg;

	if (cmd[2] == "+l"){
		if (cmd.size() < 4){
			mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
			return (0);
		}
		if (isnumber(cmd[3]) == false)
			return (0);
		if (atol(cmd[3].c_str()) > INT_MAX)
			return (0);
		if (atol(cmd[3].c_str()) == channel->getLimitUser())
			return (0);
		channel->setLimitUser(atoi(cmd[3].c_str()));
		channel->setisLimitUser(true);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + " " + cmd[3] + "\r\n";
		sendChannel(-1, cmd[1], msg);
	}
	else if (cmd[2] == "-l"){
		if (channel->getisLimitUser() == false)
			return (0);
		channel->setLimitUser(INT_MAX);
		channel->setisLimitUser(false);
		msg =  ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " MODE " + cmd[1] + " " + cmd[2] + "\r\n";
		sendChannel(-1, cmd[1], msg);
	}
	return (1);
}
