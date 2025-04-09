/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/07 14:53:09 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "all.hpp"

class Channel {
	private:
		std::string			_name;
		std::vector<int>	_users;
		int					_op;

	public:
		Channel(int op, const std::string& name): _name(name), _op(op){}

		void	add(int fd);
		void	delete_user(int fd);
		void	sendChannel(int fd, std::string msg);
		void	joinChannel(std::string channel);
		bool	findChannel(std::string value);
};
