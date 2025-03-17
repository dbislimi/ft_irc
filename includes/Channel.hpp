/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/17 14:32:46 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_H
# define CHANNEL_H

#include "Client.hpp"

class Channel {
	private:
		std::string			_name;
		std::vector<int>	_users;

	public:
		Channel(const std::string& name): _name(name){}

		void	add(int fd);
		void	sendChannel(int fd, std::string msg);
};

#endif