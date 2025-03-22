/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/22 16:38:45 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "all.hpp"

class Client {
	private:
		bool	_isConnected;
		bool _isSigned;
		bool _allName;
		bool _isOpps;
		int _fd;
		std::string		_ip;
		struct in_addr	addr;
		std::string _userName;
		std::string _nickName;
		std::string	_channel;
		Server*		_server;
		std::string	_to_cat;

	public:
		Client(Server* server): _isConnected(false), _server(server){}
		~Client(){std::cout << "Client <" << _fd << "> disconnected." << std::endl;}
		bool getSign();
		bool getBoolName();
		void setSign(bool isSigned);
		void setBoolName(bool allName);
		bool	isConnected() const;
		void	connect();
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
		std::string	getCat() const;
		std::string cat(std::string buff);
		void		clearCat();
};
