/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:07:40 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/13 18:33:09 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
# include <vector>
# include <map>
class Client {
	private:
		bool	_isConnected;
		bool _isSigned;
		bool _allName;
		int _fd;
		std::string		_ip;
		std::string _userName;
		std::string _nickName;

	public:
		bool getSign();
		bool getBoolName();
		void setSign(bool isSigned);
		void setBoolName(bool allName);
		bool	isConnected() const;
		void	connect();
		Client(): _isSigned(false){}
		~Client(){std::cout << "Client " << _fd << "erased." << std::endl;}
		void setFd(int fd);
		int	getFd() const;
		std::string	getUserName() const;
		std::string	getNickName() const;
		void setUserName(std::string userName);
		void setNickName(std::string nickName);
		void setIpAdd(struct in_addr addr);
		const std::string&	getIp() const;
		void welcomeMsg();
};

#endif