/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/10 20:54:06 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "all.hpp"

class Channel {
	private:
		std::string			_name;
		std::deque<int>					_ops;
		bool				_invitRestrict;
		bool				_ismdp;
		std::string			_mdp;
		int					_limitUser;

	public:
		Channel(int op, const std::string& name): _name(name){_ops.push_back(op);}

		bool		isOp(int fd);
		void	removeOp(int fd);
		void	addOp(int fd);
		
		bool 		getInvitRestrict();
		void		setInvitRestrict(bool val);
		std::string getMdp();
		void		setMdp(std::string word);
		bool		getIsmdp();
		void		setIsmdp(bool val);
		int 		getLimitUser();
		void		setLimitUser(int val);
};
