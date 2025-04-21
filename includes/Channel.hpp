/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/21 16:13:23 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#pragma once

# include "all.hpp"

class Channel {
	private:
		std::string			_name;
		std::string			_topic;
		std::time_t			_timestamp;
		std::deque<int>		_ops;
		bool				_invitRestrict;
		bool				_ismdp;
		std::string			_mdp;
		size_t				_limitUser;
		bool				_isLimitUser;
		bool				_isTopicRestrict;
		std::string			_modes;
				bool				_channelOnInvited;
		bool				_channelWithPass;
		bool				_channelUserRestrict;

	public:
		Channel(int op, const std::string& name): _name(name){_ops.push_back(op), _channelOnInvited = false;}

		bool	isOp(int fd);
		void	setChannelOnInvited(bool channelOnInvited);
		bool	getChannelOnInvited();
		void	setChannelWithPass(bool channelWithPass);
		bool	getChannelWithPass();
		void	setChannelUserRestrict(bool channelUserRestrict);
		bool	getChannelUserRestrict();
		void	removeOp(int fd);
		void	addOp(int fd);

		void		setTopic(std::string topic);
		std::string	getTopic() const;
		void		setTime();
		std::time_t	getTime() const;
		bool 		getInvitRestrict();
		void		setInvitRestrict(bool val);
		std::string getMdp();
		void		setMdp(std::string word);
		bool		getIsmdp();
		void		setIsmdp(bool val);
		size_t 		getLimitUser();
		void		setLimitUser(size_t val);
		bool		getisLimitUser();
		void		setisLimitUser(bool val);
		bool		getTopicRestrict();
		void		setTopicRestrict(bool val);
		void		updateModes(std::deque<std::string> cmd);
		std::string	getModes();
};
