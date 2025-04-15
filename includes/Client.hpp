/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/10 17:04:40 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "all.hpp"

class Client {
	private:
		bool	_isConnected;
		bool	_isRegistered;
		bool _isSigned;
		bool _allName;
		bool _isOps;
		bool _nick;
		bool _isInvited;
		int _fd;
		std::map<std::string, bool> _invitedOn;
		std::string		_ip;
		struct in_addr	addr;
		std::string _userName;
		std::string _nickName;
		std::string	_prevNick;
		std::string	_channel;
		Server*		_server;
		std::string	_to_cat;

	public:
		Client(Server* server): _isConnected(false), _isRegistered(false), _nick(false), _server(server){}
		~Client(){std::cout << "Client <" << _fd << "> disconnected." << std::endl;}
		bool getRegister();
		bool getIsInvited();
		void setIsInvited(bool isInvited);
		void setRegister();
		bool	isConnected() const;
		void	connect();
		void setFd(int fd);
		int	getFd() const;
		std::string	getUserName() const;
		std::string	getNickName() const;
		std::string getPrevNick() const;
		void setUserName(std::string userName);
		void setNickName(std::string nickName);
		void updatePrevNick();
		void setIpAdd(struct in_addr addr);
		const std::string&	getIp() const;
		void welcomeMsg();
		void	setChannel(std::string& name);
		void statusInvit(std::string channel);
		std::string	getChannel() const;
		std::string	getCat() const;
		std::string cat(std::string buff);
		void		clearCat();
};
