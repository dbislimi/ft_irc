/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/16 18:47:22 by dbislimi         ###   ########.fr       */
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
		std::map<std::string, std::map<std::string, int> > _nbCliChannel;
		std::map<int, Client*>	_clients;
		std::vector<struct pollfd>	_fds; 
		std::deque<std::string> _cmd;
		std::string _passWord;
		std::map<std::string, void (Server::*)(int, std::deque<std::string>)> _cmds;
		void	_init_socket();
		
	public: 
		Server(const std::string& name, int port, std::string password) : _name(name), _port(port), _passWord(password){
			_cmds["JOIN"] = &Server::JOIN;
			_cmds["PART"] = &Server::PART;
			_cmds["QUIT"] = &Server::QUIT;
			_cmds["PASS"] = &Server::PASS;
			_cmds["NICK"] = &Server::NICK;
			_cmds["USER"] = &Server::USER;
			_cmds["KICK"] = &Server::KICK;
			_cmds["INVITE"] = &Server::INVITE;
			_cmds["TOPIC"] = &Server::TOPIC;
			_cmds["MODE"] = &Server::MODE;
			_cmds["PRIVMSG"] = &Server::PRIVMSG;
			_cmds["WHO"] = &Server::WHO;
		} 
		~Server();
		static void signals(int signum);
		void	init();
		void 	newClient();
		void	newCmd(int fd);
		void	printmap();
		void	eraseClient(int fd);
		void 	checkPassword(int fd);
		void	handleCmd(std::deque<std::string> cmd, int fd);
		void	get_info(int fd, std::deque<std::string> cmd);
		void	intro(int clientfd);
		ssize_t	mysend(int fd, std::string msg);

		void	JOIN(int fd, std::deque<std::string> cmd);
		void	USER(int fd, std::deque<std::string> cmd);
		void	NICK(int fd, std::deque<std::string> cmd);
		void	KICK(int fd, std::deque<std::string> cmd);
		void	PART(int fd, std::deque<std::string> cmd);
		void	INVITE(int fd, std::deque<std::string> cmd);
		void	TOPIC(int fd, std::deque<std::string> cmd);
		void	MODE(int fd, std::deque<std::string> cmd);
		bool	MODEi(int fd, std::deque<std::string> cmd, Channel* channel);
		bool	MODEt(int fd, std::deque<std::string> cmd, Channel* channel);
		bool	MODEk(int fd, std::deque<std::string> cmd, Channel* channel);
		bool	MODEo(int fd, std::deque<std::string> cmd, Channel* channel);
		bool	MODEl(int fd, std::deque<std::string> cmd, Channel* channel);
		void	QUIT(int fd, std::deque<std::string> cmd);
		void	PASS(int fd, std::deque<std::string> cmd);
		void	PRIVMSG(int fd, std::deque<std::string> cmd);
		void	WHO(int fd, std::deque<std::string> cmd);

		
		void deleteFromChannel(int fd, std::string channel, std::deque<std::string> cmd, std::string reason);
		void createChannel(int op, std::string value);
		void joinChannel(std::string value, int fd);
		bool checkChannel(std::string value);
		bool checkClient(std::string value);
		void sendChannel(int fd, std::string channel_name, std::string msg);
		bool findUser(std::string channel_name, std::string nick);
		int	findFd(std::string nick);
};
	
std::deque<std::string>	split(std::string buff, std::string sep);
std::string trim(std::string str);
std::string	catParam(std::deque<std::string> cmd, int start);
std::string longToString(long value);
bool		isnumber(std::string s);