/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:55:52 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/13 18:34:07 by dbislimi         ###   ########.fr       */
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
	struct pollfd poll;
	Client *clicli = new Client();

	clientfd = accept(this->_serverFd, reinterpret_cast<struct sockaddr*>(&sa), &size);
	if (clientfd == -1)
		throw std::runtime_error("Error: function accept failed");
	if (fcntl(clientfd, F_SETFL, O_NONBLOCK))
		throw std::runtime_error("Error: failed to set option O_NONBLOCK on socket.");
	poll.fd = clientfd;
	poll.events = POLLIN;
	poll.revents = 0;
	clicli->setFd(clientfd);
	clicli->setSign(false);
	std::cout << "FD = " << clicli->getFd() << std::endl;
	clicli->setIpAdd(sa.sin_addr);
	_clients.insert(std::pair<int, Client*>(clientfd, clicli));
	_fds.push_back(poll);
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
	_cmd = parseCmd(buff);
	if (_clients[fd]->isConnected() == false){
		get_info(fd);
		return ;
	}
	handleCmd(_cmd, fd);
	std::cout << "Client <" << fd << "> Data: "<< buff << std::endl;
}

void	Server::get_info(int fd){
	if (_clients[fd]->getSign() == false){
		checkPassword(fd);
		return ;
	}
	if (_clients[fd]->getUserName() == ""){
		_clients[fd]->setUserName(_cmd[0]);
		return ;
	}
	else if (_clients[fd]->getNickName() == ""){
		_clients[fd]->setNickName(_cmd[0]);
		_clients[fd]->connect();
		return ;
	}
}
bool Server::checkPassword(int fd){
	bool	flag = 0;
	trim(_passWord);
	std::string pass;
	if (_cmd[0] == _passWord){
		pass = "valid passeword\r\n";
		_clients[fd]->setSign(true);
		flag = 1;
	}
	else
		pass = "wrong password, retry \r\n";
	send(fd, pass.c_str(), pass.length(), 0);
	if (flag)
		intro(fd);
	return (flag);
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

void	Server::handleCmd(std::deque<std::string> cmd, int fd){
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it->second->getBoolName() == false){
		std::string ask = "entry nickname:\r\n";
		send(fd, ask.c_str(), ask.length(), 0);
		it->second->setNickName(_cmd[0]);
		it->second->setBoolName(true);
	}
	std::string cmds[5] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE"};
	void	(Server::*funct[5])(int, std::string) = {&Server::JOIN, &Server::KICK, &Server::INVITE, &Server::TOPIC, &Server::MODE};
	
	for (int i = 0; i < 5; ++i){
		if (cmd[0] == cmds[i])
			(this->*funct[i])(fd, cmd[1]);
	}
}

void	Server::JOIN(int fd, std::string value){
	std::string welcome = _clients[fd]->getNickName() +" [~" + _clients[fd]->getNickName() + "@" + _clients[fd]->getIp() + "] has joined #" + value;
	std::map<std::string, Channel*>::iterator it = _channels.find(value);
	
	if (it == _channels.end())
		_channels[value] = new Channel(value);
	_channels[value]->add(fd);
	_channels[value]->sendChannel(welcome);
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

void	Server::intro(int clientfd){
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
	std::string ask = "entry username:\r\n";
	send(clientfd, ask.c_str(), ask.length(), 0);
	std::map<int, Client*>::iterator it = _clients.find(clientfd);
	if (it == _clients.end()){
		throw std::runtime_error("Error : not find client");
	}
	it->second->setUserName(_cmd[0]);
}
