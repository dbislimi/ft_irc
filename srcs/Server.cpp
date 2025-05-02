/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/05/02 16:04:33 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

const int Server::PING_WAITNEXT = 25;
const int Server::PING_TIMEOUT = 15;
bool Server::signal = false;

Server::~Server()
{
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		std::cout << "closing fd: " << _fds[i].fd << std::endl;
		close(_fds[i].fd);
	}
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	_clients.clear();
	_fds.clear();
	if (!_channels.empty()){
		for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end();){
			std::map<std::string, Channel*>::iterator temp = it;
			++it;
			delete temp->second;
			_channels.erase(temp);
		}
	}
	_channels.clear();
}

void Server::signals(int signum)
{
	(void)signum;
	Server::signal = true;
}

void Server::_init_socket()
{
	struct sockaddr_in sa;
	struct pollfd poll;

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(_port);
	std::cout << "port:" << _port << std::endl;
	this->_serverFd = socket(sa.sin_family, SOCK_STREAM, 0);
	if (this->_serverFd == -1)
		throw std::runtime_error("Error: socket init failed.");
	std::cout << "Socket created: " << this->_serverFd << std::endl;

	int en = 1;
	if (setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)))
		throw std::runtime_error("Error: failed to set option SO_REUSEADDR on socket.");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error: failed to set option O_NONBLOCK on socket.");
	if (bind(this->_serverFd, reinterpret_cast<struct sockaddr *>(&sa), sizeof(sa)))
		throw std::runtime_error("Error: bind failed.");
	if (listen(this->_serverFd, BACKLOG))
		throw std::runtime_error("Error: failed to listen.");
	poll.fd = this->_serverFd;
	poll.events = POLLIN;
	poll.revents = 0;
	_fds.push_back(poll);
}

void Server::init() {
    _init_socket();
    while (Server::signal == false) {
		pingClient();
        if ((poll(&_fds[0], _fds.size(), 3000) == -1) && Server::signal == false) {
            throw std::runtime_error("Error: function poll failed");
        }
        for (size_t i = 0; i < _fds.size(); ++i) {
            if (_fds[i].revents & POLLIN) {
                if (_fds[i].fd == _serverFd)
                    newClient();
                else
                    newCmd(_fds[i].fd);
            }
        }
    }
}

void Server::pingClient() {
    time_t currentTime = time(NULL);

    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ) {
        if (it->second->isConnected() && (currentTime - it->second->getLastAction() > PING_TIMEOUT)) {
            if (it->second->getLastPong() == 0) {
                it->second->setLastPong(currentTime);
            }
            if (!it->second->getStartedPing()) {
                if (currentTime - it->second->getLastPing() > PING_TIMEOUT) {
                    std::string pingMsg = "PING :" + this->_name + "\r\n";
                    send(it->second->getFd(), pingMsg.c_str(), pingMsg.size(), 0);
                    it->second->setLastPing(currentTime);
                    it->second->setStartedPing(true);
                }
            }
        }
        if (it->second->getStartedPing() && currentTime - it->second->getLastPong() <= PING_WAITNEXT) {
            it->second->setStartedPing(false);
        }
        if (it->second->getStartedPing() && currentTime - it->second->getLastPong() > PING_WAITNEXT) {
			std::string discMsg = "You have been disconnected from the server\r\n";
			send(it->second->getFd(), discMsg.c_str(), discMsg.size(), 0);
            int fd = it->second->getFd();
            ++it;
            eraseClient(fd);
            continue;
        }
        ++it;
    }
}

void Server::PONG(int fd, std::deque<std::string> cmd) {
	(void)cmd;
    time_t timer = time(NULL);
    _clients[fd]->setLastAction(timer);
	_clients[fd]->setLastPong(timer);
	_clients[fd]->setStartedPing(false);
}

