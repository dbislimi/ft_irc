/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:35 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/19 13:40:58 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

std::deque<std::string>	split(const char* buff, std::string sep){
	std::deque<std::string> deque;
	std::string	str(buff);
	size_t	first = 0;
	size_t	last = 0;

	while (1){
		first = str.find_first_not_of(sep, last);
		if (first == std::string::npos)
			break ;
		last = str.find_first_of(sep, first);
		deque.push_back(str.substr(first, last - first));
	}
	return (deque);
}

std::string trim(std::string str) {
    size_t last = str.find_last_not_of("\r\n\t");
    if (last != std::string::npos){
        str.erase(last + 1);
	}
	return (str);
}
