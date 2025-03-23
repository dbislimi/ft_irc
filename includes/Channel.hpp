/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/23 12:59:51 by dbislimi         ###   ########.fr       */
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
		void	sendChannel(int fd, std::string msg);
		void	joinChannel(std::string channel);
		bool	findChannel(std::string value);
};
