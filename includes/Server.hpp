/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:55:49 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/13 16:30:40 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <algorithm>
# include <exception>
# include <cstring>
# include <cstdlib>
# include <unistd.h>
# include <cstdio>
# include <fcntl.h>
# include <poll.h>
# include <map>
# include <vector>
# include <csignal>
#include <deque>
# define BACKLOG 10 // nombre max de demandes de connexion

class Server {
	private:
		static bool signal;
		std::string			_name; 
		int					_port; 
		int					_serverFd; 
		std::map<int, Client*>	_clients; 
		std::vector<struct pollfd>	_fds; 
		void	_init_socket();
		std::deque<std::string> _cmd;
		std::string _passWord;
		
	public: 
		Server(const std::string& name, int port, std::string password) : _name(name), _port(port), _passWord(password){} 
		~Server();
		static void signals(int signum);
		void	init();
		void 	newClient();
		void	newCmd(int fd);
		void	printmap();
		void	eraseClient(int fd);
		void 	checkPassword(int fd);
		void	handleCmd(std::deque<std::string> cmd, int fd);
		void	intro(int clientfd);

		void	NICK();
		void	USER();
		void	JOIN();
		void	KICK();
		void	INVITE();
		void	TOPIC();
		void	MODE();
		
};
	
std::deque<std::string>	parseCmd(char* buff);
void trim(std::string &str);
	
#endif