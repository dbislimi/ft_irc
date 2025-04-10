/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/10 18:28:55 by bsafi            ###   ########.fr       */
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
		bool	_nick;
		int _fd;
		std::string		_ip;
		struct in_addr	addr;
		std::string _userName;
		std::string _nickName;
		std::string	_prevNick;
		std::string	_channel;
		Server*		_server;
		std::string	_to_cat;
		bool 		_isopps;

	public:
		Client(Server* server): _isConnected(false), _isRegistered(false), _nick(false), _server(server){}
		~Client(){std::cout << "Client <" << _fd << "> disconnected." << std::endl;}
		bool getSign();
		bool getBoolName();
		bool getBoolNick();
		void setBoolNick();
		bool getRegister();
		void setRegister();
		void setBoolOps(bool isOps);
		bool getBoolOps();
		void setSign(bool isSigned);
		void setBoolName(bool allName);
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
		std::string	getChannel() const;
		std::string	getCat() const;
		std::string cat(std::string buff);
		void		clearCat();
		//bool		getIsopps();
		//void		setIsopps(bool v);
};
