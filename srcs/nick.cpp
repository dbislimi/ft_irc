/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:00:53 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/18 17:15:34 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

void	Server::USER(int fd, std::deque<std::string> cmd){
	if (!_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 462 " + _clients[fd]->getNickName() + " :You may not reregister\r\n");
		return ;
	}
	if (cmd.size() < 5){
		mysend(fd, ":server 461 " + _clients[fd]->getNickName() +  " " + cmd[0] + " :Not enough parameters\r\n");
		return ;
	}
	_clients[fd]->setUserName(cmd[1]);
}

void	Server::NICK(int fd, std::deque<std::string> cmd){
	if (cmd.size() == 1){
		if (!_clients[fd]->getNickName().empty())
			mysend(fd, ":server 431 " + _clients[fd]->getNickName() + " :No nickname given\r\n");
		else
			mysend(fd, ":server 431 * :No nickname given\r\n");
		return ;
	}
	if (_clients[fd]->getTempNick().empty())
		_clients[fd]->setTempNick(cmd[1]);
	if (!isCorrectNick(cmd[1])){
		if (!_clients[fd]->getNickName().empty())
			mysend(fd, ":server 432 " + _clients[fd]->getNickName() + " :Erroneus nickname\r\n");
		else
			mysend(fd, ":server 432 * :Erroneus nickname\r\n");
		return ;
	}
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end();){
		if (it->first != fd && it->second->getNickName() == cmd[1]){
			mysend(fd, ":server 433 " + cmd[1] + " :Nickname is already in use\r\n");
			return ;
		}
		++it;
	}
	if (!_clients[fd]->getUserName().empty()){
		if (_clients[fd]->getNickName().empty())
			mysend(fd, ":" + _clients[fd]->getTempNick() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " NICK :" + cmd[1] + "\r\n");
		else
			mysend(fd, ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " NICK :" + cmd[1] + "\r\n");
	}
	_clients[fd]->setNickName(cmd[1]);
}


bool Server::isCorrectNick(std::string nick){
	if (!isalpha(nick[0]) && !isSpecialChar(nick[0]))
		return (false);
	if (nick.size() > 9)
		return (false);
	for (size_t i = 1; i < nick.size(); ++i)
		if (!(isalnum(nick[i]) || isSpecialChar(nick[i]) || nick[i] == '-'))
			return (false);
	return (true);
}
