/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:55:49 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/10 15:07:36 by dbislimi         ###   ########.fr       */
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
# define BACKLOG 10 // nombre max de demandes de connexion

class Server {
	private:
		std::string			_name; 
		int					_port; 
		int					_serverFd; 
		std::map<int, Client>	_clients; 
		std::vector<struct pollfd>	_fds; 
		void	_init_socket(); 
		
		public: 
		Server(const std::string& name, int port) : _name(name), _port(port){} 
		~Server();
		Server(const Server& instance); 
		Server&	operator=(const Server& instance); 
		void	init(); 
};
	
	
#endif