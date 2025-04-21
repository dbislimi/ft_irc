/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dravaono <dravaono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:29:49 by dbislimi          #+#    #+#             */
/*   Updated: 2025/04/15 18:38:01 by dravaono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.hpp"

int main(int ac, char** av){
	if (ac != 3){
		std::cout << "Error: valid input is ./ircserv <port> <password>" << std::endl;
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
		//FERMER LES FDs
	}
}