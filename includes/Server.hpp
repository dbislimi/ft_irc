/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:03:27 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/06 12:04:28 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"

#include <deque>

class Server {
	private:
		int					_serverFd;
		std::deque<Client*>	_clients;
		
	public:
		Server();
		~Server();
		Server(const Server& instance);
		Server&	operator=(const Server& instance);
};

#endif