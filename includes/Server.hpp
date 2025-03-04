/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:03:27 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/04 08:07:23 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"

#include <deque>

class Server {
	private:
		std::deque<Client*>	_clients;
		
	public:
		Server();
		~Server();
		Server(const Server& instance);
		Server&	operator=(const Server& instance);
};

#endif