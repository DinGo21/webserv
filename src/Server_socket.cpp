/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:22:36 by disantam          #+#    #+#             */
/*   Updated: 2025/01/22 16:00:57 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

int	Server::socket_create()
{
	int	on = 1;

	this->server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 1)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (setsockopt(this->server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (fcntl(this->server_sock, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	return (0);
}