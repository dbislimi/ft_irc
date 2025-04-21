/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/21 19:28:38 by dbislimi         ###   ########.fr       */
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
		long				_limitUser;
		bool				_isLimitUser;
		bool				_isTopicRestrict;
		std::string			_modes;
		
	public:
		Channel(int op, const std::string& name): _name(name){_ops.push_back(op);}

		bool	isOp(int fd);
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
};
