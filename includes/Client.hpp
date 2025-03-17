/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/17 17:00:30 by dbislimi         ###   ########.fr       */
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
		struct in_addr	addr;
		std::string _userName;
		std::string _nickName;
		std::string	_channel;

	public:
		bool getSign();
		bool getBoolName();
		void setSign(bool isSigned);
		void setBoolName(bool allName);
		bool	isConnected() const;
		void	connect();
		Client(){}
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
		void	setChannel(std::string& name);
		std::string	getChannel() const;
};

#endif