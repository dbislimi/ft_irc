/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:07:40 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/11 14:18:43 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

class Client {
	private:
		int _fd;
		struct in_addr	addr;

	public:
		Client(){}
		~Client(){std::cout << "Client " << _fd << "erased." << std::endl;}
		void setFd(int fd);
		void setIpAdd(struct in_addr addr);
		const struct in_addr&	getIp() const;
};

#endif