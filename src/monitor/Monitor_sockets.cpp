/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Monitor_sockets.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:30:05 by disantam          #+#    #+#             */
/*   Updated: 2025/04/01 16:33:00 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Monitor.hpp"

int	Monitor::sockets_init()
{
	int								on = 1;
	std::list<listen_t>::iterator	it;

	for (it = this->_listenSocks.begin(); it != this->_listenSocks.end(); it++)
	{
		it->sockd = socket(AF_INET, SOCK_STREAM, 0);
		if (it->sockd < 0 ||
			setsockopt(it->sockd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0 ||
			bind(it->sockd, (struct sockaddr *)&it->addr, it->addrlen) < 0 ||
			fcntl(it->sockd, F_SETFL, O_NONBLOCK) < 0 ||
			listen(it->sockd, 10) < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			return (-1);
		}
		this->_maxSock = it->sockd;
	}
	return (0);
}

void	Monitor::sockets_set()
{
	std::list<listen_t>::iterator	it;

	FD_ZERO(&this->_masterSet);
	for (it = this->_listenSocks.begin(); it != this->_listenSocks.end(); it++)
	{
		FD_SET(it->sockd, &this->_masterSet);
	}
}

void	Monitor::sockets_clean()
{
	for (int i = 0; i < this->_maxSock; i++)
	{
		if (FD_ISSET(i, &this->_masterSet))
		{
			close(i);
		}
	}
}

void	Monitor::sockets_close(const int sock)
{
	close(sock);
	FD_CLR(sock, &this->_masterSet);
	if (sock == this->_maxSock)
	{
		while (!FD_ISSET(this->_maxSock, &this->_masterSet))
			this->_maxSock -= 1;
	}
}

bool	Monitor::sockets_islistening(const int sock)
{
	std::list<listen_t>::iterator	it;

	for (it = this->_listenSocks.begin(); it != this->_listenSocks.end(); it++)
	{
		if (sock == it->sockd)
		{
			return (1);
		}
	}
	return (0);
}
