/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 10:10:17 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/08 18:19:36 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

void	Server::PRIVMSG(int fd, std::deque<std::string> cmd){
	std::string privmsg;
	
	if (_clients[fd]->getNickName().empty() || _clients[fd]->getUserName().empty()){
		mysend(fd, "You need to register first. Use NICK <nickname> then USER <username>.\r\n");
		return ;
	}
	privmsg = catParam(cmd, 2);
	privmsg.erase(privmsg.begin());
	std::string msg = ":" + _clients[fd]->getNickName() + "!" + _clients[fd]->getUserName() + "@" + _clients[fd]->getIp() + " PRIVMSG " + _clients[fd]->getChannel() + " " + cmd[1] + " :" + privmsg + "\r\n";
	_channels[cmd[1]]->sendChannel(fd, msg);
}
