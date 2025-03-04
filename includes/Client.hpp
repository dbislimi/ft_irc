/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:07:40 by dbislimi          #+#    #+#             */
/*   Updated: 2025/03/04 08:08:52 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CLIENT_HPP
# define CLIENT_HPP

class Client {
	private:

	public:
		Client();
		~Client();
		Client(const Client& instance);
		Client&	operator=(const Client& instance);
};

#endif