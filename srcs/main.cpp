/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:29:49 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/30 16:27:57 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

int main(int ac, char** av){
	if (ac != 3){
		std::cout << "Error: valid input is ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	if (atoi(av[1]) < 1024 || atoi(av[1]) > 65535){
		std::cerr << "Error: port number must be between 1024 and 65535" << std::endl;
		return (1);
	}
	Server	server("irc", atoi(av[1]), av[2]);
	try {
		signal(SIGINT, Server::signals);
		signal(SIGQUIT, Server::signals);
		server.init();
	}
	catch (std::exception& e){
		std::cout << e.what() << std::endl;
	}
}