void Server::newClient(){
	struct sockaddr_in sa;
	int clientfd;
	socklen_t size = sizeof(sa);
	struct pollfd poll;
	Client *clicli = new Client(this);

	clientfd = accept(this->_serverFd, reinterpret_cast<struct sockaddr *>(&sa), &size);
	if (clientfd == -1)
		throw std::runtime_error("Error: function accept failed");
	if (fcntl(clientfd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error: failed to set option O_NONBLOCK on socket.");
	poll.fd = clientfd;
	poll.events = POLLIN;
	poll.revents = 0;
	clicli->setFd(clientfd);
	clicli->setIpAdd(sa.sin_addr);
	_clients.insert(std::pair<int, Client *>(clientfd, clicli));
	_fds.push_back(poll);
	std::cout << "Client <" << clientfd << "> Connected" << std::endl;
	printmap();
}

void Server::newCmd(int fd)
{
	char buff[1024];
    time_t currentTime = time(NULL);
	
	_clients[fd]->setLastAction(currentTime);
	_clients[fd]->setLastPing(currentTime);
	_clients[fd]->setLastPong(currentTime);
	memset(buff, 0, sizeof(buff));
	size_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0){
		std::cout << "Client <" << fd << "> disconnected." << std::endl;
		eraseClient(fd);
		return;
	}
	buff[bytes] = 0;
	std::string	sbuff(buff);
	if (!_clients[fd]->getCat().empty() || buff[bytes - 1] != '\n'){
		sbuff = _clients[fd]->cat(sbuff);
		if (*(sbuff.end() - 1) != '\n')
			return ;
		_clients[fd]->clearCat();
	}
	_cmd = split(sbuff, "\r\n");
	for (std::deque<std::string>::iterator it = _cmd.begin(); it != _cmd.end(); ++it){
		std::cout << "Data: [" << *it << "] from " << fd << std::endl;
		if (_clients[fd]->getNickName().empty() && !strncmp((*it).c_str(), "CAP", 3))
			continue ;
		handleCmd(split((*it), " \t\r\n"), fd);
	}
}

void Server::handleCmd(std::deque<std::string> cmd, int fd)
{
	std::map<std::string, void (Server::*)(int, std::deque<std::string>)>::iterator it = _cmds.find(cmd[0]);
	std::string	ignore[2] = {"CAP", "WHO"};

	if (it != _cmds.end()){
		if (it->first == "PASS")
			PASS(fd, cmd);
		else if (it->first == "QUIT" || _clients[fd]->isConnected()){
			(this->*(it->second))(fd, cmd);
		}
		return ;
	}
	for (int i = 0; i < 2; ++i)
		if (cmd[0] == ignore[i])
			return ;
	mysend(fd, ":" + _name + " 421 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Unknown command\r\n");
}

void Server::eraseClient(int fd)
{
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if ((*it).fd == fd)
		{
			_fds.erase(it);
			break;
		}
	}
	std::deque<std::string>	cmd(1);
	cmd[0] = "PART";
	for (std::map<std::string, std::map<std::string, int> >::iterator it = _nbCliChannel.begin(); it != _nbCliChannel.end();){
		std::map<std::string, std::map<std::string, int> >::iterator temp1 = it;
		++it;
		for (std::map<std::string, int>::iterator it2 = (temp1->second).begin(); it2 != (temp1->second).end();){
			std::map<std::string, int>::iterator temp2 = it2;
			++it2;
			if (temp2->second == fd){
				_channels[temp1->first]->removeFromLstI(temp2->first);
				deleteFromChannel(fd, temp1->first, cmd, ":Leaving");
			}
		}
	}
	std::map<int, Client *>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return;
	delete it->second;
	_clients.erase(it);
	close(fd);
}

void	Server::QUIT(int fd, std::deque<std::string> cmd){
	(void)cmd;
	eraseClient(fd);
}

void Server::intro(int clientfd)
{
	ssize_t bytes;

	std::string test = "Welcome to the TEST Internet Relay Chat Network\r\n";
	bytes = send(clientfd, test.c_str(), test.size(), 0);
	if (bytes == -1)
		throw std::runtime_error("Error: function send failed");
	test = "Your host is " + _name + " running version 1.0\r\n";
	bytes = send(clientfd, test.c_str(), test.size(), 0);
	if (bytes == -1)
		throw std::runtime_error("Error: function send failed");
	test = "This server was created the 11/03/2025\r\n";
	bytes = send(clientfd, test.c_str(), test.size(), 0);
	if (bytes == -1)
		throw std::runtime_error("Error: function send failed");
	std::map<int, Client *>::iterator it = _clients.find(clientfd);
	if (it == _clients.end())
	{
		throw std::runtime_error("Error : not find client");
	}
}

ssize_t	Server::mysend(int fd, std::string msg){
	return send(fd, msg.c_str(), msg.length(), 0);
}

bool Server::checkClient(std::string value){
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it){
		if (it->second->getNickName() == value)
			return true;
	}
	return false;
}

void	Server::sendChannel(int fd, std::string channel_name, std::string msg){
	for (std::map<std::string, int>::iterator it = _nbCliChannel[channel_name].begin(); it != _nbCliChannel[channel_name].end(); ++it){
        if (fd == -1 || it->second != fd)
			send(it->second, msg.c_str(), msg.length(), 0);
    }
}

bool Server::findUser(std::string channel_name, std::string nick){
	std::map<std::string, int>::iterator it = _nbCliChannel[channel_name].find(nick);
	if (it == _nbCliChannel[channel_name].end())
		return (false);
	return (true);
}

void Server::printmap()
{
	std::cout << std::endl
			  << "Clients: " << std::endl;
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{

		std::cout << "[" << it->first << "] = " << it->second->getIp() << std::endl;
	}
	std::cout << std::endl;
}

int	Server::findFd(std::string nick){
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it){
		if (it->second->getNickName() == nick)
			return (it->first);
	}
	return (0);
}