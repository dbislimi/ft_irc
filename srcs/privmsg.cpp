/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 10:10:17 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/14 15:23:34 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

void	Server::PRIVMSG(int fd, std::deque<std::string> cmd){
	std::string	msg;
	std::string privmsg;
	size_t		size = cmd.size();
	
	if (_clients[fd]->getNickName().empty()){
		mysend(fd, ":server 451 * :You have not registered\r\n");
		return ;
	}
	if (_clients[fd]->getUserName().empty()){
		mysend(fd, ":server 451 " + _clients[fd]->getNickName() +  " :You have not registered\r\n");
		return ;
	}
	if (size == 1){
		mysend(fd, ":server 411 " + _clients[fd]->getNickName() +  " :No recipient given (PRIVMSG)\r\n");
		return ;
	}
	if (size == 2){
		mysend(fd, ":server 412 " + _clients[fd]->getNickName() +  " :No text to send\r\n");
		return ;
	}
	privmsg = catParam(cmd, 2);
	if (privmsg[0] == ':')
		privmsg.erase(privmsg.begin());
	msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " PRIVMSG " + cmd[1] + " :" + privmsg + "\r\n";
	if (cmd[1][0] == '#'){
		if (_channels.find(cmd[1]) == _channels.end()){
			mysend(fd, ":server 403 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such channel\r\n");
			return ;
		}
		sendChannel(fd, cmd[1], msg);
	}
	else{
		int receiver = findFd(cmd[1]);
		if (_clients.find(receiver) == _clients.end()){
			mysend(fd, ":server 401 " + _clients[fd]->getNickName() + " " + cmd[1] + " :No such nick/channel\r\n");
			return ;			
		}
		mysend(receiver, msg);	
	}	
}

