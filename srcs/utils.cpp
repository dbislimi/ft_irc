/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:35 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/12 14:57:23 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::deque<std::string>	parseCmd(char* buff){
	std::deque<std::string> deque;
	std::string	str(buff);
	size_t	first = 0;
	size_t	last = 0;

	while (1){
		first = str.find_first_not_of(" \t\n", last);
		if (first == std::string::npos)
			break ;
		last = str.find_first_of(" \t\n", first);
		deque.push_back(str.substr(first, last - first));
	}
	return (deque);
}