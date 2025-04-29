/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/29 18:02:31 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#pragma once

# include "all.hpp"

class Channel {
	private:
		std::string					_name;
		std::string					_topic;
		std::time_t					_timestamp;
		std::deque<int>				_ops;
		bool						_invitRestrict;
		bool						_ismdp;
		std::string					_mdp;
		long						_limitUser;
		bool						_isLimitUser;
		bool						_isTopicRestrict;
		std::string					_modes;
		bool						_channelOnInvited;
		bool						_channelWithPass;
		bool						_channelUserRestrict;
		std::vector<std::string>	_lstInvit;

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
		long 		getLimitUser();
		void		setLimitUser(long val);
		bool		getisLimitUser();
		void		setisLimitUser(bool val);
		bool		getTopicRestrict();
		void		setTopicRestrict(bool val);
		void		updateModes(std::deque<std::string> cmd);
		std::string	getModes();
		std::string getName();
		void		setLstInvit(std::string val);
		void		removeFromLstI(std::string nash);
		bool		checkLstI(std::string name);
};
