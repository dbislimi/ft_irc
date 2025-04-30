/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 10:10:17 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/14 16:06:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

void	Server::PRIVMSG(int fd, std::deque<std::string> cmd){
	std::deque<std::string> receivers;
	std::string	msg;
	std::string privmsg;
	size_t		size = cmd.size();
	int			begin = 1;
	
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
	for (std::deque<std::string>::iterator it = cmd.begin() + 2; it != cmd.end(); ++it){
		++begin;
		if ((*it)[0] == ':')
			break ;
	}
	privmsg = catParam(cmd, begin);
	if (privmsg[0] == ':')
		privmsg.erase(privmsg.begin());
	receivers = split(cmd[1], ",");
	for (std::deque<std::string>::iterator it = receivers.begin(); it != receivers.end(); ++it){
		msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " PRIVMSG " + *it + " :" + privmsg + "\r\n";
		if ((*it)[0] == '#'){
			if (_channels.find(*it) == _channels.end()){
				mysend(fd, ":server 403 " + _clients[fd]->getNickName() + " " + *it + " :No such channel\r\n");
				continue ;
			}
			else if (_nbCliChannel[*it].find(_clients[fd]->getNickName()) == _nbCliChannel[*it].end()){
				mysend(fd, ":server 404 " + _clients[fd]->getNickName() + " " + *it + " :Cannot send to channel\r\n");
				continue ;
			}
			sendChannel(fd, *it, msg);
		}
		else{
			int receiver = findFd(*it);
			if (_clients.find(receiver) == _clients.end()){
				mysend(fd, ":server 401 " + _clients[fd]->getNickName() + " " + *it + " :No such nick/channel\r\n");
				continue ;			
			}
			mysend(receiver, msg);	
		}
	}
}

