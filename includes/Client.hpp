/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/29 18:35:47 by bsafi            ###   ########.fr       */
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
		std::string		_ip;
		// struct in_addr	addr;
		std::string _userName;
		std::string _nickName;
		std::string	_tempNick;
		Server*		_server;
		std::string	_to_cat;
		time_t 		_lastAction;
		time_t 		_lastPing;
		time_t 		_lastPong;
		bool _startToPing;
		

	public:
		Client(Server* server): _isConnected(false), _isRegistered(false), _nick(false), _server(server), _startToPing(false){}
		~Client(){std::cout << "Client <" << _fd << "> disconnected." << std::endl;}
		bool getSign();
		bool getBoolName();
		bool getBoolNick();
		void setBoolNick();
		void setSign(bool isSigned);
		void setBoolName(bool allName);
		void	connect();
		bool getRegister();
		bool getIsInvited();
		void setIsInvited(bool isInvited);
		void setRegister();
		bool	isConnected() const;
		bool	getStartedPing() const;
		void	setStartedPing(bool startPing);
		void setFd(int fd);
		int	getFd() const;
		std::string	getUserName() const;
		std::string	getNickName() const;
		std::string getTempNick() const;
		void setUserName(std::string userName);
		void setNickName(std::string nickName);
		void setTempNick(std::string nick);
		void setIpAdd(struct in_addr addr);
		const std::string&	getIp() const;
		void welcomeMsg();
		void	setChannel(std::string& name);
		void statusInvit(std::string channel);
		std::string	getChannel() const;
		std::string	getCat() const;
		std::string cat(std::string buff);
		void		clearCat();
		void		setInvited(std::string, bool value);
		bool		getInvited(Channel c);
		void		insertInvited(std::string, bool val);
		time_t getLastAction();
		void   setLastAction(time_t lastAct);
		time_t getLastPing();
    	void setLastPing(time_t lastPing);
		time_t getLastPong();
    	void setLastPong(time_t lastPong);
		void deleteFromInvite(std::string channel);
};
