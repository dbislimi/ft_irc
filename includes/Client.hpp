/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:07:40 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/06 12:06:40 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CLIENT_HPP
# define CLIENT_HPP

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

class Client {
	private:

	public:
		Client();
		~Client();
		Client(const Client& instance);
		Client&	operator=(const Client& instance);
};


// Pour une adresse IPv4 uniquement
// (voir sockaddr_in6 pour IPv6)
struct sockaddr_in {
    sa_family_t    sin_family;
    in_port_t      sin_port;
    struct in_addr sin_addr;
};
struct in_addr {
    uint32_t       s_addr;
};


// Pour une adresse IPv6 uniquement
// (voir sockaddr_in pour IPv4)
struct sockaddr_in6 {
    sa_family_t     sin6_family;
    in_port_t       sin6_port;
    uint32_t        sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t        sin6_scope_id;
};
struct in6_addr {
    unsigned char   s6_addr[16];
};

#endif