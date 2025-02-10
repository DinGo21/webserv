/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_register.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:02:20 by disantam          #+#    #+#             */
/*   Updated: 2025/02/10 17:30:38 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

int	Server::register_requests(socket_t &data, int &i, int &flag)
{
	int 	nb;
	char	*buff[3000];

	(void)data;
	nb = recv(i, buff, 3000, 0);
	if (nb < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	if (nb == 0)
		return (0);
	buff[nb] = '\0';
	std::cout << buff;
	if (send(i, buff, nb, 0) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	flag = 1;
	return (0);
}

int	Server::register_connections(socket_t &data)
{
	while (true)
	{
		data.newSock = accept(data.serverSock, NULL, NULL);
		if (data.newSock < 0 && errno != EWOULDBLOCK)
		{
			std::cerr << strerror(errno) << std::endl;
			return (-1);
		}
		if (data.newSock < 0)
			break;
		FD_SET(data.newSock, &data.masterSet);
		if (data.newSock > data.maxSock)
		{
			data.maxSock = data.newSock;
		}
	}
	return (0);
}

int	Server::register_event(socket_t &data)
{
	int				i;
	int				flag;

	for (i = 0; i <= data.maxSock && data.ready > 0; i++)
	{
		flag = 0;
		while (i <= data.maxSock && !FD_ISSET(i, &data.workingSet))
			i++;
		if (i > data.maxSock)
			break;
		data.ready -= 1;
		if (i == data.serverSock && this->register_connections(data) < 0)
			return (-1);
		if (i != data.serverSock && this->register_requests(data, i, flag) < 0)
			return (-1);
		if (flag)
		{
			this->socket_close(data, i);
		}
	}
	return (0);
}
