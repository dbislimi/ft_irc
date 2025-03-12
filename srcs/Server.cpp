/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:55:52 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/12 16:40:56 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool Server::signal = false;

void Server::signals(int signum){
	(void)signum;
	std::cout << "signal received " << std::endl;
	Server::signal = true;
}

void	Server::_init_socket(){ 
	struct	sockaddr_in	sa;
	struct	pollfd		poll;

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(_port);
	std::cout << "port:" << _port << std::endl;
	this->_serverFd = socket(sa.sin_family, SOCK_STREAM, 0);
	if (this->_serverFd == -1)
		throw std::runtime_error("Error: socket init failed.");
	std::cout << "Socket created: " << this->_serverFd << std::endl;
	
	int	en = 1;
	if (setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)))
		throw std::runtime_error("Error: failed to set option SO_REUSEADDR on socket.");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error: failed to set option O_NONBLOCK on socket.");
	if (bind(this->_serverFd, reinterpret_cast<struct sockaddr*>(&sa), sizeof(sa)))
		throw std::runtime_error("Error: bind failed.");
	if (listen(this->_serverFd, BACKLOG))
		throw std::runtime_error("Error: failed to listen.");
	poll.fd = this->_serverFd;
	poll.events = POLLIN;
	poll.revents = 0;
	_fds.push_back(poll);
}

void	Server::init(){
	_init_socket();
	while (Server::signal == false){
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

void	Server::newClient(){
	struct sockaddr_in sa;
	int clientfd;
	socklen_t size = sizeof(sa);
	struct pollfd paul;
	Client *clicli = new Client();
	
	clientfd = accept(this->_serverFd, reinterpret_cast<struct sockaddr*>(&sa), &size);
	if (clientfd == -1)
		throw std::runtime_error("Error: function accept failed");
	if (fcntl(clientfd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error: failed to set option O_NONBLOCK on socket.");
	paul.fd = clientfd;
	paul.events = POLLIN;
	paul.revents = 0;

	clicli->setFd(clientfd);
	clicli->setIpAdd(sa.sin_addr);
	_clients.insert(std::pair<int, Client*>(clientfd, clicli));
	_fds.push_back(paul);
	std::cout << "Client <" << clientfd << "> Connected" << std::endl;
	printmap();
}


void	Server::newCmd(int fd){
	char	buff[1024];
	
	memset(buff, 0, sizeof(buff));
	size_t	bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0){
		std::cout << "Client " << fd << " disconnected." << std::endl;
		eraseClient(fd);
		close(fd);
		return ;
	}
	buff[bytes] = 0;
	std::cout << "Client <" << fd << "> Data: "<< buff << std::endl;
	handleCmd(parseCmd(buff));
}

Server::~Server(){
	for (size_t i = 0; i < _fds.size(); ++i){
		std::cout << "closing fd: " << _fds[i].fd << std::endl;
		close(_fds[i].fd);
	}
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		delete it->second;
	_clients.clear();
	_fds.clear();
}

void	Server::printmap(){
	std::cout << std::endl << "Map: " << std::endl;
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it){
		char buffer[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET, &((it->second)->getIp()), buffer, sizeof buffer);
		std::cout << "[" << it->first << "] = " << buffer << std::endl;
	}
	std::cout << std::endl;
}

void	Server::eraseClient(int fd){
	for(std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it){
		if ((*it).fd == fd){
			_fds.erase(it); 
			break;
		}
	}
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return ;
	delete it->second;
	_clients.erase(it);
}

void	Server::handleCmd(std::deque<std::string> cmd){
	std::string cmds[7] = {"NICK", "USER", "JOIN", "KICK", "INVITE", "TOPIC", "MODE"};
	void	(Server::*funct[7])() = {&NICK, &USER, &JOIN, &KICK, &INVITE, &TOPIC, &MODE};
	
	for (int i = 0; i < 7; ++i){
		if (cmd[0] == cmds[i])
			(this->*funct[i])();
	}
}

void	Server::NICK(){
}
void	Server::USER(){
}
void	Server::JOIN(){
}
void	Server::KICK(){
}
void	Server::INVITE(){
}
void	Server::TOPIC(){
}
void	Server::MODE(){
}