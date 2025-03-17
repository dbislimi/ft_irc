/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/17 17:14:17 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Server.hpp"

bool Server::signal = false;

void Server::signals(int signum)
{
	(void)signum;
	std::cout << "signal received " << std::endl;
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

void Server::init()
{
	_init_socket();
	while (Server::signal == false)
	{
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && Server::signal == false){
			throw std::runtime_error("Error: function poll failed");
		}
		for (size_t i = 0; i < _fds.size(); ++i){
			if (_fds[i].revents & POLLIN){
				if (_fds[i].fd == _serverFd)
					newClient();
				else
					newCmd(_fds[i].fd);
			}
		}
	}
}

void Server::newClient(){
	struct sockaddr_in sa;
	int clientfd;
	socklen_t size = sizeof(sa);
	struct pollfd poll;
	Client *clicli = new Client();

	clientfd = accept(this->_serverFd, reinterpret_cast<struct sockaddr *>(&sa), &size);
	if (clientfd == -1)
		throw std::runtime_error("Error: function accept failed");
	if (fcntl(clientfd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error: failed to set option O_NONBLOCK on socket.");
	poll.fd = clientfd;
	poll.events = POLLIN;
	poll.revents = 0;
	clicli->setFd(clientfd);
	clicli->setSign(false);
	clicli->setBoolName(false);
	// std::cout << "IP = " << clicli->getFd() << std::endl;
	clicli->setIpAdd(sa.sin_addr);
	_clients.insert(std::pair<int, Client *>(clientfd, clicli));
	_fds.push_back(poll);
	std::cout << "Client <" << clientfd << "> Connected" << std::endl;
	intro(clientfd);
	printmap();
}

void Server::newCmd(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	size_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0){
		std::cout << "Client " << fd << " disconnected." << std::endl;
		eraseClient(fd);
		close(fd);
		return;
	}
	buff[bytes] = 0;
	_cmd = parseBuff(buff);
	// if (_clients[fd]->isConnected() == false){
	// 	get_info(fd, _cmd);
	// 	return ;
	// }
	for (std::deque<std::string>::iterator it = _cmd.begin(); it != _cmd.end(); ++it){
		std::cout << "Data: [" << *it << "]" << std::endl;
		handleCmd(buff, parseCmd(*it), fd);
	}
	// std::cout << "Client <" << fd << "> Data: " << buff << std::endl;
}

void	Server::get_info(int fd, std::deque<std::string> cmd){
	for (std::deque<std::string>::iterator it = cmd.begin(); it != cmd.end(); ++it){
		if (*it == "NICK"){
			++it;
			_clients[fd]->setNickName(*it);
		}
		if (*it == "USER"){
			++it;
			_clients[fd]->setUserName(*it);
			_clients[fd]->connect();
		}
	}
}

void Server::checkPassword(int fd)
{
	trim(_passWord);
	std::string pass;
	if (_cmd[0] == _passWord)
	{
		pass = "valid passeword\r\n";
		send(fd, pass.c_str(), pass.length(), 0);
		for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if (it->first == fd)
			{
				it->second->setSign(true);
			}
		}
	}
	else
	{
		pass = "wrong password, retry \r\n";
		send(fd, pass.c_str(), pass.length(), 0);
	}
}

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
}

void Server::printmap()
{
	std::cout << std::endl
			  << "Map: " << std::endl;
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{

		std::cout << "[" << it->first << "] = " << it->second->getIp() << std::endl;
	}
	std::cout << std::endl;
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
	std::map<int, Client *>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return;
	delete it->second;
	_clients.erase(it);
}

void Server::handleCmd(std::string buff, std::deque<std::string> cmd, int fd)
{
	std::string cmds[7] = {"JOIN", "NICK", "USER", "KICK", "INVITE", "TOPIC", "MODE"};
	void (Server::*funct[7])(int, std::string) = {&Server::JOIN, &Server::USER, &Server::NICK, &Server::KICK, &Server::INVITE, &Server::TOPIC, &Server::MODE};
	std::string	unvalid = "Unvalid command, please use JOIN\r\n";
	
	for (int i = 0; i < 7; ++i){
		if (cmd[0] == cmds[i]){
			(this->*funct[i])(fd, cmd[1]);
			return ;
		}
	}
	if (_clients[fd]->getBoolName() == true)
		_channels[_clients[fd]->getChannel()]->sendChannel(fd, buff);
	else
		send(fd, unvalid.c_str(), unvalid.length(), 0);
}

void	Server::JOIN(int fd, std::string value){
	std::string welcome = _clients[fd]->getNickName() +" [~" + _clients[fd]->getNickName() + "@" +  "] has joined #" + value + "\r\n";
	std::map<std::string, Channel*>::iterator it = _channels.find(value);
	
	if (it == _channels.end())
		_channels[value] = new Channel(value);
	_clients[fd]->setChannel(value);
	_channels[value]->add(fd);
	_channels[value]->sendChannel(-1, welcome);
	_clients[fd]->setBoolName(true);
}
void	Server::USER(int fd, std::string value){
	(void)value;
	(void)fd;
	std::cout << "set USER to: " << value << std::endl;
}
void	Server::NICK(int fd, std::string value){
	(void)value;
	(void)fd;
	std::cout << "set NICK to: " << value << std::endl;
}
void	Server::KICK(int fd, std::string value){
	(void)value;
	(void)fd;
}
void	Server::INVITE(int fd, std::string value){
	(void)value;
	(void)fd;
}
void	Server::TOPIC(int fd, std::string value){
	(void)value;
	(void)fd;
}
void	Server::MODE(int fd, std::string value){
	(void)value;
	(void)fd;
}

void Server::intro(int clientfd)
{
	ssize_t bytes;

	std::string test = "welcome to the TEST Internet Relay Chat Network\r\n";
	bytes = send(clientfd, test.c_str(), test.size(), 0);
	if (bytes == -1)
		throw std::runtime_error("Error: function send failed");
	test = "your host is " + _name + " running version 1.0\r\n";
	bytes = send(clientfd, test.c_str(), test.size(), 0);
	if (bytes == -1)
		throw std::runtime_error("Error: function send failed");
	test = "this server was created the 11/03/2025\r\n";
	bytes = send(clientfd, test.c_str(), test.size(), 0);
	if (bytes == -1)
		throw std::runtime_error("Error: function send failed");
	std::string ask = "Please enter a password with /password [password].\r\n";
	send(clientfd, ask.c_str(), ask.length(), 0);
	std::map<int, Client *>::iterator it = _clients.find(clientfd);
	if (it == _clients.end())
	{
		throw std::runtime_error("Error : not find client");
	}
}
