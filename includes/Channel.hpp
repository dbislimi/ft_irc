/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/10 16:14:05 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "all.hpp"

class Channel {
	private:
		std::string			_name;
		std::deque<int>		_ops;
		bool				_channelOnInvited;
		bool				_channelWithPass;
		bool				_channelUserRestrict;

	public:
		Channel(int op, const std::string& name): _name(name){_ops.push_back(op), _channelOnInvited = false;}

		bool		isOp(int fd);
		void	setChannelOnInvited(bool channelOnInvited);
		bool	getChannelOnInvited();
		void	setChannelWithPass(bool channelWithPass);
		bool	getChannelWithPass();
		void	setChannelUserRestrict(bool channelUserRestrict);
		bool	getChannelUserRestrict();
		void	removeOp(int fd);
		void	addOp(int fd);
};
