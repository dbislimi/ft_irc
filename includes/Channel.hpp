/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:16 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/09 20:41:02 by dbislimi         ###   ########.fr       */
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

	public:
		Channel(int op, const std::string& name): _name(name){_ops.push_back(op);}

		bool	isOp(int fd);
		void	removeOp(int fd);
		void	addOp(int fd);

		void		setTopic(std::string topic);
		std::string	getTopic() const;
		void		setTime();
		std::time_t	getTime() const;
};
