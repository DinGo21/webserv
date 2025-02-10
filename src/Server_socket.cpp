/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:22:36 by disantam          #+#    #+#             */
/*   Updated: 2025/02/10 17:30:17 by disantam         ###   ########.fr       */
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
	if (fcntl(data.serverSock, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (bind(data.serverSock, (struct sockaddr *)&data.addr, sizeof(data.addr)) < 0)
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

int	Server::run(socket_t &data)
{
	FD_ZERO(&data.masterSet);
	FD_SET(data.serverSock, &data.masterSet);
	while (true)
	{
		memcpy(&data.workingSet, &data.masterSet, sizeof(data.masterSet));
		data.timeout.tv_sec = 3 * 60;
		data.timeout.tv_usec = 0;
		data.ready = select(data.maxSock + 1, &data.workingSet, NULL, NULL, &data.timeout);
		if (data.ready < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			return (-1);
		}
		if (data.ready == 0)
			break;
		if (this->register_event(data) < 0)
			return (-1);
	}
	for (int i = 0; i < data.maxSock; i++)
	{
		if (FD_ISSET(i, &data.masterSet))
			close(i);
	}
	return (0);
}

void	Server::init(socket_t &sockData)
{
	memset(&sockData, 0, sizeof(sockData));
	sockData.addr.sin_family = AF_INET;
	sockData.addr.sin_port = htons(this->_port);
	sockData.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockData.addrlen = sizeof(sockData.addr);
}
