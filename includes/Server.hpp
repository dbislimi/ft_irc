/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:55:49 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/17 15:41:32 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERVER_HPP
# define SERVER_HPP

# include "Channel.hpp"
# include <algorithm>
# include <exception>
# include <cstring>
# include <cstdlib>
# include <unistd.h>
# include <cstdio>
# include <fcntl.h>
# include <poll.h>


# include <csignal>
#include <deque>
# define BACKLOG 10 // nombre max de demandes de connexion

class Server {
	private:
		static bool signal;
		std::string			_name; 
		int					_port; 
		int					_serverFd;
		std::map<std::string, Channel*>	_channels;
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
		void	handleCmd(std::string buff, std::deque<std::string> cmd, int fd);
		void	intro(int clientfd);
		void	get_info(int fd, std::deque<std::string> cmd);

		void	JOIN(int fd, std::string value);
		void	USER(int fd, std::string value);
		void	NICK(int fd, std::string value);
		void	KICK(int fd, std::string value);
		void	INVITE(int fd, std::string value);
		void	TOPIC(int fd, std::string value);
		void	MODE(int fd, std::string value);		
};
	
std::deque<std::string>	parseCmd(char* buff);
void trim(std::string &str);
	
#endif