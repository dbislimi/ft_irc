/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:35 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/08 18:18:36 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

std::deque<std::string>	split(std::string str, std::string sep){
	std::deque<std::string> deque;
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

std::string	catParam(std::deque<std::string> cmd, int start){
	std::string param;
	size_t		size = cmd.size();
	
	for (size_t i = start; i < size; ++i){
			if (i != size - 1)
				param += cmd[i] + ' ';
			else
				param += cmd[i];
	}
	return (param);
}
