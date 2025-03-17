/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsafi <bsafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:22:35 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/17 15:29:45 by bsafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

std::deque<std::string>	parseCmd(char* buff){
	std::deque<std::string> deque;
	std::string	str(buff);
	size_t	first = 0;
	size_t	last = 0;

	while (1){
		first = str.find_first_not_of(" \r\t\n", last);
		if (first == std::string::npos)
			break ;
		last = str.find_first_of(" \r\t\n", first);
		deque.push_back(str.substr(first, (last) - first));
	}
	for (size_t i = 0; i < deque.size(); ++i){
		std::cout << deque[i] << std::endl;
	}
	return (deque);
}

void trim(std::string &str) {
    size_t last = str.find_last_not_of("\r\n\t");
    if (last != std::string::npos)
        str.erase(last + 1);
}
