/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:22:36 by disantam          #+#    #+#             */
/*   Updated: 2025/02/14 13:12:27 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

void	Server::socket_close(socket_t &data, int sock)
{
	close(sock);
	FD_CLR(sock, &data.masterSet);
	if (sock == data.maxSock)
	{
		while (!FD_ISSET(data.maxSock, &data.masterSet))
			data.maxSock -= 1;
	}
}

int	Server::socket_create(socket_t &data)
{
	int	on = 1;

	data.serverSock = socket(AF_INET, SOCK_STREAM, 0);	
	if (data.serverSock < 1)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (setsockopt(data.serverSock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (bind(data.serverSock, (struct sockaddr *)&data.addr, sizeof(data.addr)) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (fcntl(data.serverSock, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (listen(data.serverSock, 10) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	data.maxSock = data.serverSock;
	return (0);
}
