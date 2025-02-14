/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_register.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:02:20 by disantam          #+#    #+#             */
/*   Updated: 2025/02/14 16:46:20 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Server.hpp"

int	Server::register_request(socket_t &data, int &i, int &flag)
{
	Request		request;
	std::string	response;

	(void)data;
	request = this->request_read(i);
	this->response_make(request, response);
	std::cout << response;
	if (send(i, response.c_str(), response.size(), MSG_DONTWAIT) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		return (-1);
	}
	flag = 1;
	return (0);
}

int	Server::register_connection(socket_t &data)
{
	int	newSock;

	while (true)
	{
		newSock = accept(data.serverSock, NULL, NULL);
		if (newSock < 0 && errno != EWOULDBLOCK)
		{
			std::cerr << strerror(errno) << std::endl;
			return (-1);
		}
		if (newSock < 0)
			break;
		FD_SET(newSock, &data.masterSet);
		if (newSock > data.maxSock)
		{
			data.maxSock = newSock;
		}
	}
	return (0);
}

int	Server::register_event(socket_t &data)
{
	int	i;
	int	flag;

	for (i = 0; i <= data.maxSock && data.ready > 0; i++)
	{
		flag = 0;
		while (i <= data.maxSock && !FD_ISSET(i, &data.workingSet))
			i++;
		if (i > data.maxSock)
			break;
		data.ready -= 1;
		if (i == data.serverSock && this->register_connection(data) < 0)
			return (-1);
		if (i != data.serverSock && this->register_request(data, i, flag) < 0)
			return (-1);
		if (flag)
		{
			this->socket_close(data, i);
		}
	}
	return (0);
}
