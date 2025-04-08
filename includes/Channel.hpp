/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/08 19:23:11 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "all.hpp"

class Channel {
	private:
		std::string			_name;
		std::map<std::string, int>	_users;
		std::deque<int>					_ops;

	public:
		Channel(int op, const std::string& name): _name(name){_ops.insert(_ops.end(), op);}

		void	add(int fd, std::string nick);
		void	sendChannel(int fd, std::string msg);
		void	joinChannel(std::string channel);
		bool	findChannel(std::string value);
		bool		isOp(int fd);
		bool	findUser(std::string nick);
		void	erase(std::string nick);
		std::map<std::string, int>	getUsers();
};
