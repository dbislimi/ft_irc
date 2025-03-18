/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/18 17:15:53 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Server.hpp"
#include "../includes/Client.hpp"
#include "../includes/Channel.hpp"

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
	clicli->setSign(false);
	clicli->setBoolName(false);
	// std::cout << "IP = " << clicli->getFd() << std::endl;
	clicli->setIpAdd(sa.sin_addr);
	_clients.insert(std::pair<int, Client *>(clientfd, clicli));
	_fds.push_back(poll);
	std::cout << "Client <" << clientfd << "> Connected" << std::endl;
	std::string ask = "Please log in with /password [..] .\r\n";
	send(clientfd, ask.c_str(), ask.length(), 0);
	printmap();
}

void Server::newCmd(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	size_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0){
		std::cout << "Client <" << fd << "> disconnected." << std::endl;
		eraseClient(fd);
		return;
	}
	buff[bytes] = 0;
	_cmd = split(buff, "\r\n");
	for (std::deque<std::string>::iterator it = _cmd.begin(); it != _cmd.end(); ++it){
		std::cout << "Data: [" << *it << "]" << std::endl;
		if (_clients[fd]->getNickName().empty() && !strncmp((*it).c_str(), "CAP", 3))
			continue ;
		handleCmd(buff, split((*it).c_str(), " \t\r\n"), fd);
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
	close(fd);
}

void Server::handleCmd(std::string buff, std::deque<std::string> cmd, int fd)
{
	std::string	suggest = (_clients[fd]->isConnected()) ? "/join ." : "/password [..] .";
	std::string	unvalid = cmd[0] + " :Unknown command, please use " + suggest + "\r\n";
	std::map<std::string, void (Server::*)(int, std::string)>::iterator it = _cmds.find(cmd[0]);
	
	if (it != _cmds.end())
		(this->*(it->second))(fd, cmd[1]);
	else if (_clients[fd]->getBoolName() == true)
		_channels[_clients[fd]->getChannel()]->sendChannel(fd, buff);
	else
		send(fd, unvalid.c_str(), unvalid.length(), 0);
}

void	Server::USER(int fd, std::string value){
	(void)fd;
	std::cout << "set USER to: " << value << std::endl;
}
void	Server::NICK(int fd, std::string value){
	(void)fd;
	std::cout << "set NICK to: " << value << std::endl;
}

void	Server::PASS(int fd, std::string value){
	(void)value;
	(void)fd;
	if (value == this->_passWord){
		_clients[fd]->connect();
		return ;
	}
	std::string	bad = "Wrond password ... Please enter a correct password with /password [..].\r\n";
	send(fd, bad.c_str(), bad.length(), 0);
}

void	Server::QUIT(int fd, std::string value){
	(void)value;
	eraseClient(fd);
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
	std::map<int, Client *>::iterator it = _clients.find(clientfd);
	if (it == _clients.end())
	{
		throw std::runtime_error("Error : not find client");
	}
}
