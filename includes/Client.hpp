/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:07:40 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/13 15:23:07 by dravaono         ###   ########.fr       */
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
		bool _isSigned;
		bool _allName;
		int _fd;
		struct in_addr	addr;
		std::string _userName;
		std::string _nickName;

	public:
		bool getSign();
		bool getBoolName();
		void setSign(bool isSigned);
		void setBoolName(bool allName);
		Client(){}
		~Client(){std::cout << "Client " << _fd << "erased." << std::endl;}
		void setFd(int fd);
		int	getFd() const;
		std::string	getUserName() const;
		std::string	getNickName() const;
		void setUserName(std::string userName);
		void setNickName(std::string nickName);
		void setIpAdd(struct in_addr addr);
		const struct in_addr&	getIp() const;
		void welcomeMsg();
};

#endif