/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monitor_register.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:31:22 by disantam          #+#    #+#             */
/*   Updated: 2025/04/01 16:07:05 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Monitor.hpp"

int	Monitor::register_event()
{
	int	flag;

	for (int i = 0; i <= this->maxSock && this->socksReady > 0; i++)
	{
		flag = 0;
		while (i <= this->maxSock && !FD_ISSET(i, &this->masterSet))
			i++;
		if (i > this->maxSock)
		{
			std::cout << i << std::endl;
			break;
		}
		if (this->sockets_islistening(i) && this->register_connection(i) < 0)
			return (-1);
		if (!this->sockets_islistening(i) && this->register_request(i, flag) < 0)
			return (-1);
		if (flag)
		{
			this->sockets_close(i);
		}
	}
	return (0);
}

int	Monitor::register_connection(const int listenSock)
{
	int	newSock;
	int	flag;

	flag = 0;
	while (true)
	{
		newSock = accept(listenSock, NULL, NULL);
		if (newSock < 0 && errno != EWOULDBLOCK)
		{
			std::cerr << strerror(errno) << std::endl;
			return (-1);
		}
		if (newSock < 0)
			break;
		FD_SET(newSock, &this->masterSet);
		if (newSock > this->maxSock)
			this->maxSock = newSock;
		if (!flag)
			this->socksReady--;
		flag = 1;
	}
	return (0);
}

int	Monitor::register_request(const int sock, int &flag)
{
	int 		nb = 1;
	char		buff[501];
	std::string	req;

	buff[0] = '\0';
	while (nb != 0)
	{
		nb = recv(sock, buff, 500, MSG_DONTWAIT);
		if (nb < 0)
			break;
		buff[nb] = '\0';
		req += buff;
	}
	send(sock, req.c_str(), req.size(), MSG_DONTWAIT);
	flag = 1;
	this->socksReady--;
	return (0);
}
