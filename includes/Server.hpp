/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/22 16:38:57 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

# include "all.hpp"

class Server {
	private:
		static bool signal;
		std::string			_name; 
		int					_port; 
		int					_serverFd;
		std::map<std::string, Channel*>	_channels;
		std::map<std::string, std::set<int> > _nbCliChannel;
		std::map<int, Client*>	_clients;
		std::vector<struct pollfd>	_fds; 
		std::deque<std::string> _cmd;
		std::string _passWord;
		std::map<std::string, void (Server::*)(int, std::string)> _cmds;
		void	_init_socket();
		
	public: 
		Server(const std::string& name, int port, std::string password) : _name(name), _port(port), _passWord(password){
			_cmds["JOIN"] = &Server::JOIN;
			_cmds["QUIT"] = &Server::QUIT;
			_cmds["password"] = &Server::PASS;
			_cmds["NICK"] = &Server::NICK;
			_cmds["USER"] = &Server::USER;
			_cmds["KICK"] = &Server::KICK;
			_cmds["INVITE"] = &Server::INVITE;
			_cmds["TOPIC"] = &Server::TOPIC;
			_cmds["MODE"] = &Server::MODE;
		} 
		~Server();
		static void signals(int signum);
		void	init();
		void 	newClient();
		void	newCmd(int fd);
		void	printmap();
		void	eraseClient(int fd);
		void 	checkPassword(int fd);
		void	handleCmd(std::string buff, std::deque<std::string> cmd, int fd);
		void	get_info(int fd, std::deque<std::string> cmd);
		void	intro(int clientfd);

		void	JOIN(int fd, std::string value);
		void	USER(int fd, std::string value);
		void	NICK(int fd, std::string value);
		void	KICK(int fd, std::string value);
		void	INVITE(int fd, std::string value);
		void	TOPIC(int fd, std::string value);
		void	MODE(int fd, std::string value);
		void	QUIT(int fd, std::string value);
		void	PASS(int fd, std::string value);
		
		void createChannel(std::string value);
		void joinChannel(std::string value, int fd);
		bool checkChannel(std::string value);
};
	
std::deque<std::string>	split(std::string buff, std::string sep);
std::string trim(std::string str);